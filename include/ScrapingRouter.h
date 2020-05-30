//
// Created by Rohan Talkad on 2020-05-30.
//

#ifndef UNTITLED1_SCRAPINGROUTER_H
#define UNTITLED1_SCRAPINGROUTER_H

#include "OrderRouter.h"

class ScrapingRouter : public OrderRouter
{
public:
    ScrapingRouter(const OrderBook &orderBook) : orderBook(orderBook), log(*(new Logger("SprayRouter")))
    {
    }

    int route(Order &order)
    {
        liquidityAggregator.acceptOrder(order);
        return order.leaves();
    }

private:
    VenueOrderManager liquidityAggregator;
    Logger            log;
    OrderBook         orderBook;
};

#endif //UNTITLED1_SCRAPINGROUTER_H
