//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGORITHM_H
#define UNTITLED1_ALGORITHM_H

#include "AlgoConfig.h"

class Algorithm
{
public:
    void executeAlgo();
    bool cancelAlgo();
    void setAlgoConfig(AlgoConfig& config)
    {
        this->algoConfig = config;
    }
private:
    AlgoConfig algoConfig;
};
#endif //UNTITLED1_ALGORITHM_H
