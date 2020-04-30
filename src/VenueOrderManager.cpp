//
// Created by Rohan on 4/29/2020.
//

#include "../include/VenueOrderManager.h"


/**
 * There are three types of orders accepted: those that take
 * liquidity from a book, those that add liquidity to the book, and those that
 * are a combination of both.
 */
void VenueOrderManager::acceptOrder(Order& order)
{
    {
        OrderSide side = order.getSide();
        std::string sym = order.getSymbol();
        OrderBook book = this->books[sym][side];
        LiquidityIndicator li = order.getLiquidityIndicator();
        bool remove = li  == LiquidityIndicator::REMOVE;
        bool both;
        if ( remove || ( both = ( li  == LiquidityIndicator::BOTH ) ) )
        {
            Node<PricePoint>* depth = book.getRoot();
            if ( depth != nullptr )
            {
                std::function<bool(PricePoint&)> isCompatibleFunct = ( side == OrderSide::BUY ) ?
                                                                     VenueOrderManager::isCompatibleBuy(order) : VenueOrderManager::isCompatibleSell(order);
                dispatchToExecutionService(depth, order, isCompatibleFunct);
            }
        }
        if ( !remove )
        {
            if ( both && order.isTerminal())
            {
                return;
            }
            book.addOrder(order);
        }
    }
}

void VenueOrderManager::dispatchToExecutionService(Node<PricePoint> *depth, Order &order, std::function<bool(PricePoint &)>& isCompatible)
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