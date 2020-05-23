//
// Created by Rohan Talkad on 2020-05-21.
//

#include "../include/BasketServer.h"
#include "../include/BasketWave.h"

Basket *
BasketServer::createTradableBasket(std::string accountId, std::vector<std::string> symbols, std::vector<int> quantities,
                                   std::vector<OrderSide> sides)
{
    auto *basket = new Basket(symbols, accountId, basketId++, quantities, sides);
    basketDb.addBasket(basket);
    return basket;
}

Basket *BasketServer::getBasket_(long bsId)
{
    Basket *basket = this->basketDb.getBasket(bsId);
    if (basket == nullptr)
    {
        throw std::runtime_error("Could not find basket!");
    }
    return basket;
}

template<typename A>
void BasketServer::cancelBasketWave(long bsId)
{
    Basket *basket = getBasket_(bsId);
    if (!basket->getWaveStatus())
    {
        throw std::runtime_error("BasketWave not in progress!");
    }
    basket->getCurrentWave();
}