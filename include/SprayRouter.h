//
// Created by Rohan on 4/4/2020.
//

#include "VenueManager.h"
#include "Order.h"
#include "Logger.h"
#include "OrderRouter.h"

#ifndef UNTITLED1_SERIALROUTER_H
#define UNTITLED1_SERIALROUTER_H

#endif //UNTITLED1_SERIALROUTER_H

class SprayRouter : public OrderRouter
{
public:
    SprayRouter(const VenueManager &vm, const Logger &log);

    void route(const Order &order);
private:
    VenueManager venueManager;
    Logger Log;
};



