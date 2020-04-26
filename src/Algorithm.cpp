//
// Created by Rohan on 4/25/2020.
//

#include "../include/Algorithm.h"
#include "../include/RoutingType.h"
#include "../include/Venue.h"


void Algorithm::sendToRouter()
{
    Order child = getChildOrder();
    RoutingConfig routingConfig = this->algoConfig.getRoutingConfig();
    if (routingConfig.getRoutingType() == RoutingType::DIRECT)
    {
        const std::string& venueName = routingConfig.getVenueName();
        std::vector<Venue> venues = venueManager.venues(this->algoConfig.getOrder().getSymbol());
        int i = -1;
        Venue* v;
        while (++i < venues.size())
        {
            if ((v = &venues[i])->getName() == venueName)
            {
                if (v->isAvailable())
                {
                    // TODO send to venue
                    return;
                }
                throw new std::exception;
            }
        }
    }
    else if (routingConfig.getRoutingType() == RoutingType::SPRAY)
    {
        this->sprayRouter.route(child);
    }
    else
    {
        // TODO
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


