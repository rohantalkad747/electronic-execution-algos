//
// Created by Rohan Talkad on 2020-05-21.
//

#include "../include/Raptor.h"

struct InvalidRouteException : public std::exception
{
    std::string s;

    explicit InvalidRouteException(std::string ss) : s(ss)
    {}

    ~InvalidRouteException() noexcept override
    {}

    const char *what() const noexcept override
    { return s.c_str(); }
};

void Raptor::send(RoutingConfig &routingConfig, Order &order)
{
    switch (routingConfig.getRoutingType())
    {
        case (RoutingType::DIRECT):
            this->vm.sendOrder(routingConfig.getVenueName(), order);
            break;
        case (RoutingType::SPRAY):
            this->sprayRouter.route(order);
            break;
        default:
            throw InvalidRouteException("Invalid routing type!");
    }
}