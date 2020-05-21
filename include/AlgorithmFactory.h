//
// Created by Rohan Talkad on 2020-05-21.
//

#ifndef UNTITLED1_ALGORITHMFACTORY_H
#define UNTITLED1_ALGORITHMFACTORY_H

#include "Algorithm.h"
#include "AlgorithmType.h"

class AlgorithmFactory
{
public:
    static Algorithm& getInstance(AlgorithmType& type, Raptor &raptor, AlgoConfig& cfg);
};

#endif //UNTITLED1_ALGORITHMFACTORY_H
