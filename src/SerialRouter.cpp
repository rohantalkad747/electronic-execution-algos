//
// Created by Rohan on 4/5/2020.
//

#include "../include/SerialRouter.h"


void SerialRouter::route(const Order &order)
{
    const std::string &symbol = order.getSymbol();
    Log.info("routing ...");
    if (order.isTerminal())
    {
        Log.error("Order is terminal!");
        return;
    }
    int leaves = order.leaves();
    Log.info("leavesQty: ", leaves);
    if (leaves == 0)
    {
        Log.error("order is fully filled.");
        return;
    }
    std::vector<Venue> venues = VenueManager.venues(symbol);
    if (venues.empty())
    {
        Log.error("No venues for symbol: ", symbol);
        return;
    }
    int curRouted = 0;
    for ( ; ; )
    {
        for (const auto &venue : venues)
        {
            double executionProbability = venue.getExecutionProbability();
            int childQuantity = static_cast<int>(leaves * executionProbability);
            if (curRouted + childQuantity >= order.getQuantity())
            {
                Log.error("Routed all shares ", symbol);
                return;
            }
            curRouted += childQuantity;
            std::cout << "v: " << venue << ", prob:" << executionProbability << ", child_qty: " << childQuantity << std::endl;
            Order child(order);
            child.setQuantity(childQuantity);
            VenueManager.sendOrder(venue, child);
        }
    }
}