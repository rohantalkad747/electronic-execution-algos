//
// Created by Rohan on 4/25/2020.
//

#include "../include/TWAPAlgorithm.h"
#include "../include/TWAPConfig.h"

double TWAPAlgorithm::getPrice()
{
    double numerator = 0.0;
    TWAPConfig *twapConfig = static_cast<TWAPConfig *>(this->algoConfig);
    long intervalStart = TimeUtils::getSecondsSinceMidnight();
    long tillIntervalEnd = intervalStart + twapConfig->getInterval();
    std::vector<double> histPrice = twapConfig->getHistPrice();
    for (int i = intervalStart; i < tillIntervalEnd; i++)
    {
        numerator += histPrice[i];
    }
    return numerator / (tillIntervalEnd - intervalStart);
}


