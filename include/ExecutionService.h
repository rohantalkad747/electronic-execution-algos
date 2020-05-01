//
// Created by Rohan on 4/29/2020.
//

#ifndef UNTITLED1_EXECUTIONSERVICE_H
#define UNTITLED1_EXECUTIONSERVICE_H


#include <atomic>
#include "Order.h"
#include "Logger.h"

/**
 * Handles filling orders and reporting executions
 * to a post-execution listener, which routes a FIX
 * message back to the broker.
 */
class ExecutionService
{
private:
    std::atomic_long execId = 0;
    double lastFill;
    Logger log = *(new Logger("Fill Service"));
public:
    void execute(Order& orderOne, Order&fromBook);
    void reportExecution(Order& ordOne, Order& fromBook);
    void cancel(Order &order);
    void buildExec(const Order &ordOne, double avPx);
};


#endif //UNTITLED1_EXECUTIONSERVICE_H
