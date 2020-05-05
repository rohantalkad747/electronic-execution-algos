//
// Created by Rohan on 4/25/2020.
//

#include <future>
#include "../include/TimedAlgorithm.h"
#include"../include/AntiGaming.h"

void TimedAlgorithm::executeAlgo()
{
    std::async(std::launch::async, [this]()
    {
        log.info("========= Booting algorithm ========= ");
        auto *timingContext = dynamic_cast<TimingContext *> (this->algoConfig);
        int startTimeDifferential = std::max(0L, timingContext->getStartTime() - TimeUtils::getCurTimeEpoch());
        int sleepTime = startTimeDifferential + timingContext->getInitialDelay();
        if (sleepTime != 0)
        {
            std::unique_lock<std::mutex> lk(mtx_);
            this->schedGuard_.wait_for(lk, std::chrono::duration_cast<std::chrono::seconds>(std::chrono::seconds(sleepTime)), [this]
            {
                return this->cancel;
            });
            if (this->cancel)
            {
                return;
            }
        }
        int interval = timingContext->getInterval();
        for ( ; ; )
        {
            std::unique_lock<std::mutex> lk(mtx_);
           if (!(this->cancel))
           {
               log.info("--- Algorithm active ... sending to router  ---");
               this->sendToRouter();
               if (!(this->algoActive()))
               {
                   break;
               }
               long adjustedInterval = interval + AntiGaming::randomize(0, 2);
               this->schedGuard_.wait_for(lk, std::chrono::duration_cast<std::chrono::seconds>(std::chrono::seconds(adjustedInterval)), [this]
               {
                   return this->cancel;
               });
               if (this->cancel)
               {
                   break;
               }
           }
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
                          (dynamic_cast<TimingContext *> (this->algoConfig))->getInterval());
    }
    return leavesQuantity;
}
