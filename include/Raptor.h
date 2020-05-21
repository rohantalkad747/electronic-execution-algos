//
// Created by Rohan Talkad on 2020-05-21.
//

#ifndef UNTITLED1_RAPTOR_H
#define UNTITLED1_RAPTOR_H


#include "VenueManager.h"
#include "RoutingConfig.h"
#include "SprayRouter.h"

class Raptor
{
public:
    Raptor(const VenueManager &vm) : sprayRouter(SprayRouter(vm)), vm(vm)
    {}

    void send(RoutingConfig &routingConfig, Order &order);

private:
    SprayRouter  sprayRouter;
    VenueManager vm;
};


#endif //UNTITLED1_RAPTOR_H
