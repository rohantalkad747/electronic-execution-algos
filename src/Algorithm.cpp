//
// Created by Rohan on 4/25/2020.
//

#include "../include/Algorithm.h"
#include "../include/TimeUtils.h"
#include "../include/TimingContext.h"


void Algorithm::sendToRouter()
{
    Order child = getChildOrder();
    RoutingConfig routingConfig = this->algoConfig->getRoutingConfig();
    switch (routingConfig.getRoutingType())
    {
        case (RoutingType::DIRECT):
            this->venueManager.sendOrder(routingConfig.getVenueName(), child);
            break;
        case (RoutingType::SPRAY):
            this->sprayRouter.route(child);
            break;
        case (RoutingType::SERIAL): // TODO
            break;
        default:
            throw *(new std::exception);
    }
    this->sharesTraded += child.getQuantity();
}

Order Algorithm::getChildOrder()
{
    Order prnt = algoConfig->getOrder();
    Order child(prnt);
    double px = this->getPrice();
    if (prnt.getOrderType() == OrderType::LIMIT && pxIncompatibleWithLimit(px, prnt))
    {
        px = prnt.getPrice();
    }
    int leaves = this->getLeavesQuantity();
    child.setPrice(px);
    child.setQuantity(leaves);
    return child;
}

bool Algorithm::algoActive()
{
    return
            TimeUtils::getCurTimeEpoch() <= ((TimingContext *) (this->algoConfig))->getEndTime() &&
            !this->cancel &&
            this->sharesTraded != this->algoConfig->getOrder().getQuantity();
}

bool Algorithm::pxIncompatibleWithLimit(double px, Order order)
{
    double lmt = order.getPrice();
    return (order.getSide() == OrderSide::BUY) ? px <= lmt : px >= lmt;
}



