//
// Created by Rohan Talkad on 2020-05-20.
//

#include <numeric>
#include "../include/Wave.h"
#include "../include/AlgorithmFactory.h"

template<typename A>
std::vector<Order> Wave<A>::splitBySecurity(Basket *b)
{
    std::vector<Order> orders;
    for (int           i = 0; i < orders.size(); i++)
    {
        std::string symbol    = b->getSymbols()[i];
        OrderSide   side      = b->getSides()[i];
        int         quantity  = b->getQuantities()[i] * percentage;
        OrderType   orderType = b->getOrderTypes()[i];
        double      price     = prices[i];
        auto        *order    = new Order(side, symbol, quantity, orderType, price, TimeInForce::DAY);
        orders.push_back(*order);
        total += quantity;
    }
    return orders;
}

template<typename A>
std::string Wave<A>::getStatus()
{
    if (waveSymbolStatus & Wave::SENT)
    {
        return "Sent";
    }
    if (waveSymbolStatus & Wave::CANCELLED)
    {
        std::string wss = "Cancelled";
        if (waveSymbolStatus & Wave::PARTIAL_EX)
        {
            wss += "- Partial Execution";
        }
        return wss;
    }
    if (waveSymbolStatus & Wave::EXECUTED)
    {
        return "Executed";
    }
    if (waveSymbolStatus & Wave::PENDING)
    {
        return "Pending";
    }
    return "N/A";
}

template<typename A>
void Wave<A>::executeWave(Basket *b)
{
    if (waveSymbolStatus & Wave::PENDING)
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
        waveSymbolStatus = (waveSymbolStatus | Wave::SENT) & ~Wave::PENDING;

    }
}

template<typename A>
void Wave<A>::cancelWave()
{
    Algorithm *algo = this->getAlgorithm();
    waveSymbolStatus |= Wave::CANCELLED;
    algo->cancelAlgo();
}

template<typename A>
Order *Wave<A>::findOrder(const std::string &orderId)
{
    Order *order;
    int   i = 0;
    while ((order = &orders[++i])->getClOrdId() != orderId);
    return order;
}

template<typename A>
void Wave<A>::onExecution(Execution *execution)
{
    Order &order   = findOrder(execution->order_id());
    int   executed = order.getQuantity() - execution->leavesQty();
    this->traded += executed;
    std::unique_lock lk(mtx_);
    if (waveSymbolStatus & Wave::SENT)
    {
        waveSymbolStatus = (waveSymbolStatus | Wave::SENT) & ~Wave::PARTIAL_EX;
    } else if (traded == total)
    {
        waveSymbolStatus |= Wave::EXECUTED;
    }
}

template<typename A>
std::vector<Order> Wave<A>::getOrders(OrderStatus orderStatus)
{
    return std::copy_if(orders.begin(), orders.end(), [orderStatus](Order order)
    {
        return order.getOrderStatus() == orderStatus;
    });
}



