//
// Created by Rohan Talkad on 2020-05-21.
//

#include "../include/BasketServer.h"

Basket *
BasketServer::createTradableBasket(std::string accountId, std::vector<std::string> symbols, std::vector<int> quantities,
                                   std::vector<OrderSide> sides)
{
    auto *basket = new Basket(symbols, accountId, curBasketId++, quantities, sides);
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

BasketWave * BasketServer::createWave(int basketId, double percentage, OrderConfig *orderConfig, AlgorithmType *algorithmType, std::vector<double> &prices, std::vector<OrderType> &orderTypes, LotSizing lotSizing, Rounding rounding)
{
    Basket *basket = getBasket_(basketId);
    auto *wave = new BasketWave(basket->getCurrentWave() + 1,
                                percentage,
                                orderConfig,
                                algorithmType,
                                prices,
                                orderTypes,
                                &raptor,
                                rounding,
                                lotSizing);
    basket->setNewWaveStatus();
    wave->executeWave(basket);
    return wave;
}

void BasketServer::cancelOutstandingOrders(long &bsId)
{

    std::vector<BasketWave*> waves = basketDb.getWaves(bsId);
    for (auto* wave : waves)
    {
        unsigned char wss = wave->getWaveSymbolStatus();
        unsigned char cx = BasketWave::CANCELLED | BasketWave::EXECUTED;
        if ( ( wss & cx) ==  cx )
        {
            wave->cancelWave();
        }
    }
}