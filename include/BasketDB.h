//
// Created by Rohan Talkad on 2020-05-21.
//

#ifndef UNTITLED1_BASKETDB_H
#define UNTITLED1_BASKETDB_H


#include <map>
#include "Basket.h"

class BasketDB
{
private:
    std::map<long, Basket*> baskets;
public:
    void addBasket(Basket* basket);

    Basket* getBasket(long basketId);

    void deleteBasket(Basket* basket);

    void deleteBasket(long basketId);
};


#endif //UNTITLED1_BASKETDB_H
