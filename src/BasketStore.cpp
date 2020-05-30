//
// Created by Rohan Talkad on 2020-05-23.
//

#include "../include/BasketStore.h"


void BasketStore::addBasket(Basket *basket)
{
    this->baskets[basket->getBasketId()] = basket;
}

Basket *BasketStore::getBasket(long &basketId)
{
    return this->baskets[basketId];
}

std::vector<BasketWave *> &BasketStore::getWaves(long &basketId)
{
    return waves[basketId];
}

void BasketStore::addWave(long &basketId, BasketWave *wave)
{
    std::vector<BasketWave *> basketWaves = waves[basketId];
    basketWaves.push_back(wave);
}

void BasketStore::deleteBasket(long &basketId)
{
    Basket *basket = getBasket(basketId);
    delete basket;
    baskets.erase(basketId);
}

void BasketStore::deleteBasket(Basket *basket)
{
    long id = basket->getBasketId();
    deleteBasket(id);
}