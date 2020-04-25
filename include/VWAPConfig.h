//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_VWAPCONFIG_H
#define UNTITLED1_VWAPCONFIG_H

#include <vector>
#include "TimingContext.h"

class VWAPConfig : public TimingContext
{
public:
    VWAPConfig(OrderSide orderSide, const Order &order, long initialDelay, long startTime, long endTime, long interval,
               const std::vector<double> &histPrice, const std::vector<int> &histVolume) : TimingContext(orderSide,
                                                                                                            order,
                                                                                                            initialDelay,
                                                                                                            startTime,
                                                                                                            endTime,
                                                                                                            interval),
                                                                                              histPrice(histPrice),
                                                                                              histVolume(histVolume)
    {}

    VWAPConfig(OrderSide orderSide, const Order &order, long initialDelay, long startTime, long endTime, long interval,
               const std::vector<double> &histPrice) : TimingContext(orderSide, order, initialDelay, startTime, endTime,
                                                                     interval), histPrice(histPrice)
    {}

private:
    std::vector<int> histVolume;
    std::vector<double> histPrice;
public:
    const std::vector<double> &getHistPrice() const
    {
        return histPrice;
    }

    void setHistPrice(const std::vector<double> &histPrice)
    {
        VWAPConfig::histPrice = histPrice;
    }

public:
    const std::vector<int> &getHistVolume() const
    {
        return histVolume;
    }

    void setHistVolume(const std::vector<int> &histVolume)
    {
        VWAPConfig::histVolume = histVolume;
    }

};

#endif //UNTITLED1_VWAPCONFIG_H
