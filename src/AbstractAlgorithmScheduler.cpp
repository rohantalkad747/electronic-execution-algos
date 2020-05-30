//
// Created by Rohan on 5/3/2020.
//

#include "../include/AbstractAlgorithmScheduler.h"

inline AbstractAlgorithmScheduler::AbstractAlgorithmScheduler() : mExit{false}, mThread{[&]
                                                                                        {
        std::unique_lock<std::mutex> lock{mMutex};
        for (;;)
        {
            auto time = mTasks.empty()
                        ? std::chrono::steady_clock::time_point::max()
                        : mTasks.front().time;

            if (mCv.wait_until(lock,
                               time,
                               [&]()
                               {
                                   return mExit ||
                                          (!mTasks.empty() &&
                                           mTasks.front().time !=
                                           time);
                               }))
            {
                if (mExit)
                {
                    break;
                }
            }
            else if (!mTasks.empty())
            {
                std::pop_heap(mTasks.begin(),mTasks.end(),TaskComparer{});
                auto task = std::move(mTasks.back());mTasks.pop_back();
                lock.unlock();
                task.func();
                lock.lock();
            }
        }
    }}
{}

inline AbstractAlgorithmScheduler::~AbstractAlgorithmScheduler()
{
    {
        std::lock_guard<std::mutex> lock{mMutex};
        mExit = true;
    }
    mCv.notify_one();
    mThread.join();
}

template<class F, class... Args>
std::future<typename std::result_of<typename std::decay<F>::type(typename std::decay<Args>::type...)>::type>
AbstractAlgorithmScheduler::schedule(F &&f, Args &&... args)
{
    return schedule_at(std::chrono::steady_clock::now(), std::forward<F>(f), std::forward<Args>(args)...);
}

template<class F, class... Args>
std::future<typename std::result_of<typename std::decay<F>::type(typename std::decay<Args>::type...)>::type>
AbstractAlgorithmScheduler::schedule_after(const std::chrono::steady_clock::duration &d, F &&f, Args &&... args)
{
    return schedule_at(std::chrono::steady_clock::now() + d, std::forward<F>(f), std::forward<Args>(args)...);
}

template<class F, class... Args>
std::future<typename std::result_of<typename std::decay<F>::type(typename std::decay<Args>::type...)>::type>
AbstractAlgorithmScheduler::schedule_at(const std::chrono::steady_clock::time_point &t, F &&f, Args &&... args)
{
    auto func   = std::make_shared<std::packaged_task<typename std::result_of<typename std::decay<F>::type(
            typename std::decay<Args>::type...)>::type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    auto future = func->get_future();

    {
        std::lock_guard<std::mutex>  lock{mMutex};
        mTasks.push_back(Task{t, [=, func = std::move(func)]
        { (*func)(); }});
        std::push_heap(mTasks.begin(), mTasks.end(), TaskComparer{});
    }
    mCv.notify_one();
    return future;
}

inline void AbstractAlgorithmScheduler::clear()
{
    std::lock_guard<std::mutex> lock{mMutex};
    mTasks.clear();
}