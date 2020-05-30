//
// Created by Rohan Talkad on 2020-05-21.
//

#ifndef UNTITLED1_BASKETWAVE_H
#define UNTITLED1_BASKETWAVE_H


#include "Algorithm.h"
#include "AlgorithmType.h"
#include "LotSizing.h"
#include "Rounding.h"
#include "Basket.h"
#include "AlgorithmFactory.h"

class BasketWave
{
private:
    double                 waveNumber;
    double                 percentage;
    RoutingConfig          *routingConfig;
    Raptor                 *raptor;
    OrderConfig            *orderCfg;
    Algorithm              *algorithm;
    AlgorithmType          *algoType;
    std::vector<double>    prices;
    std::vector<Order>     orders;
    std::vector<OrderType> orderTypes;
    LotSizing              lotSizing;
    Rounding               round;
    unsigned char          waveSymbolStatus = 0;
    std::atomic<int>       traded           = 0;
    int                    total            = 0;
    long                   timestamp        = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

    std::vector<Order> splitBySecurity(Basket *b);

    std::mutex mtx_;

    Order *findOrder(const std::string &orderId);

public:
    static const int PENDING    = 1;
    static const int SENT       = 2;
    static const int EXECUTED   = 4;
    static const int PARTIAL_EX = 8;
    static const int CANCELLED  = 16;

    unsigned char getWaveSymbolStatus()
    {
        return waveSymbolStatus;
    }

    /**
     *
     * @param waveNumber
     * @param percentage
     * @param orderConfig
     * @param algorithmType
     * @param prices
     * @param orderTypes
     * @param raptor
     * @param round
     * @param lotSizing
     */
    BasketWave(double waveNumber,
               double percentage,
               OrderConfig *orderConfig,
               AlgorithmType *algorithmType,
               const std::vector<double> &prices,
               const std::vector<OrderType> orderTypes,
               Raptor *raptor,
               Rounding round,
               LotSizing lotSizing) :
            waveNumber(waveNumber),
            percentage(percentage),
            orderCfg(orderConfig),
            orderTypes(orderTypes),
            algoType(algorithmType),
            prices(prices),
            raptor(raptor),
            round(round),
            lotSizing(lotSizing),
            waveSymbolStatus(BasketWave::PENDING)
    {
    };

    void onExecution(Execution *execution);

    void cancelWave();

    std::string getStatus();

    void executeWave(Basket *b);

    std::vector<Order> getOrders(OrderStatus orderStatus);

    std::vector<Order> getOrders()
    {
        return this->orders;
    }

    int getQuantityAfterLotAdjustment(const Basket *b, int totalQuantity);
};


#endif //UNTITLED1_BASKETWAVE_H


