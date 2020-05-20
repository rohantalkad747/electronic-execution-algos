//
// Created by Rohan on 4/29/2020.
//

#include "../include/VenueOrderManager.h"


/**
 * There are three types of orders accepted: those that take
 * liquidity from a book, those that add liquidity to the book, and those that
 * are a combination of both.
 */
void VenueOrderManager::acceptOrder(Order &order)
{
    {
        this->orderArena.insert_or_assign(order.getClOrdId(), &order);
        OrderSide          side            = order.getSide();
        std::string        sym             = order.getSymbol();
        OrderBook          &book           = this->books[sym][side];
        LiquidityIndicator li              = order.getLiquidityIndicator();
        bool               removeLiquidity = li == LiquidityIndicator::REMOVE;
        if (removeLiquidity || li == LiquidityIndicator::BOTH)
        {
            Node<PricePoint> *depth = book.getRoot();
            if (depth != nullptr)
            {
                std::function<bool(PricePoint &)> isCompatibleFunct = (side == OrderSide::BUY) ?
                                                                      VenueOrderManager::isCompatibleBuy(order)
                                                                                               : VenueOrderManager::isCompatibleSell(
                                order);
                dispatchToExecutionService(depth, order, isCompatibleFunct);
            }
        }
        if (!removeLiquidity && !order.isTerminal())
        {
            if ((order.getTimeInForce() == TimeInForce::IOC) &&
                (order.getCumulativeQuantity() < order.getMinQuantity()))
            {
                executionService.cancel(order);
            } else
            {
                book.addOrder(order);
            }
        }
    }
}

void VenueOrderManager::dispatchToExecutionService(Node<PricePoint> *depth, Order &order,
                                                   std::function<bool(PricePoint &)> &isCompatible)
{
    if (depth == nullptr || !(order.getOrderType() == OrderType::MARKET || isCompatible(depth->key)))
    {
        return;
    }
    dispatchToExecutionService(depth->left, order, isCompatible);
    if (order.isTerminal())
    {
        return;
    }
    std::vector ppOdrs = depth->key.getOrders();
    for (auto   &ordr : ppOdrs)
    {
        std::lock_guard<std::mutex> lock(*(ordr.getMtx()));
        executionService.execute(order, ordr, fillTable);
        if (order.isTerminal())
        {
            return;
        }
    }
    dispatchToExecutionService(depth->right, order, isCompatible);
}