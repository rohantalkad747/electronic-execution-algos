//
// Created by Rohan on 4/25/2020.
//

#include <future>
#include "../include/TimedAlgorithm.h"
#include "../include/TimeUtils.h"

void TimedAlgorithm::executeAlgo()
{
    auto ftr = std::async(std::launch::async, [this]()
    {
        TimingContext timingContext = static_cast<TimingContext &>(this->algoConfig);
        int delay = timingContext.getInitialDelay();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        int interval = timingContext.getInterval();
        while (this->algoActive())
        {
            this->sendToRouter();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    });
}

int TimedAlgorithm::getLeavesQuantity()
{
    if (leavesQuantity == 0)
    {
        leavesQuantity = (algoConfig.getOrder().getQuantity() / (static_cast<TimingContext &>(this->algoConfig)).getInterval());
    }
    return leavesQuantity;
}