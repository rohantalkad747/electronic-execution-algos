//
// Created by Rohan on 4/26/2020.
//

#include "../include/CountDownLatch.h"

void CountDownLatch::await(void) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_count > 0) {
        m_cv.wait(lock, [this]() { return m_count == 0; });
    }
}

template<class Rep, class Period>
bool CountDownLatch::await(const std::chrono::duration<Rep, Period> &timeout) {
    std::unique_lock<std::mutex> lock(m_mutex);
    bool result = true;
    if (m_count > 0) {
        result = m_cv.wait_for(lock, timeout, [this]() { return m_count == 0; });
    }

    return result;
}

void CountDownLatch::countDown(void) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_count > 0) {
        m_count--;
        m_cv.notify_all();
    }
}

unsigned int CountDownLatch::getCount(void) {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_count;
}
