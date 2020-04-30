//
// Created by Rohan on 4/29/2020.
//

#ifndef UNTITLED1_ORDERBOOKMANAGER_H
#define UNTITLED1_ORDERBOOKMANAGER_H


#include <functional>
#include <map>
#include "OrderBook.h"
#include "FillService.h"
#include "OrderSide.h"

/**
 * Th is the interface through which the venue interacts with its order books.
 */
class OrderBookManager
{
private:
    FillService fillService;
    std::map<std::string, std::tuple<OrderBook>> books;

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
    void takeLiquidity(OrderBook& book, Order& order);
    void acceptOrder();
    void dispatchToExecutionService(Node<PricePoint>* depth, Order& order, std::function<bool(PricePoint&)>& isCompatible);
};


#endif //UNTITLED1_ORDERBOOKMANAGER_H
