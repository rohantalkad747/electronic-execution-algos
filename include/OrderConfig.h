//
// Created by Rohan Talkad on 2020-05-27.
//

#include "Order.h"
#include "RoutingConfig.h"

#ifndef UNTITLED1_ORDERCONFIG_H
#define UNTITLED1_ORDERCONFIG_H

#endif //UNTITLED1_ORDERCONFIG_H

class OrderConfig
{
protected:
public:

    virtual ~OrderConfig() {} // Make polymorphic

    Order &getOrder()
    {
        return order;
    }

    void setOrder(const Order &order)
    {
        OrderConfig::order = order;
    }

    RoutingConfig &getRoutingConfig()
    {
        return routingConfig;
    }

    void setRoutingConfig(const RoutingConfig &routingConfig)
    {
        OrderConfig::routingConfig = routingConfig;
    }

protected:
public:
    OrderConfig(const Order &order, const RoutingConfig &routingConfig) : order(order), routingConfig(routingConfig)
    {}

    OrderConfig(const RoutingConfig &routingConfig) : routingConfig(routingConfig)
    {}

protected:
    Order         order;
    RoutingConfig routingConfig;
};
