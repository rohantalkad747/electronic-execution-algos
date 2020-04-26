//
// Created by Rohan on 4/25/2020.
//

#include <future>
#include "../include/TimedAlgorithm.h"
#include "../include/TimeUtils.h"
#include <algorithm>

void TimedAlgorithm::executeAlgo()
{
    std::async(std::launch::async, [this]()
    {
        log.info("Booting algo ...");
        TimingContext* timingContext = ( TimingContext * ) (this->algoConfig);
        int startTimeDifferential = std::max(0L, timingContext->getStartTime() - TimeUtils::getCurTimeEpoch());
        int sleepTime = startTimeDifferential + timingContext->getInitialDelay();
        log.info("Sleeping for " + log.to_string<long>(sleepTime));
        if (sleepTime != 0)
        {
            std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
        }
        int interval = timingContext->getInterval();
        while (this->algoActive())
        {
            this->sendToRouter();
            std::this_thread::sleep_for(std::chrono::seconds(interval));
        }
        log.info("Algorithm fully executed! ");
    });
}

int TimedAlgorithm::getLeavesQuantity()
{
    if (leavesQuantity == -1)
    {
        leavesQuantity = (algoConfig->getOrder().getQuantity() / ((TimingContext *)(this->algoConfig))->getInterval());
    }
    return leavesQuantity;
}
