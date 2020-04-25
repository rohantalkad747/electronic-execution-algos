//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_VWAPCONFIG_H
#define UNTITLED1_VWAPCONFIG_H

#include <vector>
#include "TimingContext.h"

class VWAPConfig: public TimingContext
{
private:
    std::vector<double> histPrice;
public:
    VWAPConfig(OrderSide orderSide, const Order &order, long initialDelay, long startTime, long endTime, long interval,
               const std::vector<double> &histPrice, const std::vector<double> &histVolume) : TimingContext(orderSide,
                                                                                                            order,
                                                                                                            initialDelay,
                                                                                                            startTime,
                                                                                                            endTime,
                                                                                                            interval),
                                                                                              histPrice(histPrice),
                                                                                              histVolume(histVolume)
    {}

private:
    std::vector<double> histVolume;
public:
    const std::vector<double> &getHistVolume() const
    {
        return histVolume;
    }

    void setHistVolume(const std::vector<double> &histVolume)
    {
        VWAPConfig::histVolume = histVolume;
    }

};
#endif //UNTITLED1_VWAPCONFIG_H
