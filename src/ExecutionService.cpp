//
// Created by Rohan on 4/29/2020.
//

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
void ExecutionService::execute(Order &orderOne, Order &fromBook, std::map<std::string, double> &fillTable)
{
    if (!fromBook.isTerminal() && !orderOne.isTerminal())
    {
        int trgtQuantity      = orderOne.getQuantity();
        int bookEntryQuantity = fromBook.getQuantity();
        int executed          = std::min(trgtQuantity, bookEntryQuantity);
        orderOne.setQuantity(trgtQuantity - executed);
        orderOne.setCumulativeQuantity(orderOne.getCumulativeQuantity() + executed);
        fromBook.setQuantity(bookEntryQuantity - executed);
        fromBook.setCumulativeQuantity(fromBook.getCumulativeQuantity() + executed);
        if (executed != 0)
        {
            reportExecution(orderOne, fromBook, fillTable);
        }
    }
}

void ExecutionService::reportExecution(Order &ordOne, Order &fromBook, std::map<std::string, double> &fillTable)
{
    double avPx = resolvePx(ordOne, fromBook, fillTable);
    buildExec(ordOne, avPx);
    buildExec(fromBook, avPx);
}

double ExecutionService::resolvePx(const Order &ordOne, const Order &fromBook,
                                   std::map<std::string, double> &fillTable) const
{
    double    avPx;
    OrderType ordOneType   = ordOne.getOrderType();
    OrderType fromBookType = fromBook.getOrderType();
    if (ordOneType == OrderType::MARKET)
    {
        if (fromBookType == OrderType::MARKET)
        {
            avPx = fillTable[ordOne.getSymbol()];
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
    return avPx;
}

void ExecutionService::buildExec(const Order &ordOne, double &avPx)
{
    bool          isFullExec          = ordOne.isTerminal();
    ExecutionType execType;
    OrderStatus   ordStatus;
    if (isFullExec)
    {
        execType  = ExecutionType::DONE;
        ordStatus = OrderStatus::FILLED;
    }
    else
    {
        execType  = ExecutionType::TRADE;
        ordStatus = OrderStatus::PARTIAL;
    }
    std::lock_guard<std::mutex>  grd(*(this->mtx));
    std::unique_ptr<Execution *> exec = std::make_unique<Execution *>(
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
    std::cout << "Execution Report: S " << ordOne.getSymbol() << "C" << " " << ordOne.getCumulativeQuantity()
              << std::endl;
    // Send to execution listener for FIX exec broadcast e.g., executionListener.onExec(std::move(exec));
}
