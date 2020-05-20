//
// Created by Rohan on 4/26/2020.
//

#ifndef UNTITLED1_COUNTDOWNLATCH_H
#define UNTITLED1_COUNTDOWNLATCH_H


#include <chrono>
#include <condition_variable>
#include <mutex>

class CountDownLatch
{
public:
    explicit CountDownLatch(const unsigned int count) : m_count(count)
    {}

    virtual ~CountDownLatch() = default;

    void await(void);

    template<class Rep, class Period>
    bool await(const std::chrono::duration<Rep, Period> &timeout);

    void countDown(void);

    unsigned int getCount(void);

protected:
    std::mutex              m_mutex;
    std::condition_variable m_cv;
    unsigned int            m_count = 0;
};

#endif //UNTITLED1_COUNTDOWNLATCH_H
