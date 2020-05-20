//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ORDERROUTER_H
#define UNTITLED1_ORDERROUTER_H

#include "Order.h"
#include "VenueManager.h"

class OrderRouter
{
protected:
    bool cancelled;
public:
    /**
     * @return the number of shares routed.
     */
    virtual int route(const Order &order) = 0;

    void cancel()
    {
        this->cancelled = true;
    }
};

#endif //UNTITLED1_ORDERROUTER_H
