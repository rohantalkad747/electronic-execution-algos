//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ALGORITHM_H
#define UNTITLED1_ALGORITHM_H

#include "AlgoConfig.h"
#include "SprayRouter.h"

/**
 * Base-level class for all trading algorithms.
 */
class Algorithm
{
public:

    Algorithm(AlgoConfig *algoConfig, const VenueManager &venueManager)
            : algoConfig(algoConfig), sprayRouter(SprayRouter(venueManager)), venueManager(venueManager),
              log(*(new Logger("Algorithm"))), cancel(false)
    {}

    virtual void executeAlgo() = 0;

    void cancelAlgo();

    bool algoActive();

    AlgoConfig *getAlgoConfig()
    {
        return this->algoConfig;
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
    SprayRouter  sprayRouter;
    VenueManager venueManager;

    Order getChildOrder();

    static bool pxIncompatibleWithLimit(double px, const Order &order);
};

#endif //UNTITLED1_ALGORITHM_H
