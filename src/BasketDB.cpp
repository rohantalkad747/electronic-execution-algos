//
// Created by Rohan Talkad on 2020-05-23.
//

#include "../include/BasketDB.h"

void BasketDB::addBasket(Basket *basket)
{
    this->baskets[basket->getBasketId()] = basket;
}

Basket * BasketDB::getBasket(long basketId)
{
    return this->baskets[basketId];
}

void BasketDB::deleteBasket(long basketId)
{
    this->baskets.erase(basketId);
}

void BasketDB::deleteBasket(Basket *basket)
{
    deleteBasket(basket->getBasketId());
}