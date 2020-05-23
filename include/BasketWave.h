//
// Created by Rohan Talkad on 2020-05-21.
//

#ifndef UNTITLED1_BASKETWAVE_H
#define UNTITLED1_BASKETWAVE_H


#include "Algorithm.h"
#include "Basket.h"
#include "AlgorithmType.h"
#include "LotSizing.h"
#include "Round.h"

template<typename A>
class BasketWave
{
private:
    static const int    PENDING          = 1;
    static const int    SENT             = 2;
    static const int    EXECUTED         = 4;
    static const int    PARTIAL_EX       = 8;
    static const int    CANCELLED        = 16;
    double              waveNumber;
    double              percentage;
    RoutingConfig       *routingConfig;
    Raptor              *raptor;
    A                   *algoConfig;
    AlgorithmType       *algoType;
    std::vector<double> prices;
    std::vector<Order>  orders;
    std::vector<OrderType> orderTypes;
    LotSizing           lotSizing;
    Round               round;
    unsigned int        waveSymbolStatus = 0;
    std::atomic<int>    traded           = 0;
    int                 total            = 0;
    long                timestamp        = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::vector<Order> splitBySecurity(Basket *b);

    std::mutex mtx_;

    AlgoConfig *getAlgorithmConfig()
    {
        return dynamic_cast<AlgoConfig *>(algoConfig);
    }

    Order *findOrder(const std::string &orderId);

public:

    /**
     * @param waveNumber
     * @param percentage
     * @param algoConfig
     * @param prices
     * @param orderTypes
     * @param raptor
     */
    BasketWave(double waveNumber, double percentage,
               A *algoConfig,
               const std::vector<double> &prices,
               const std::vector<OrderType> orderTypes,
               Raptor* raptor,
               Round round,
               LotSizing lotSizing) :
         waveNumber(waveNumber),
         percentage(percentage),
         algoConfig(algoConfig),
         orderTypes(orderTypes),
         prices(prices),
         raptor(raptor),
         round(round),
         lotSizing(lotSizing)
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


