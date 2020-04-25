//
// Created by Rohan on 4/4/2020.
//

#include "VenueManager.h"
#include "Order.h"
#include "Logger.h"

#ifndef UNTITLED1_SERIALROUTER_H
#define UNTITLED1_SERIALROUTER_H

#endif //UNTITLED1_SERIALROUTER_H

class SprayRouter
{
public:
    SprayRouter(const VenueManager &vm) : VenueManager(vm), Log("SprayRouter")
    {
    }

    void route(const Order &order);

private:
    VenueManager VenueManager;
    Logger Log;
};



