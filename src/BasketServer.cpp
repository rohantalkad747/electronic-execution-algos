//
// Created by Rohan Talkad on 2020-05-21.
//

#include "../include/BasketServer.h"

Basket *
BasketServer::createTradableBasket(std::string accountId, std::vector<std::string> symbols, std::vector<int> quantities,
                                   std::vector<OrderSide> sides)
{
    auto *basket = new Basket(symbols, accountId, basketId++, quantities, sides);
    basketDb.addBasket(basket);
    return basket;
}

template<typename A>
Wave<A> *
BasketServer::acceptWaveOrderRequest(int basketId, double percentage, A *algoConfig, const std::vector<double> &prices,
                                     const std::vector<OrderType> &orderTypes)
{
    Basket *basket = this->basketDb.getBasket(basketId);
    if (basket == nullptr)
    {
        throw std::runtime_error("Could not find basket!");
    }
    auto *wave = new Wave<A>(basket->getCurrentWave() + 1, percentage, algoConfig, prices, orderTypes, raptor);
    basket->setNewWaveStatus();
    wave->executeWave(basket);
    return wave;
}

void BasketServer::cancelBasketWave(long basketId)
{

}