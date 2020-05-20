//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_TIMINGCONTEXT_H
#define UNTITLED1_TIMINGCONTEXT_H

#include "AlgoConfig.h"

class TimingContext : public AlgoConfig {
public:
    TimingContext(const Order &order, const RoutingConfig &routingConfig, long startTime, long endTime,
                  long initialDelay, long interval) : AlgoConfig(order, routingConfig, startTime, endTime),
                                                      initialDelay(initialDelay), interval(interval) {}

private:
    long initialDelay;
public:
    long getInitialDelay() const {
        return initialDelay;
    }

    void setInitialDelay(long initialDelay) {
        TimingContext::initialDelay = initialDelay;
    }

    long getInterval() const {
        return interval;
    }

    void setInterval(long interval) {
        TimingContext::interval = interval;
    }

private:
    long interval;
};

#endif //UNTITLED1_TIMINGCONTEXT_H
