//
// Created by Rohan on 4/4/2020.
//

#include "VenueManager.h"
#include "Order.h"
#include "Logger.h"
#include "OrderRouter.h"

#ifndef UNTITLED1_SERIALROUTER_H
#define UNTITLED1_SERIALROUTER_H

class SprayRouter : public OrderRouter
{
public:
    SprayRouter(const VenueManager &venueManager) : VenueManager(venueManager), Log(*(new Logger("SprayRouter")))
    {
    }

    int route(const Order &order);

private:
    VenueManager VenueManager;
private:
    Logger Log;
};

#endif //UNTITLED1_SERIALROUTER_H




