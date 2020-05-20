//
// Created by Rohan Talkad on 2020-05-20.
//

#ifndef UNTITLED1_WAVE_H
#define UNTITLED1_WAVE_H


#include "Algorithm.h"
#include "Basket.h"

template<typename A>
class Wave
{
private:
    static const        PENDING          = 1;
    static const        SENT             = 2;
    static const        EXECUTED         = 4;
    static const        PARTIAL_EX       = 8;
    static const        CANCELLED        = 16;
    int                 timestamp;
    double              waveNumber;
    double              percentage;
    A                   *algoConfig;
    OrderType           orderType;
    std::vector<double> prices;
    std::vector<Order>  orders;
    unsigned char       waveSymbolStatus = 0;
    std::atomic<int>    traded           = 0;
    int                 total            = 0;

    std::vector<Order> splitBySecurity(Basket *b);

    std::mutex      mtx_;
    std::lock_guard grd_;

    Algorithm *getAlgorithm()
    {
        return dynamic_cast<Algorithm *>(algoConfig);
    }

    Order *findOrder(const std::string &orderId);

public:

    Wave(double waveNumber, double percentage, A *algoConfig, OrderType orderType,
         const std::vector<double> &prices) : waveNumber(waveNumber), percentage(percentage), algoConfig(algoConfig),
                                              orderType(orderType), prices(prices)
    {};

    virtual ~Wave();

    void onExecution(Execution *execution);

    void cancelWave();

    std::string getStatus();

    void executeWave(Basket *b);

    std::vector<Order> getOrders()
    {
        return this->orders;
    }
};


#endif //UNTITLED1_WAVE_H
