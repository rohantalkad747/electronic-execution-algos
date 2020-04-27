//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGOCONFIG_H
#define UNTITLED1_ALGOCONFIG_H


#include "OrderSide.h"
#include "Order.h"
#include "RoutingConfig.h"

class AlgoConfig
{
public:
    virtual ~AlgoConfig()
    {}

    const Order &getOrder() const
    {
        return order;
    }

    void setOrder(const Order &order)
    {
        AlgoConfig::order = order;
    }

public:
    AlgoConfig(const Order &order, const RoutingConfig &routingConfig, long startTime, long endTime) : order(order),
                                                                                                       routingConfig(
                                                                                                               routingConfig),
                                                                                                       startTime(
                                                                                                               startTime),
                                                                                                       endTime(endTime)
    {}

protected:
    Order order;
    RoutingConfig routingConfig;
    long startTime;
    long endTime;
public:
    void setRoutingConfig(const RoutingConfig &routingConfig)
    {
        AlgoConfig::routingConfig = routingConfig;
    }

    long getStartTime() const
    {
        return startTime;
    }

    void setStartTime(long startTime)
    {
        AlgoConfig::startTime = startTime;
    }

    long getEndTime() const
    {
        return endTime;
    }

    void setEndTime(long endTime)
    {
        AlgoConfig::endTime = endTime;
    }

public:
    const RoutingConfig &getRoutingConfig() const
    {
        return routingConfig;
    }
};


#endif //UNTITLED1_ALGOCONFIG_H
