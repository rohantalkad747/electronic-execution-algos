//
// Created by Rohan on 4/29/2020.
//

#include <bits/shared_ptr.h>
#include "../include/ExecutionService.h"
#include "../include/Execution.h"

void ExecutionService::cancel(Order &order)
{
    std::lock_guard<std::mutex> lock(*(order.getMtx()));
    order.setQuantity(0);
    order.setOrderStatus(OrderStatus::CANCELLED);
    // Report cumulative
}

/**
 * Executes the given orders. It is assumed that only
 * {@code orderTwo} needs to be locked.
 */
inline void ExecutionService::execute(Order &orderOne, Order &fromBook)
{
    if (!fromBook.isTerminal() && !orderOne.isTerminal())
    {
        int trgtQuantity = orderOne.getQuantity();
        int bookEntryQuantity = fromBook.getQuantity();
        int executed = std::abs(trgtQuantity - bookEntryQuantity);
        orderOne.setQuantity(trgtQuantity - executed);
        fromBook.setQuantity(bookEntryQuantity - executed);
        if (executed != 0)
        {
            reportExecution(orderOne, fromBook);
        }
    }
}

void ExecutionService::reportExecution(Order &ordOne, Order &fromBook)
{
    double avPx;
    OrderType ordOneType = ordOne.getOrderType();
    OrderType fromBookType = fromBook.getOrderType();
    if (ordOneType == OrderType::MARKET)
    {
        if (fromBookType == OrderType::MARKET)
        {
            avPx = lastFill;
        }
        else
        {
            avPx = fromBook.getPrice();
        }
    }
    else if (fromBookType == OrderType::MARKET)
    {
        avPx = ordOne.getPrice();
    }
    else
    {
        avPx = fromBook.getPrice();
    }
    buildExec(ordOne, avPx);
    buildExec(fromBook, avPx);
}

void ExecutionService::buildExec(const Order &ordOne, double avPx)
{
    bool isFullExec = ordOne.isTerminal();
    ExecutionType execType;
    OrderStatus ordStatus;
    if (isFullExec)
    {
        execType = ExecutionType::DONE;
        ordStatus = OrderStatus::FILLED;
    }
    else
    {
        execType = ExecutionType::TRADE;
        ordStatus = OrderStatus::PARTIAL;
    }
    std::shared_ptr<Execution*> exec = std::make_shared<Execution*>(
            new Execution(
                    ordOne.getClOrdId(),
                    std::to_string(execId++),
                    execType,
                    ordStatus,
                    ordOne.getSymbol(),
                    ordOne.getSide(),
                    ordOne.leaves(),
                    ordOne.getCumulativeQuantity(),
                    avPx
                    )
            );
    // send to execution listener for FIX message broadcast
}
