//
// Created by Rohan on 4/29/2020.
//

#include "../include/OrderBookManager.h"
#include "../include/PricePoint.h"
#include "../include/FillService.h"


void OrderBookManager::takeLiquidity(OrderBook& book, Order& order)
{
    {
        Node<PricePoint>* depth = book.getRoot();
        if ( depth == nullptr )
        {
            return;
        }
        OrderSide os = order.getSide();
        std::function<bool(PricePoint&)> isCompatible = (os == OrderSide::BUY) ? OrderBookManager::isCompatibleBuy(order) : OrderBookManager::isCompatibleSell(order);
        dispatchToExecutionService(depth, order, isCompatible);
    }
}

void OrderBookManager::dispatchToExecutionService(Node<PricePoint> *depth, Order &order, std::function<bool(PricePoint &)>& isCompatible)
{
    if (depth == nullptr || !isCompatible(depth->key))
    {
        return;
    }
    dispatchToExecutionService(depth->left, order, isCompatible);
    if (order.isTerminal())
    {
        return;
    }
    if (order.getOrderType() == OrderType::MARKET || isCompatible(depth->key))
    {
        std::vector ppOdrs = depth->key.getOrders();
        for (auto& ordr : ppOdrs)
        {
            std::scoped_lock<std::mutex, std::mutex> lck(*(order.getMtx()), *(ordr.getMtx()));
            if (!ordr.isTerminal())
            {
                fillService.execute(order, ordr);
                if (order.isTerminal())
                {
                    return;
                }
            }
        }
    }
    dispatchToExecutionService(depth->right, order, isCompatible);
}