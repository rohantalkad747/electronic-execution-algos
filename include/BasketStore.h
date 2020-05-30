//
// Created by Rohan Talkad on 2020-05-21.
//

#ifndef UNTITLED1_BASKETSTORE_H
#define UNTITLED1_BASKETSTORE_H


#include <map>
#include "Basket.h"
#include "BasketWave.h"

class BasketStore
{
private:
    std::map<long, Basket *>                  baskets;
    std::map<long, std::vector<BasketWave *>> waves;
public:
    void addBasket(Basket *basket);

    void addWave(long &basketId, BasketWave *wave);

    std::vector<BasketWave *> &getWaves(long &basketId);

    Basket *getBasket(long &basketId);

    void deleteBasket(Basket *basket);

    void deleteBasket(long &basketId);
};


#endif //UNTITLED1_BASKETSTORE_H
