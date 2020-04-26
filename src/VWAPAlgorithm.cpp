//
// Created by Rohan on 4/25/2020.
//

#include "../include/VWAPAlgorithm.h"
#include "../include/VWAPConfig.h"
#include "../include/TimeUtils.h"

double VWAPAlgorithm::getPrice()
{
    VWAPConfig* vwapConfig = (VWAPConfig *)(this->algoConfig);
    std::vector<int> histVol = vwapConfig->getHistVolume();
    std::vector<double> histPrice = vwapConfig->getHistPrice();
    long intervalStart = TimeUtils::getSecondsSinceMidnight();
    long tillIntervalEnd = intervalStart + vwapConfig->getInterval();
    double num = 0, den = 0;
    for (int i = intervalStart; i < tillIntervalEnd; i++)
    {
        num += histVol[i] * histPrice[i];
        den += histPrice[i];
    }
    return std::min(this->algoConfig->getOrder().getPrice(), num / den);
}
