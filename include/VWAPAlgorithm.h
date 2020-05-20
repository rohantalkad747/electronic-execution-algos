//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_VWAPALGORITHM_H
#define UNTITLED1_VWAPALGORITHM_H

#include "TimedAlgorithm.h"

class VWAPAlgorithm : public TimedAlgorithm {
public:
    using TimedAlgorithm::TimedAlgorithm;
private:
    double getPrice();

public:
    VWAPAlgorithm();
};

#endif //UNTITLED1_VWAPALGORITHM_H
