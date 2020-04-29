//
// Created by Rohan on 4/29/2020.
//

#include "TakeLiquidityManager.h"


void TakeLiquidityManager::takeLiquidity(OrderBook& book, Order& order)
{
    {
        Node<PricePoint>* depth = book.getRoot();
        if ( depth == nullptr )
        {
            return;
        }
        OrderSide os = order.getSide();
        std::function<bool(PricePoint&)> isCompatible = (os == OrderSide::BUY) ? TakeLiquidityManager::isCompatibleBuy(order) : TakeLiquidityManager::isCompatibleSell(order);
        dispatchToExecutionService(depth, order, isCompatible);
    }
}

void TakeLiquidityManager::dispatchToExecutionService(Node<PricePoint> *depth, Order &order, std::function<bool(PricePoint &)>& isCompatible)
{
    if (depth == nullptr || !isCompatible(depth->key))
        return;
    dispatchToExecutionService(depth->left, order, isCompatible);
    if (order.isTerminal())
        return;
    if (order.getOrderType() == OrderType::MARKET || isCompatible(depth->key))
    {
        std::vector ppOdrs = depth->key.getOrders();
        for (auto& ordr : ppOdrs)
        {
            if (!ordr.isTerminal())
            {
                executionService.execute(order, ordr);
                if (order.isTerminal())
                    return;
            }
        }
    }
    dispatchToExecutionService(depth->right, order, isCompatible);
}

double TakeLiquidityManager::getTakerFees(Order &order) const
{
    return order.getQuantity() * takerFee;
}
