#include "../include/RingBuffer.h"

template<class T, long Q_SIZE> void RingBuffer<T, Q_SIZE>::push(T* x)
{
    std::unique_lock<std::mutex> lock(mtx_);
    cond_overflow_.wait(lock,[this](){ return read_ptr_ + Q_SIZE > write_ptr_; });
    ptrs_[write_ptr_++ & Q_MASK ] = x;
    cond_empty_.notify_all();
};

template<class T, long Q_SIZE> T* RingBuffer<T, Q_SIZE>::pop()
{
    std::unique_lock<std::mutex> lock(mtx_);
    cond_empty_.wait(lock, [this](){ return read_ptr_ < write_ptr_; });
    T* item = ptrs_ [ read_ptr_++ & Q_MASK ];
    cond_overflow_.notify_all();
    return item;
};