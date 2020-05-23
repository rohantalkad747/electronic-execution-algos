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
    BasketDB basketDb;
    std::atomic<int> basketId = 0;
    Raptor raptor;

    Basket * getBasket_(long basketId);

public:

    BasketServer(Raptor raptor, BasketDB basketDb, BasketServerStatus bss) : raptor(raptor), basketDb(basketDb), bss(bss)
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


    Basket* createTradableBasket(
            std::string accountId,
            std::vector<std::string> symbols,
            std::vector<int> quantities,
            std::vector<OrderSide> sides
    );

    template<typename A>
    BasketWave<A>* acceptWaveOrderRequest(int basketId,
                                          double percentage,
                                          A *algoConfig,
                                          const std::vector<double> &prices,
                                          const std::vector<OrderType> &orderTypes);

    template<typename A>
    void cancelBasketWave(long basketId);
};


#endif //UNTITLED1_BASKETSERVER_H
