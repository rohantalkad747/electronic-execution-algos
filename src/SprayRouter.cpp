//
// Created by Rohan on 4/5/2020.
//

#include <chrono>
#include <thread>
#include "../include/SprayRouter.h"
#include "../include/CountDownLatch.h"


std::vector<long> getLatencyAdjustments(const std::vector<Venue> &venues);

void SprayRouter::route(const Order &order)
{
    const std::string &symbol = order.getSymbol();
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
    for (;;)
    {
        std::vector<std::function<void(CountDownLatch*)>> tasks;
        for (int i = 0; i < venues.size(); i++)
        {
            auto &venue = venues[i];
            double executionProbability = venue.getExecutionProbability();
            int childQuantity = std::min(order.getQuantity() - curRouted, static_cast<int>(leaves * executionProbability));
            curRouted += childQuantity;
            Order child(order);
            child.setQuantity(childQuantity);
            long adjustment = adjustments[i];
            tasks.push_back([&](CountDownLatch* latch){
                std::cout << "Executing asynchronously!" << std::endl;
                std::cout << adjustment << std::endl;
                std::cout << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(adjustment));
                VenueManager.sendOrder(venue, child);
                latch->countDown();
            });
            std::cout << "v: " << venue << ", prob:" << executionProbability << ", child_qty: " << childQuantity << ", price: " << order.getPrice()
                      << std::endl;
            if (curRouted == order.getQuantity())
            {
                Log.info("Routed all shares ", symbol);
                return;
            }
        }
        CountDownLatch* latch = new CountDownLatch(tasks.size());
        for (auto& task : tasks)
        {
            std::thread thread_obj(task, latch);
            thread_obj.detach();
        }
        latch->await();
    }
}


std::vector<long> getLatencyAdjustments(const std::vector<Venue> &venues)
{
    std::vector<long> adjustments;
    int max = 0;
    for (const auto &venue : venues)
    {
        long latency = venue.getAvgLatency();
        if (latency > max)
        {
            max = latency;
        }
    }
    for (const auto &venue : venues)
    {
        long thisVenueLatency = venue.getAvgLatency();
        long adjustment = max - thisVenueLatency;
        adjustments.push_back(adjustment);
    }

    return adjustments;
}