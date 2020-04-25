//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_TWAPALGORITHM_H
#define UNTITLED1_TWAPALGORITHM_H


#include "TimedAlgorithm.h"

class TWAPAlgorithm : public TimedAlgorithm
{
private:
    int getLeavesQuantity();
    double getPrice();
    int leavesPerOrder;
public:
    TWAPAlgorithm(int leavesPerOrder);
};


#endif //UNTITLED1_TWAPALGORITHM_H
