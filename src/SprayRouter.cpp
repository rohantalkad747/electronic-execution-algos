//
// Created by Rohan on 4/5/2020.
//
#include <chrono>
#include <thread>
#include "../include/SprayRouter.h"
#include "../include/CountDownLatch.h"

std::vector<long> getLatencyAdjustments(const std::vector<Venue> &venues);

int SprayRouter::route(Order &order)
{
    Log.debug("-------------- BEGIN ROUTING ------------------- ");
    const std::string &symbol = order.getSymbol();
    if (order.isTerminal())
    {
        Log.error("Order is terminal!");
        return 0;
    }
    int leaves = order.leaves();
    Log.info("leavesQty: ", leaves);
    if (leaves == 0)
    {
        Log.error("order is fully filled.");
        return 0;
    }
    std::vector<Venue> venues = VenueManager.venues(symbol);
    if (venues.empty())
    {
        Log.error("No venues for symbol: ", symbol);
        return 0;
    }
    std::vector<long>                                  adjustments = getLatencyAdjustments(venues);
    int                                                curRouted   = 0;
    std::vector<std::function<void(CountDownLatch *)>> tasks;
    for (int                                           i           = 0;
         i < venues.size() && curRouted < order.getQuantity() && !this->cancelled; i++)
    {
        auto   &venue               = venues[i];
        double executionProbability = venue.getExecutionProbability();
        int    childQuantity        = std::min(order.getQuantity() - curRouted,
                                               static_cast<int>(leaves * executionProbability));
        curRouted += childQuantity;
        Order child(order);
        child.setQuantity(childQuantity);
        long adjustment = adjustments[i];
        tasks.emplace_back([adjustment, &venue, &child](CountDownLatch *latch)
                           {
                               if (adjustment != 0)
                               {
                                   std::this_thread::sleep_for(std::chrono::milliseconds(adjustment));
                               }
                               venue.acceptOrder(child);
                               latch->countDown();
                           });
        std::cout << "v: " << venue << ", prob:" << executionProbability << ", child_qty: " << childQuantity
                  << ", price: " << order.getPrice()
                  << std::endl;
    }
    if (this->cancelled)
    {
        return 0;
    }
    auto      latch = std::make_unique<CountDownLatch *>(new CountDownLatch(tasks.size()));
    for (auto &task : tasks)
    {
        std::thread thread_obj(task, *latch);
        thread_obj.detach();
    }
    (*latch)->await();
    Log.debug("-------------- DONE ROUTING ------------------- ");
    return curRouted;
}


std::vector<long> getLatencyAdjustments(const std::vector<Venue> &venues)
{
    std::vector<long> adjustments;
    int               max = 0;
    for (const auto   &venue : venues)
    {
        long latency = venue.getAvgLatency();
        if (latency > max)
        {
            max = latency;
        }
    }
    for (const auto   &venue : venues)
    {
        long thisVenueLatency = venue.getAvgLatency();
        long adjustment       = max - thisVenueLatency;
        adjustments.push_back(adjustment);
    }

    return adjustments;
}