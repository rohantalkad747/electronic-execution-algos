//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGORITHM_H
#define UNTITLED1_ALGORITHM_H

#include "AlgoConfig.h"

class Algorithm
{
public:

    Algorithm(const AlgoConfig &algoConfig) : algoConfig(algoConfig), cancel(false)
    {}

    void executeAlgo();

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


    bool algoActive()
    {
        return !(this->cancel);
    }

protected:
    AlgoConfig algoConfig;
    bool cancel;
};
#endif //UNTITLED1_ALGORITHM_H
