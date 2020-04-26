//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_ROUTINGCONFIG_H
#define UNTITLED1_ROUTINGCONFIG_H

#include "RoutingType.h"

class RoutingConfig
{
private:
    RoutingType routingType;
public:
    RoutingConfig(RoutingType routingType, const std::string &venueName) : routingType(routingType),
                                                                           venueName(venueName)
    {}

    RoutingType getRoutingType() const
    {
        return routingType;
    }

    void setRoutingType(RoutingType routingType)
    {
        RoutingConfig::routingType = routingType;
    }

    const std::string &getVenueName() const
    {
        return venueName;
    }

    void setVenueName(const std::string &venueName)
    {
        RoutingConfig::venueName = venueName;
    }

private:
    std::string venueName;
};

#endif //UNTITLED1_ROUTINGCONFIG_H
