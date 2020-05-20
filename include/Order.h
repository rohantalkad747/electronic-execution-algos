//
// Created by Rohan on 4/4/2020.
//

#ifndef UNTITLED1_ORDER_H
#define UNTITLED1_ORDER_H


#include <string>
#include <mutex>
#include "OrderSide.h"
#include "OrderType.h"
#include "TimeInForce.h"
#include "OrderStatus.h"
#include "LiquidityIndicator.h"

class Order {
public:
    explicit Order(OrderSide side, std::string symbol, int quantity, OrderType orderType, double price,
                   TimeInForce timeInForce) :
            side(side), symbol(symbol), quantity(quantity), orderType(orderType), price(price),
            timeInForce(timeInForce) {
        minQuantity = quantity;
        cumulativeQuantity = 0;
        orderStatus = OrderStatus::NEW;
    };

    explicit Order(OrderSide side, std::string symbol, int quantity, OrderType orderType, double price,
                   TimeInForce timeInForce, LiquidityIndicator liquidityIndicator) :
            side(side), symbol(symbol), quantity(quantity), orderType(orderType), price(price),
            timeInForce(timeInForce), liquidityIndicator(liquidityIndicator) {
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
            timeInForce(o.timeInForce) {
        minQuantity = o.quantity;
        cumulativeQuantity = o.cumulativeQuantity;
        orderStatus = OrderStatus::NEW;
    }

    int leaves() const {
        return quantity - cumulativeQuantity;
    }

    bool isTerminal() const {
        return leaves() == 0;
    }

    OrderSide getSide() const {
        return side;
    }

    const std::string &getSymbol() const {
        return symbol;
    }

    int getQuantity() const {
        return quantity;
    }

    OrderType getOrderType() const {
        return orderType;
    }

    double getPrice() const {
        return price;
    }

    TimeInForce getTimeInForce() const {
        return timeInForce;
    }

    int getMinQuantity() const {
        return minQuantity;
    }

    int getCumulativeQuantity() const {
        return cumulativeQuantity;
    }

    OrderStatus getOrderStatus() const {
        return orderStatus;
    }

    const std::string &getAccount() const {
        return account;
    }

    const std::string &getClOrdId() const {
        return ClOrdID;
    }

    const std::string &getMsgType() const {
        return msgType;
    }

    const std::string &getText() const {
        return text;
    }

    const std::string &getTransactTime() const {
        return transactTime;
    }

    const std::string &getTradeDate() const {
        return tradeDate;
    }

    const std::string &getExDestination() const {
        return exDestination;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

private:
    OrderSide side;
    std::string symbol;
    int quantity;
    OrderType orderType;
    double price;
public:
    void setPrice(double price) {
        Order::price = price;
    }

private:
    TimeInForce timeInForce;
    int minQuantity;
    int cumulativeQuantity;
    OrderStatus orderStatus;
public:
    void setSide(OrderSide side) {
        Order::side = side;
    }

    void setSymbol(const std::string &symbol) {
        Order::symbol = symbol;
    }

    void setOrderType(OrderType orderType) {
        Order::orderType = orderType;
    }

    void setTimeInForce(TimeInForce timeInForce) {
        Order::timeInForce = timeInForce;
    }

    void setMinQuantity(int minQuantity) {
        Order::minQuantity = minQuantity;
    }

    void setCumulativeQuantity(int cumulativeQuantity) {
        Order::cumulativeQuantity = cumulativeQuantity;
    }

    void setOrderStatus(OrderStatus orderStatus) {
        Order::orderStatus = orderStatus;
    }

    void setAccount(const std::string &account) {
        Order::account = account;
    }

    void setClOrdId(const std::string &clOrdId) {
        ClOrdID = clOrdId;
    }

    void setMsgType(const std::string &msgType) {
        Order::msgType = msgType;
    }

    void setText(const std::string &text) {
        Order::text = text;
    }

    void setTransactTime(const std::string &transactTime) {
        Order::transactTime = transactTime;
    }

    void setTradeDate(const std::string &tradeDate) {
        Order::tradeDate = tradeDate;
    }

    void setExDestination(const std::string &exDestination) {
        Order::exDestination = exDestination;
    }

    void setLiquidityIndicator(LiquidityIndicator liquidityIndicator) {
        Order::liquidityIndicator = liquidityIndicator;
    }

    void setMtx(std::mutex *mtx) {
        mtx_ = mtx;
    }

private:
    // Other FIX fields
    std::string account;
    std::string ClOrdID;
    std::string msgType;
    std::string text;
    std::string transactTime;
    std::string tradeDate;
    std::string exDestination;
    LiquidityIndicator liquidityIndicator;
    std::mutex *mtx_ = new std::mutex();
public:
    LiquidityIndicator getLiquidityIndicator() const {
        return liquidityIndicator;
    }

    std::mutex *getMtx() const {
        return mtx_;
    }
};


#endif //UNTITLED1_ORDER_H
