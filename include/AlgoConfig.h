//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGOCONFIG_H
#define UNTITLED1_ALGOCONFIG_H


#include "OrderSide.h"
#include "Order.h"

class AlgoConfig
{
protected:
    OrderSide orderSide;
public:
    OrderSide getOrderSide() const
    {
        return orderSide;
    }

    void setOrderSide(OrderSide orderSide)
    {
        AlgoConfig::orderSide = orderSide;
    }

    const Order &getOrder() const
    {
        return order;
    }

    void setOrder(const Order &order)
    {
        AlgoConfig::order = order;
    }

protected:
    Order order;
public:
    AlgoConfig(OrderSide orderSide, const Order &order) : orderSide(orderSide), order(order)
    {}
};


#endif //UNTITLED1_ALGOCONFIG_H
