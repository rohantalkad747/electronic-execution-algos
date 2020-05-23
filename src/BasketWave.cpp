//
// Created by Rohan Talkad on 2020-05-20.
//

#include <numeric>
#include "../include/BasketWave.h"
#include "../include/AlgorithmFactory.h"

template<typename A>
std::vector<Order> BasketWave<A>::splitBySecurity(Basket *b)
{
    std::vector<Order> orders;
    for (int           i = 0; i < orders.size(); i++)
    {
        std::string symbol    = b->getSymbols()[i];
        OrderSide   side      = b->getSides()[i];
        int totalQuantity     = b->getQuantities()[i];
        int withRoundLots     = getQuantityAfterLotAdjustment(b, totalQuantity);
        OrderType   orderType = b->getOrderTypes()[i];
        double      price     = prices[i];
        auto        *order    = new Order(side, symbol, withRoundLots, orderType, price, TimeInForce::DAY);
        orders.push_back(*order);
        total += withRoundLots;
    }
    return orders;
}

// ROUND

// UP: 473 -> 500
// DOWN: 473 -> 400

// LOT SIZING
// ROUND: ABLE TO ROUND
// ODD: NO ROUNDING


template<typename A>
int BasketWave<A>::getQuantityAfterLotAdjustment(const Basket *b, int totalQuantity)
{
    double quantity = totalQuantity * percentage;
    if (lotSizing == LotSizing::ODD)
    {
        return quantity;
    }
    int    withRoundLots = ((int) (quantity / 100)) * 100;
    if (round == Round::UP)
    {
        int remaining = b->leaves() - withRoundLots;
        withRoundLots += std::min(100, remaining);
    }
    return withRoundLots;
}

template<typename A>
std::string BasketWave<A>::getStatus()
{
    if (waveSymbolStatus & BasketWave::SENT)
    {
        return "Sent";
    }
    if (waveSymbolStatus & BasketWave::CANCELLED)
    {
        std::string wss = "Cancelled";
        if (waveSymbolStatus & BasketWave::PARTIAL_EX)
        {
            wss += "- Partial Execution";
        }
        return wss;
    }
    if (waveSymbolStatus & BasketWave::EXECUTED)
    {
        return "Executed";
    }
    if (waveSymbolStatus & BasketWave::PENDING)
    {
        return "Pending";
    }
    return "N/A";
}

template<typename A>
void BasketWave<A>::executeWave(Basket *b)
{
    if (waveSymbolStatus & BasketWave::PENDING)
    {
        orders = splitBySecurity(b);
        for (const auto &order : orders)
        {
            if (algoConfig != nullptr)
            {
                AlgoConfig *cfg = getAlgorithmConfig();
                cfg->setOrder(order);
                Algorithm *algorithm = AlgorithmFactory::getInstance(this->algoType, raptor, cfg);
                algorithm->executeAlgo();
            }
            else
            {
                raptor->send(this->routingConfig, order);
            }
        }
        waveSymbolStatus = (waveSymbolStatus | BasketWave::SENT) & ~BasketWave::PENDING;

    }
}

template<typename A>
void BasketWave<A>::cancelWave()
{
    Algorithm *algo = this->getAlgorithm();
    waveSymbolStatus |= BasketWave::CANCELLED;
    algo->cancelAlgo();
}

template<typename A>
Order *BasketWave<A>::findOrder(const std::string &orderId)
{
    Order *order;
    int   i = 0;
    while ((order = &orders[++i])->getClOrdId() != orderId);
    return order;
}

template<typename A>
void BasketWave<A>::onExecution(Execution *execution)
{
    Order &order   = findOrder(execution->order_id());
    int   executed = order.getQuantity() - execution->leavesQty();
    this->traded += executed;
    std::unique_lock lk(mtx_);
    if (waveSymbolStatus & BasketWave::SENT)
    {
        waveSymbolStatus = (waveSymbolStatus | BasketWave::SENT) & ~BasketWave::PARTIAL_EX;
    } else if (traded == total)
    {
        waveSymbolStatus |= BasketWave::EXECUTED;
    }
}

template<typename A>
std::vector<Order> BasketWave<A>::getOrders(OrderStatus orderStatus)
{
    return std::copy_if(orders.begin(), orders.end(), [orderStatus](Order order)
    {
        return order.getOrderStatus() == orderStatus;
    });
}



