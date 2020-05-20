//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_TWAPALGORITHM_H
#define UNTITLED1_TWAPALGORITHM_H


#include "TimedAlgorithm.h"

class TWAPAlgorithm : public TimedAlgorithm {
public:
    using TimedAlgorithm::TimedAlgorithm;
protected:
    double getPrice();
};


#endif //UNTITLED1_TWAPALGORITHM_H
