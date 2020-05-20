//
// Created by Rohan on 4/28/2020.
//

#ifndef UNTITLED1_ORDERBOOK_H
#define UNTITLED1_ORDERBOOK_H


#include "Order.h"
#include "PricePoint.h"
#include "../include/Node.h"

class OrderBook {
public:
    void addOrder(const Order &order);

    Node<PricePoint> *getRoot() const {
        return this->root;
    }

private:
    Node<PricePoint> *root;
};


#endif //UNTITLED1_ORDERBOOK_H
