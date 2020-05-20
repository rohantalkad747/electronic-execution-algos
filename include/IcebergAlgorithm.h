//
// Created by Rohan on 4/27/2020.
//

#ifndef UNTITLED1_ICEBERGALGORITHM_H
#define UNTITLED1_ICEBERGALGORITHM_H

#include "./Algorithm.h"

class IcebergAlgorithm : public Algorithm {
public:
    using Algorithm::Algorithm;

    void executeAlgo();

    void triggerNextDisplay();

protected:
    double getPrice();

    int getLeavesQuantity();

    void init();

    double upper = -1;
    double lower = -1;
};


#endif //UNTITLED1_ICEBERGALGORITHM_H
