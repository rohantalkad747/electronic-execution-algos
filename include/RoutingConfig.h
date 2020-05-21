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
    std::string venueName;

    RoutingConfig(RoutingType routingType) : routingType(routingType)
    {}

    RoutingConfig(RoutingType routingType, const std::string &venueName) : routingType(routingType),
                                                                           venueName(venueName)
    {}

public:
    static RoutingConfig getSOR(RoutingType routingType)
    {
        return *(new RoutingConfig(routingType, ""));

    }

    static RoutingConfig getDirectRouter(const std::string &venueName)
    {
        return *(new RoutingConfig(RoutingType::DIRECT, venueName));
    }

    RoutingType getRoutingType() const
    {
        return routingType;
    }

    void setRoutingType(RoutingType routingType)
    {
        RoutingConfig::routingType = routingType;
    }

    std::string &getVenueName()
    {
        return venueName;
    }

    void setVenueName(const std::string &venueName)
    {
        RoutingConfig::venueName = venueName;
    }
};

#endif //UNTITLED1_ROUTINGCONFIG_H
