//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_TIMINGCONTEXT_H
#define UNTITLED1_TIMINGCONTEXT_H

#include "AlgoConfig.h"

class TimingContext : public AlgoConfig
{
public:
    TimingContext(OrderSide orderSide, const Order &order, long initialDelay, long startTime, long endTime,
                  long interval) : AlgoConfig(orderSide, order), initialDelay(initialDelay), startTime(startTime),
                                   endTime(endTime), interval(interval)
    {}

private:
    long initialDelay;
    long startTime;
public:
    long getInitialDelay() const
    {
        return initialDelay;
    }

    void setInitialDelay(long initialDelay)
    {
        TimingContext::initialDelay = initialDelay;
    }

    long getStartTime() const
    {
        return startTime;
    }

    void setStartTime(long startTime)
    {
        TimingContext::startTime = startTime;
    }

    long getEndTime() const
    {
        return endTime;
    }

    void setEndTime(long endTime)
    {
        TimingContext::endTime = endTime;
    }

    long getInterval() const
    {
        return interval;
    }

    void setInterval(long interval)
    {
        TimingContext::interval = interval;
    }

private:
    long endTime;
    long interval;
};
#endif //UNTITLED1_TIMINGCONTEXT_H
