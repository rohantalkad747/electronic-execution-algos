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


    Algorithm(const AlgoConfig &algoConfig, bool cancel, const SprayRouter &sprayRouter,
              const VenueManager &venueManager) : algoConfig(algoConfig), cancel(cancel), sprayRouter(sprayRouter),
                                                  venueManager(venueManager)
    {}

    virtual void executeAlgo() = 0;

    void cancelAlgo()
    {
        this->cancel = true;
    }

    const AlgoConfig &getAlgoConfig() const
    {
        return algoConfig;
    }

    void setAlgoConfig(AlgoConfig &config)
    {
        this->algoConfig = config;
    }

    bool algoActive();

protected:
    virtual double getPrice() = 0;

    virtual int getLeavesQuantity() = 0;

    void sendToRouter();

    AlgoConfig algoConfig;
    bool cancel;
private:
    SprayRouter sprayRouter;
    VenueManager venueManager;

    Order getChildOrder();
};

#endif //UNTITLED1_ALGORITHM_H
