//
// Created by Rohan on 4/5/2020.
//

#include <chrono>
#include "../include/SerialRouter.h"

std::vector<long> getLatencyAdjustments(const std::vector<Venue> &venues);

void SerialRouter::route(const Order &order)
{
    const std::string &symbol = order.getSymbol();

    Log.info("... ROUTING ...");
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

    std::vector<long> adjustments = getLatencyAdjustments(venues);

    int curRouted = 0;
    for ( ; ; )
    {
        for ( int i = 0 ; i < venues.size(); i++ )
        {
            const auto& venue = venues[i];

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

            long time = std::chrono::system_clock::now().time_since_epoch().count() + adjustments[i];
            while (std::chrono::system_clock::now().time_since_epoch().count() <= time);
            VenueManager.sendOrder(venue, child);
        }
    }
}

std::vector<long> getLatencyAdjustments(const std::vector<Venue> &venues)
{
    std::vector<long> adjustments;
    int max = 0;

    for (const auto& venue : venues)
    {
        long latency = venue.getAvgLatency();
        if (latency > max)
        {
            max = latency;
        }
    }

    for (const auto & venue : venues)
    {
        long thisVenueLatency = venue.getAvgLatency();
        long adjustment = max - thisVenueLatency;
        adjustments.push_back(adjustment);
    }

    return adjustments;
}
