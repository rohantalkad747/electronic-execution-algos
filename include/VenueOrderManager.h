//
// Created by Rohan on 4/29/2020.
//

#ifndef UNTITLED1_VENUEORDERMANAGER_H
#define UNTITLED1_VENUEORDERMANAGER_H


#include <functional>
#include <map>
#include "OrderBook.h"
#include "ExecutionService.h"
#include "OrderSide.h"

/**
 * Th is the interface through which the venue interacts with its order books.
 */
class VenueOrderManager
{
private:
    Logger                                                log = *(new Logger("VenueOrderManager"));
    ExecutionService                                      executionService;
    std::map<std::string, std::map<OrderSide, OrderBook>> books;
    std::map<std::string, Order *>                        orderArena;
    std::map<std::string, double>                         fillTable;

    static std::function<bool(PricePoint &)> isCompatibleBuy(Order &o)
    {
        return [&](PricePoint &pp)
        {
            return o.getPrice() <= pp.getPrice();
        };
    }

    static std::function<bool(PricePoint &)> isCompatibleSell(Order &o)
    {
        return [&](PricePoint &pp)
        {
            return o.getPrice() >= pp.getPrice();
        };
    }

public:
    void acceptOrder(Order &order);

    void handleReplace(Order &order);

    void handleCancel(Order &order);

    void
    dispatchToExecutionService(Node<PricePoint> *depth, Order &order, std::function<bool(PricePoint &)> &isCompatible);
};


#endif //UNTITLED1_VENUEORDERMANAGER_H
