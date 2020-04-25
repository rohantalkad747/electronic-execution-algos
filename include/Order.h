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

    int leaves() const
    {
        return quantity - cumulativeQuantity;
    }

    bool isTerminal() const
    {
        return leaves() == 0;
    }

    OrderSide getSide() const
    {
        return side;
    }

    const std::string &getSymbol() const
    {
        return symbol;
    }

    int getQuantity() const
    {
        return quantity;
    }

    OrderType getOrderType() const
    {
        return orderType;
    }

    double getPrice() const
    {
        return price;
    }

    TimeInForce getTimeInForce() const
    {
        return timeInForce;
    }

    int getMinQuantity() const
    {
        return minQuantity;
    }

    int getCumulativeQuantity() const
    {
        return cumulativeQuantity;
    }

    OrderStatus getOrderStatus() const
    {
        return orderStatus;
    }

    const std::string &getAccount() const
    {
        return account;
    }

    const std::string &getClOrdId() const
    {
        return ClOrdID;
    }

    const std::string &getMsgType() const
    {
        return msgType;
    }

    const std::string &getText() const
    {
        return text;
    }

    const std::string &getTransactTime() const
    {
        return transactTime;
    }

    const std::string &getTradeDate() const
    {
        return tradeDate;
    }

    const std::string &getExDestination() const
    {
        return exDestination;
    }

    const std::string &getMinQty() const
    {
        return minQty;
    }

    void setQuantity(int newQuantity)
    {
        quantity = newQuantity;
    }

private:
    OrderSide side;
    std::string symbol;
    int quantity;
    OrderType orderType;
    double price;
public:
    void setPrice(double price)
    {
        Order::price = price;
    }

private:
    TimeInForce timeInForce;
    int minQuantity;
    int cumulativeQuantity;
    OrderStatus orderStatus;
    // Other FIX fields
    std::string account;
    std::string ClOrdID;
    std::string msgType;
    std::string text;
    std::string transactTime;
    std::string tradeDate;
    std::string exDestination;
    std::string minQty;
};


#endif //UNTITLED1_ORDER_H
