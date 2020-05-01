#ifndef EXECUTION_H
#define EXECUTION_H

#include "OrderSide.h"
#include "OrderType.h"
#include "OrderStatus.h"
#include "TimeInForce.h"
#include "ExecutionType.h"
#include "OrderSide.h"
#include <string>
#include <iostream>


class Execution
{
public:
    /**
     *
     * @param orderID
     * @param execID
     * @param execType
     * @param ordStatus
     * @param symbol
     * @param side
     * @param leavesQty
     * @param cumQty
     * @param avgPx
     */
    explicit Execution(std::string orderID, std::string execID, ExecutionType execType, OrderStatus ordStatus,
                       std::string symbol, OrderSide side, int leavesQty, int cumQty, double avgPx) :
            OrderID(orderID),
            ExecID(execID),
            ExecType(execType),
            OrdStatus(ordStatus),
            Symbol(symbol),
            Side(side),
            LeavesQty(leavesQty),
            CumQty(cumQty),
            AvgPx(avgPx)
    {}


    int leavesQty() const
    { return LeavesQty; }


    std::string symbol() const
    { return Symbol; }

    std::string exec_id() const
    { return ExecID; }

    std::string order_id() const
    { return OrderID; }


private:
    std::string OrderID;
    std::string ExecID;
    ExecutionType ExecType;
    OrderStatus OrdStatus;
    std::string Symbol;
    OrderSide Side;
    int LeavesQty;
    int CumQty;
    double AvgPx;
};

#endif