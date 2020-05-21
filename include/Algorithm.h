//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGORITHM_H
#define UNTITLED1_ALGORITHM_H

#include "AlgoConfig.h"
#include "SprayRouter.h"
#include "Raptor.h"

/**
 * Base-level class for all trading algorithms.
 */
class Algorithm
{
public:

    Algorithm(AlgoConfig *algoConfig, const VenueManager &venueManager)
            : algoConfig(algoConfig), raptor(Raptor(venueManager)),
              log(*(new Logger("Algorithm"))), cancel(false)
    {}

    Algorithm(AlgoConfig &algoConfig, const Raptor &raptor)
            : algoConfig(&algoConfig), raptor(raptor),
              log(*(new Logger("Algorithm"))), cancel(false)
    {}

    Algorithm(Algorithm &algo) : raptor(algo.raptor), log(algo.log), cancel(algo.cancel)
    {}

    void executeAlgo();

    void cancelAlgo();

    bool algoActive();

    AlgoConfig *getAlgoConfig()
    {
        return this->algoConfig;
    }

    void setAlgoConfig(AlgoConfig *cfg)
    {
        this->algoConfig = cfg;
    }

protected:
    std::condition_variable schedGuard_;
    std::mutex              mtx_;

    virtual double getPrice() = 0;

    virtual int getLeavesQuantity() = 0;

    void sendToRouter();

    int sharesTraded = 0;
public:
    int getSharesTraded() const;

protected:
    AlgoConfig *algoConfig;

protected:
    bool cancel;

    Logger log;
private:
    Raptor raptor;

    Order getChildOrder();

    static bool pxIncompatibleWithLimit(double px, const Order &order);
};

#endif //UNTITLED1_ALGORITHM_H
