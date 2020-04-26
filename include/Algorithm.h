//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGORITHM_H
#define UNTITLED1_ALGORITHM_H

#include "AlgoConfig.h"
#include "SprayRouter.h"

class Algorithm
{
public:

    Algorithm(AlgoConfig *algoConfig, const SprayRouter &sprayRouter, const VenueManager &venueManager)
            : algoConfig(algoConfig), sprayRouter(sprayRouter), venueManager(venueManager), log(*(new Logger("Algorithm")))
    {}

    virtual void executeAlgo() = 0;

    void cancelAlgo()
    {
        this->cancel = true;
    }

    bool algoActive();

protected:
    virtual double getPrice() = 0;
    virtual int getLeavesQuantity() = 0;
    void sendToRouter();

    int sharesTraded;
    AlgoConfig* algoConfig;

protected:
    bool cancel;

    Logger log;
private:
    SprayRouter sprayRouter;
    VenueManager venueManager;
    Order getChildOrder();
};

#endif //UNTITLED1_ALGORITHM_H