//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_TIMEDALGORITHM_H
#define UNTITLED1_TIMEDALGORITHM_H


#include "Algorithm.h"
#include "TimingContext.h"

class TimedAlgorithm : public Algorithm
{
public:
    using Algorithm::Algorithm;

    virtual void executeAlgo();

protected:
    int getLeavesQuantity();

    int leavesQuantity = -1;

protected:
};


#endif //UNTITLED1_TIMEDALGORITHM_H
