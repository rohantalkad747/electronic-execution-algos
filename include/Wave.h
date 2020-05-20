//
// Created by Rohan Talkad on 2020-05-20.
//

#ifndef UNTITLED1_WAVE_H
#define UNTITLED1_WAVE_H


#include "Algorithm.h"
#include "Basket.h"

template<typename A>
class Wave {
private:
    static const PENDING = 1;
    static const SENT = 2;
    static const EXECUTED = 4;
    static const CANCELLED = 8;
    int timestamp;
    double waveNumber;
    double percentage;
    A *algorithm;
    OrderType orderType;
    std::vector<double> prices;
    std::vector<Orders> orders;
    unsigned char waveStatusHistory = 0;

    std::atomic<int> traded(

    0);

    std::vector<Order> splitBySecurity(Basket *b);

    std::mutex mtx_;
    std::lock_guard grd_;

    Algorithm *getAlgorithm() {
        return dynamic_cast<Algorithm *>(algorithm);
    }

    Order *findOrder(std::string orderId);

public:
    Wave(double percentage, A *algorithm, int waveNumber) : percentage(percentage), algorithm(algorithm),
                                                            waveNumber(waveNumber) {}

    virtual ~Wave();

    void onExecution(Execution *execution);

    void cancelWave();

    void replaceWave(Wave *v);

    void executeWave(Basket *b);

    std::vector<Order> getOrders() {
        return this->orders;
    }
};


#endif //UNTITLED1_WAVE_H
