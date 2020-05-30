//
// Created by Rohan Talkad on 2020-05-23.
//

#include "../include/BasketDB.h"


void BasketDB::addBasket(Basket *basket)
{
    this->baskets[basket->getBasketId()] = basket;
}

Basket *BasketDB::getBasket(long &basketId)
{
    return this->baskets[basketId];
}

std::vector<BasketWave *> & BasketDB::getWaves(long &basketId)
{
    return waves[basketId];
}

void BasketDB::addWave(long &basketId, BasketWave *wave)
{
    std::vector<BasketWave*> basketWaves = waves[basketId];
    basketWaves.push_back(wave);
}

void BasketDB::deleteBasket(long &basketId)
{
    Basket* basket = getBasket(basketId);
    delete basket;
    baskets.erase(basketId);
}

void BasketDB::deleteBasket(Basket *basket)
{
    long id = basket->getBasketId();
    deleteBasket(id);
}