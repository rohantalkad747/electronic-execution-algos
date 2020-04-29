//
// Created by Rohan on 4/25/2020.
//

#include <future>
#include "../include/TimedAlgorithm.h"
#include <algorithm>
#include"../include/AntiGaming.h"

void TimedAlgorithm::executeAlgo()
{
    std::async(std::launch::async, [this]()
    {
        log.info("========= Booting algorithm ========= ");
        auto *timingContext = static_cast<TimingContext *> (this->algoConfig);
        int startTimeDifferential = std::max(0L, timingContext->getStartTime() - TimeUtils::getCurTimeEpoch());
        int sleepTime = startTimeDifferential + timingContext->getInitialDelay();
        if (sleepTime != 0)
        {
            std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
        }
        int interval = timingContext->getInterval();
        while (this->algoActive())
        {
            log.info("--- Algorithm active ... sending to router  ---");
            this->sendToRouter();
            long adjustedInterval = interval + AntiGaming::randomize(0, 2);
            std::this_thread::sleep_for(std::chrono::seconds(adjustedInterval));
        }
        log.info("Algorithm executed! " + std::to_string(this->sharesTraded) + "/" +
                 std::to_string(this->algoConfig->getOrder().getQuantity()) + " shares traded.");
    });
}

int TimedAlgorithm::getLeavesQuantity()
{
    if (leavesQuantity == -1)
    {
        leavesQuantity = (algoConfig->getOrder().getQuantity() /
                          (static_cast<TimingContext *> (this->algoConfig))->getInterval());
    }
    return leavesQuantity;
}
