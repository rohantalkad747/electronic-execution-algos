//
// Created by Rohan on 4/26/2020.
//

#include <numeric>
#include "../include/ParticipateAlgorithm.h"
#include "../include/ParticipateConfig.h"

int ParticipateAlgorithm::getLeavesQuantity()
{
    ParticipateConfig *povConfig = static_cast<ParticipateConfig *>( this->algoConfig);
    long intervalStart = TimeUtils::getSecondsSinceMidnight();
    long tillIntervalEnd = intervalStart + povConfig->getInterval();
    int totalVolume = 0;
    std::vector<int> histVol = povConfig->getHistVolume();
    for (int i = intervalStart; i < tillIntervalEnd; i++)
    {
        totalVolume += histVol[i];
    }
    std::cout << "Total volume " << totalVolume << std::endl;
    return std::min((int) (povConfig->getOrder().getQuantity() - this->sharesTraded),
                    (int) (totalVolume * povConfig->getParticipation()));
}

double ParticipateAlgorithm::getPrice()
{
    return this->algoConfig->getOrder().getPrice();
}
