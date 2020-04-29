//
// Created by Rohan on 4/29/2020.
//

#ifndef UNTITLED1_TAKELIQUIDITYMANAGER_H
#define UNTITLED1_TAKELIQUIDITYMANAGER_H


#include <functional>
#include "../include/OrderBook.h"
#include "ExecutionService.h"
#include "../include/OrderSide.h"

class TakeLiquidityManager
{
private:
    static std::function<bool(PricePoint&)> isCompatibleBuy(Order& o)
    {
        return [&](PricePoint& pp)
        {
            return o.getPrice() <= pp.getPrice();
        };
    }

    static std::function<bool(PricePoint&)> isCompatibleSell(Order& o)
    {
        return [&](PricePoint& pp)
        {
            return o.getPrice() >= pp.getPrice();
        };
    }

public:
    double getTakerFees(Order& order) const;

    void takeLiquidity(OrderBook& book, Order& order);

    void dispatchToExecutionService(Node<PricePoint>* depth, Order& order, std::function<bool(PricePoint&)>& isCompatible);
private:
    int takerFee;
    ExecutionService executionService;
};


#endif //UNTITLED1_TAKELIQUIDITYMANAGER_H
