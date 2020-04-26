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
    virtual ~AlgoConfig() { }
    const Order &getOrder() const
    {
        return order;
    }

    void setOrder(const Order &order)
    {
        AlgoConfig::order = order;
    }

public:
    AlgoConfig(const Order &order, RoutingConfig routingConfig)
            : order(order), routingConfig(routingConfig)
    {}
protected:
    Order order;
    RoutingConfig routingConfig;
public:
    const RoutingConfig &getRoutingConfig() const
    {
        return routingConfig;
    }
};


#endif //UNTITLED1_ALGOCONFIG_H
