//
// Created by Rohan on 4/4/2020.
//

#ifndef UNTITLED1_ORDER_H
#define UNTITLED1_ORDER_H


#include <string>
#include "OrderSide.h"
#include "OrderType.h"
#include "TimeInForce.h"
#include "OrderStatus.h"

class Order
{
public:
    explicit Order(OrderSide side, std::string symbol, int quantity, OrderType orderType, double price,
                   TimeInForce timeInForce) :
            side(side), symbol(symbol), quantity(quantity), orderType(orderType), price(price), timeInForce(timeInForce)
    {
        minQuantity = quantity;
        cumulativeQuantity = 0;
        orderStatus = OrderStatus::NEW;
    };

    Order(const Order &o) :
            side(o.side),
            symbol(o.symbol),
            quantity(o.quantity),
            orderType(o.orderType),
            price(o.price),
            timeInForce(o.timeInForce)
    {
        minQuantity = o.quantity;
        cumulativeQuantity = o.cumulativeQuantity;
        orderStatus = OrderStatus::NEW;
    }

    int leaves()
    {
        return quantity - cumulativeQuantity;
    }

    bool isTerminal()
    {
        return leaves() == 0;
    }

private:
    OrderSide side;
    std::string symbol;
    int quantity;
    OrderType orderType;
    double price;
    TimeInForce timeInForce;
    int minQuantity;
    int cumulativeQuantity;
    OrderStatus orderStatus;
    // Other FIX fields
    std::string account;
    std::string clOrdID;
    std::string msgType;
    std::string text;
    std::string transactTime;
    std::string tradeDate;
    std::string exDestination;
    std::string minQty;

};


#endif //UNTITLED1_ORDER_H
