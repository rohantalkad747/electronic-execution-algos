//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGOCONFIG_H
#define UNTITLED1_ALGOCONFIG_H


#include "OrderSide.h"
#include "Order.h"
#include "RoutingConfig.h"
#include "OrderConfig.h"

class AlgoConfig : public OrderConfig
{

public:
    AlgoConfig(const Order &order, const RoutingConfig &routingConfig, long startTime, long endTime) : OrderConfig(order, routingConfig),
                                                                                                       startTime(
                                                                                                               startTime),
                                                                                                       endTime(endTime)
    {}

public:
    AlgoConfig(const RoutingConfig &routingConfig, long startTime, long endTime) : OrderConfig(
            routingConfig),
                                                                                   startTime(
                                                                                           startTime),
                                                                                   endTime(endTime)
    {
    }


protected:
    long          startTime;
    long          endTime;
public:

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

};


#endif //UNTITLED1_ALGOCONFIG_H
