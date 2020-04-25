//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ORDERROUTER_H
#define UNTITLED1_ORDERROUTER_H

#include "Order.h"
#include "VenueManager.h"

class OrderRouter
{
public:
    virtual void route(Order &order) = 0;
};
#endif //UNTITLED1_ORDERROUTER_H
