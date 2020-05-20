//
// Created by Rohan on 4/24/2020.
//

#ifndef UNTITLED1_RINGBUFFER_H
#define UNTITLED1_RINGBUFFER_H


#include <mutex>
#include <condition_variable>

template<class T, long Q_SIZE>
class RingBuffer {
public:
    void push(T *item);

    T *pop();

private:
    static const unsigned long Q_MASK = Q_SIZE - 1;
    std::mutex mtx_;
    unsigned long read_ptr_, write_ptr_;
    T **ptrs_;
    std::condition_variable cond_empty_;
    std::condition_variable cond_overflow_;
};


#endif //UNTITLED1_RINGBUFFER_H
