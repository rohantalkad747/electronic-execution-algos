
#ifndef UNTITLED1_BLOCKINGQUEUE_H
#define UNTITLED1_BLOCKINGQUEUE_H

#include <vector>
#include <mutex>

/**
 * Queue that blocks upon getting/putting.
 * @tparam T
 */
template<class T>
class BlockingQueue {
public:

    BlockingQueue(int size) {
        this->size = size;
    }

    BlockingQueue() : size(0) {
    }

    /**
     * If space is available in this queue, immediately
     * returns true indicating success of insertion.
     */
    bool tryPut(T item);

    /**
     * Blocks the calling thread if there is no space
     * in the queue.
     */
    bool put(T item);

    /**
     * Throws an exception if there is no item in the given queue;
     * otherwise, returns a top of the queue.
     */
    T tryPop();

    /**
     * Blocks the calling thread until there is an item
     * in the given queue.
     */
    T pop();

private:
    std::vector<T> queue;
    std::mutex mtx;
    int size;
};


#endif //UNTITLED1_BLOCKINGQUEUE_H
