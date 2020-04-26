//
// Created by Rohan on 4/25/2020.
//

#include "../include/Algorithm.h"


void Algorithm::sendToRouter()
{
    Order child = getChildOrder();
    RoutingConfig routingConfig = this->algoConfig.getRoutingConfig();
    if (routingConfig.getRoutingType() == RoutingType::DIRECT)
    {
       this->venueManager.sendOrder(routingConfig.getVenueName(), child);
    }
    else if (routingConfig.getRoutingType() == RoutingType::SPRAY)
    {
        this->sprayRouter.route(child);
    }
    else
    {
        // TODO for serial router and possibly other types
        throw *(new std::exception);
    }
}

Order Algorithm::getChildOrder()
{
    Order child(algoConfig.getOrder());
    double px = getPrice();
    int leaves = getLeavesQuantity();
    child.setPrice(px);
    child.setQuantity(leaves);
    return child;
}

bool Algorithm::algoActive()
{
    return !this->cancel && !this->algoConfig.getOrder().isTerminal();
}


