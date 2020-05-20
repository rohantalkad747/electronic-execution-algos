//
// Created by Rohan Talkad on 2020-05-20.
//

#include "../include/Wave.h"

template<typename A>
std::vector<Order> Wave<A>::splitBySecurity(Basket *b) {
    std::vector<Order> orders;
    for (int i = 0; i < orders.size(); i++) {
        std::string symbol = b->getSymbols()[i];
        OrderSide side = b->getSides()[i];
        int quantity = b->getQuantities()[i] * this->percentage;
        OrderType orderType = this->orderType;
        double price = this->prices[i];
        Order *order = new Order(side, symbol, quantity, orderType, price, TimeInForce::DAY);
        orders.push_back(*order);
    }
    return orders;
}

template<typename A>
void Wave<A>::executeWave(Basket *b) {
    if (waveStatusHistory & Wave::PENDING) {
        orders = splitBySecurity(b);
        for (const auto &order : orders) {
            Algorithm *algo = getAlgorithm();
            algo->getAlgoConfig()->setOrder(order);
            algo->executeAlgo();
        }
        waveStatusHistory = (waveStatusHistory | Wave::SENT) & ~Wave::PENDING;
    }
}

template<typename A>
void Wave<A>::cancelWave() {
    Algorithm *algo = this->getAlgorithm();
    this->waveStatusHistory |= Wave::CANCELLED;
    algo->cancelAlgo();
}

template<typename A>
void Wave<A>::replaceWave(Wave<A> *v) {
    this->cancelWave();
    this = v;
}

template<typename A>
Order *Wave<A>::findOrder(std::string orderId) {
    Order *order;
    int i = 0;
    while ((order = &orders[++i])->getClOrdId() != orderId);
    return order;
}

template<typename A>
void Wave<A>::onExecution(Execution *execution) {
    Order &order = findOrder(execution->order_id());
    int executed = order.getQuantity() - execution->leavesQty();
    this->traded += executed;
}


template<typename A>
Wave<A>::~Wave() {
    delete algorithm;
}
