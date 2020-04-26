//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_TWAPCONFIG_H
#define UNTITLED1_TWAPCONFIG_H

#include <vector>
#include "TimingContext.h"

class TWAPConfig : public TimingContext
{
private:
    std::vector<double> histPrice;
public:
    const std::vector<double> &getHistPrice() const
    {
        return histPrice;
    }

    void setHistPrice(const std::vector<double> &histPrice)
    {
        TWAPConfig::histPrice = histPrice;
    }

public:
    TWAPConfig(const Order &order, long initialDelay, long startTime, long endTime, long interval,
               const std::vector<double> &histPrice, RoutingConfig routingType) : TimingContext(order, initialDelay, startTime, endTime,
                                                                                                interval, routingType), histPrice(histPrice)
    {
        std::cout << histPrice.size() << std::endl;
    }
};

#endif //UNTITLED1_TWAPCONFIG_H
