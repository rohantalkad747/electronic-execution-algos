//
// Created by Rohan on 4/26/2020.
//

#ifndef UNTITLED1_PARTICIPATEALGORITHM_H
#define UNTITLED1_PARTICIPATEALGORITHM_H

#include "TimedAlgorithm.h"

class ParticipateAlgorithm : public TimedAlgorithm
{
public:
    using TimedAlgorithm::TimedAlgorithm;
    int getLeavesQuantity();
    double getPrice();
};

#endif //UNTITLED1_PARTICIPATEALGORITHM_H
