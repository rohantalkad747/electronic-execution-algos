//
// Created by Rohan on 4/8/2020.
//

#include "../include/BlockingQueue.h"

template<class T>
bool BlockingQueue<T>::tryPut(T item)
{
    if (mtx.try_lock())
    {
        if (queue.size() == size)
        {
            return false;
        }
        queue.push_back(item);
        size++;
        mtx.unlock();
        return true;
    }
    return false;
}

template<class T>
bool BlockingQueue<T>::put(T item)
{
    mtx.lock();
    if (queue.size() == size)
    {
        return false;
    }
    queue.push_back(item);
    size++;
    mtx.unlock();
    return true;
}

template<class T>
T BlockingQueue<T>::pop()
{
    while (size == 0);
    mtx.lock();
    std::iterator iter = queue.begin();
    T item = *item;
    queue.erase(iter);
    int i = 0, j;
    while ((j = (i + 1)) < queue.size())
    {
        queue[i++] = queue[j];
    }
    mtx.unlock();
    return item;
}




