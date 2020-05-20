//
// Created by Rohan on 4/25/2020.
//

#include "../include/Algorithm.h"

struct InvalidRouteException : public std::exception {
    std::string s;

    explicit InvalidRouteException(std::string ss) : s(ss) {}

    ~InvalidRouteException() noexcept override {}

    const char *what() const noexcept { return s.c_str(); }
};

void Algorithm::cancelAlgo() {
    std::unique_lock<std::mutex> lk(mtx_);
    this->cancel = true;
    lk.unlock();
    this->schedGuard_.notify_one();
}

void Algorithm::sendToRouter() {
    Order child = getChildOrder();
    RoutingConfig routingConfig = this->algoConfig->getRoutingConfig();
    switch (routingConfig.getRoutingType()) {
        case (RoutingType::DIRECT):
            this->venueManager.sendOrder(routingConfig.getVenueName(), child);
            break;
        case (RoutingType::SPRAY):
            this->sprayRouter.route(child);
            break;
        default:
            throw InvalidRouteException("Invalid routing type!");
    }
    this->sharesTraded += child.getQuantity();
}

Order Algorithm::getChildOrder() {
    Order prnt = algoConfig->getOrder();
    Order child(prnt);
    double px = this->getPrice();
    if (prnt.getOrderType() == OrderType::LIMIT && pxIncompatibleWithLimit(px, prnt)) {
        px = prnt.getPrice();
    }
    int leaves = this->getLeavesQuantity();
    child.setPrice(px);
    child.setQuantity(leaves);
    return child;
}

bool Algorithm::algoActive() {
    return
            TimeUtils::getCurTimeEpoch() <= this->algoConfig->getEndTime() &&
            this->sharesTraded < this->algoConfig->getOrder().getQuantity();
}

bool Algorithm::pxIncompatibleWithLimit(double px, const Order &order) {
    double lmt = order.getPrice();
    return (order.getSide() == OrderSide::BUY) ? px <= lmt : px >= lmt;
}

int Algorithm::getSharesTraded() const {
    return sharesTraded;
}



