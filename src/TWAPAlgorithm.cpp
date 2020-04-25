//
// Created by Rohan on 4/25/2020.
//

#include "../include/TWAPAlgorithm.h"
#include "../include/TWAPConfig.h"
#include "../include/TimeUtils.h"

double TWAPAlgorithm::getPrice() {
    double twap = 0.0;
    TWAPConfig twapConfig = static_cast<TWAPConfig&>(this->algoConfig);
    long intervalStart = TimeUtils::getCurTimeEpochMs();
    int tillIntervalEnd = intervalStart + twapConfig.getInterval();
    std::vector<double> histPrice = twapConfig.getHistPrice();
    for (int i = intervalStart; i < tillIntervalEnd; i++)
    {
        twap += histPrice[i];
    }
    return twap / histPrice.size();
}

int TWAPAlgorithm::getLeavesQuantity() {
    if (leavesPerOrder == 0)
    {
        leavesPerOrder = (int) (algoConfig.getOrder().getQuantity() / (static_cast<TWAPConfig&>(this->algoConfig)).getInterval());
    }
    return leavesPerOrder;
}
