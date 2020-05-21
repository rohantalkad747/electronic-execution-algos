//
// Created by Rohan Talkad on 2020-05-21.
//

#include "../include/AlgorithmFactory.h"
#include "../include/IcebergAlgorithm.h"
#include "../include/VWAPAlgorithm.h"
#include "../include/ParticipateAlgorithm.h"
#include "../include/TWAPAlgorithm.h"

Algorithm &AlgorithmFactory::getInstance(AlgorithmType &type, Raptor &raptor, AlgoConfig &cfg)
{
    Algorithm *algo;
    switch (type)
    {
        case (AlgorithmType::ICEBERG):
            algo = new IcebergAlgorithm(cfg, raptor);
            break;
        case (AlgorithmType::VWAP):
            algo = new VWAPAlgorithm(cfg, raptor);
            break;
        case (AlgorithmType::PARTICIPATE):
            algo = new ParticipateAlgorithm(cfg, raptor);
            break;
        case (AlgorithmType::TWAP):
            algo = new TWAPAlgorithm(cfg, raptor);
            break;
        case (AlgorithmType::NONE):
            throw std::runtime_error("Algorithm must be defined!");
    }
    return *algo;
}
