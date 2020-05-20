//
// Created by Rohan on 5/3/2020.
//

#ifndef UNTITLED1_ABSTRACTALGORITHMSCHEDULER_H
#define UNTITLED1_ABSTRACTALGORITHMSCHEDULER_H


#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <chrono>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

class AbstractAlgorithmScheduler {
public:
    AbstractAlgorithmScheduler();

    ~AbstractAlgorithmScheduler();

    template<class F, class... Args>
    std::future<typename std::result_of<typename std::decay<F>::type(typename std::decay<Args>::type...)>::type>
    schedule(F &&f, Args &&... args);

    template<class F, class... Args>
    std::future<typename std::result_of<typename std::decay<F>::type(typename std::decay<Args>::type...)>::type>
    schedule_after(const std::chrono::steady_clock::duration &d, F &&f, Args &&... args);

    template<class F, class... Args>
    std::future<typename std::result_of<typename std::decay<F>::type(typename std::decay<Args>::type...)>::type>
    schedule_at(const std::chrono::steady_clock::time_point &t, F &&f, Args &&... args);

    void clear();

private:
    struct Task {
        std::chrono::steady_clock::time_point time;
        std::function<void()> func;
    };

    struct TaskComparer {
        bool operator()(const Task &left, const Task &right) const { return right.time < left.time; }
    };

    std::vector<Task> mTasks;
    std::mutex mMutex;
    std::condition_variable mCv;
    bool mExit;
    std::thread mThread;
};


#endif //UNTITLED1_ABSTRACTALGORITHMSCHEDULER_H
