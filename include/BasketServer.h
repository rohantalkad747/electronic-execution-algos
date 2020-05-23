//
// Created by Rohan Talkad on 2020-05-21.
//

#ifndef UNTITLED1_BASKETSERVER_H
#define UNTITLED1_BASKETSERVER_H

#include "Basket.h"
#include "OrderType.h"
#include "BasketDB.h"
#include "BasketServerStatus.h"
#include "Raptor.h"
#include "BasketWave.h"
#include <vector>

class BasketServer
{
private:
    BasketServerStatus bss;
    BasketDB           basketDb;
    std::atomic<int>   basketId = 0;
    Raptor             raptor;

    Basket *getBasket_(long basketId);

public:

    BasketServer(Raptor raptor, BasketDB basketDb, BasketServerStatus bss) : raptor(raptor), basketDb(basketDb),
                                                                             bss(bss)
    {

    }

    BasketServerStatus getBss() const
    {
        return bss;
    }

    void setBss(BasketServerStatus bss)
    {
        BasketServer::bss = bss;
    }


    /**
     *
     * @param accountId
     * @param symbols
     * @param quantities
     * @param sides
     * @return
     */
    Basket *createTradableBasket(
            std::string accountId,
            std::vector<std::string> symbols,
            std::vector<int> quantities,
            std::vector<OrderSide> sides
    );

    /**
     *
     * @tparam A
     * @param basketId
     * @param percentage
     * @param algoConfig
     * @param prices
     * @param orderTypes
     * @return
     */
    template<typename A>
    inline BasketWave<A> *createWave(int basketId,
                                     double percentage,
                                     A *algoConfig,
                                     AlgorithmType *algorithmType,
                                     std::vector<double> &prices,
                                     std::vector<OrderType> &orderTypes,
                                     LotSizing lotSizing,
                                     Rounding rounding)
    {
        Basket *basket = getBasket_(basketId);
        if (basket->getWaveStatus())
        {
            throw std::runtime_error("BasketWave order in progress!");
        }
        auto *wave = new BasketWave<A>(basket->getCurrentWave() + 1,
                                       percentage,
                                       algoConfig,
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

    template<typename A>
    void cancelBasketWave(long basketId);
};


#endif //UNTITLED1_BASKETSERVER_H
