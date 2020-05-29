//
// Created by Rohan Talkad on 2020-05-20.
//

#include <numeric>
#include "../include/Basket.h"
#include "../include/BasketWave.h"
#include "../include/Algorithm.h"
#include "../include/AlgorithmFactory.h"

std::vector<Order> BasketWave::splitBySecurity(Basket *b)
{
    std::vector<Order> orders;
    for (int           i = 0; i < b->getSymbols().size(); i++)
    {
        std::string symbol        = b->getSymbols()[i];
        OrderSide   side          = b->getSides()[i];
        int         totalQuantity = b->getQuantities()[i];
        int         withRoundLots = getQuantityAfterLotAdjustment(b, totalQuantity);
        OrderType   orderType     = orderTypes[i];
        double      price         = prices[i];
        auto        *order        = new Order(side, symbol, withRoundLots, orderType, price, TimeInForce::DAY);
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



int BasketWave::getQuantityAfterLotAdjustment(const Basket *b, int totalQuantity)
{
    double quantity = totalQuantity * percentage;
    if (lotSizing == LotSizing::ODD)
    {
        return quantity;
    }
    int withRoundLots = ((int) (quantity / 100)) * 100;
    if (round == Rounding::UP)
    {
        int remaining = b->leaves() - withRoundLots;
        withRoundLots += std::min(100, remaining);
    }
    return withRoundLots;
}

std::string BasketWave::getStatus()
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

void BasketWave::executeWave(Basket *b)
{
    if (waveSymbolStatus & BasketWave::PENDING)
    {
        orders = splitBySecurity(b);
        for (auto &order : orders)
        {
            if (orderCfg != nullptr)
            {
                auto *cfg = dynamic_cast<OrderConfig *>(orderCfg);
                cfg->setOrder(order);
                if (*algoType == AlgorithmType::NONE)
                {
                    auto *cfg = dynamic_cast<OrderConfig *>(orderCfg);
                    cfg->setOrder(order);
                    raptor->send(cfg->getRoutingConfig(), order);
                }
                else
                {
                    auto* cfg = dynamic_cast<AlgoConfig *>(orderCfg);
                    cfg->setOrder(order);
                    algorithm = &(AlgorithmFactory::getInstance(*(this->algoType), *(raptor), *cfg));
                    algorithm->executeAlgo();
                }
            }
            else
            {
                raptor->send(*(this->routingConfig), order);
            }
        }
        waveSymbolStatus = (waveSymbolStatus | BasketWave::SENT) & ~BasketWave::PENDING;
    }
}

void BasketWave::cancelWave()
{
    if ( *(this->algoType) == AlgorithmType::NONE)
    {
        std::vector<Order> cancellable;
        std::copy_if(orders.begin(), orders.end(), back_inserter(cancellable), [](const Order& o)
        {
            OrderStatus os =  o.getOrderStatus();
            return os == OrderStatus::NEW || os == OrderStatus::PARTIAL;
        });
        for (auto& o : cancellable)
        {
            o.setOrderStatus(OrderStatus::CANCELLED);
        }
    }
    else
    {
        this->algorithm->cancelAlgo();
    }
    waveSymbolStatus |= BasketWave::CANCELLED;
}

Order *BasketWave::findOrder(const std::string &orderId)
{
    Order *order;
    int   i = 0;
    while ((order = &orders[++i])->getClOrdId() != orderId);
    return order;
}

void BasketWave::onExecution(Execution *execution)
{
    Order* order   = findOrder(execution->order_id());
    int   executed = order->getQuantity() - execution->leavesQty();
    this->traded += executed;
    std::unique_lock lk(mtx_);
    if (waveSymbolStatus & BasketWave::SENT)
    {
        waveSymbolStatus = (waveSymbolStatus | BasketWave::SENT) & ~BasketWave::PARTIAL_EX;
    }
    else if (traded == total)
    {
        waveSymbolStatus |= BasketWave::EXECUTED;
    }
}

std::vector<Order>& BasketWave::getOrders(OrderStatus orderStatus)
{
    std::vector<Order> arr = this->orders;
    std::vector<Order> res = *(new std::vector<Order>());
    std::copy_if(arr.begin(), arr.end(), back_inserter(res),[&orderStatus](const Order& o) { return o.getOrderStatus() == orderStatus; });
    return res;
}



