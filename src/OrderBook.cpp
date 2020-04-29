//
// Created by Rohan on 4/28/2020.
//

#include <string>
#include "../include/OrderBook.h"
#include "../include/SplayTree.h"

void OrderBook::addOrder(const Order &order) {
    PricePoint* searchPp = PricePoint::of(order);
    Node<PricePoint>* foundPp = SplayTree::search(this->root, *searchPp);
    bool ppTemp = false;
    if (foundPp == nullptr)
    {
        ppTemp = true;
        foundPp = new Node<PricePoint>(*searchPp);
        this->root = foundPp;
    }
    searchPp->addOrder(order);
    PricePoint& pp = foundPp->key;
    pp.addOrder(order);
    if (ppTemp)
    {
        delete searchPp;
    }
}