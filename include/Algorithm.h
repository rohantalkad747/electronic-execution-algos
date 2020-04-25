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

    Algorithm(const AlgoConfig &algoConfig, const SprayRouter &sprayRouter) : algoConfig(
            algoConfig), cancel(false), sprayRouter(sprayRouter)
    {}


    virtual void executeAlgo() = 0;

    bool cancelAlgo()
    {
        this->cancel = true;
    }

    const AlgoConfig &getAlgoConfig() const
    {
        return algoConfig;
    }

    void setAlgoConfig(AlgoConfig& config)
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
};
#endif //UNTITLED1_ALGORITHM_H
