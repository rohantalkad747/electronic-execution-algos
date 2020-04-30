//
// Created by Rohan on 4/28/2020.
//

#include <string>
#include "../include/OrderBook.h"
#include "../include/SplayTree.h"

void OrderBook::addOrder(const Order &order) {
    PricePoint* searchPp = PricePoint::of(order);
    Node<PricePoint>* foundPp = SplayTree::search<PricePoint>(this->root, *searchPp);
    if (foundPp == nullptr)
    {
        foundPp = new Node<PricePoint>(*searchPp);
        if (this->root == nullptr)
        {
            this->root = foundPp;
        }
        else
        {
            SplayTree::insert<PricePoint>(this->root, foundPp->key);
        }
    }
    else
    {
        delete searchPp;
    }
    foundPp->key.addOrder(order);
}