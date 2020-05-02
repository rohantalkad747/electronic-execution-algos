//
// Created by Rohan on 4/29/2020.
//

#ifndef UNTITLED1_EXECUTIONSERVICE_H
#define UNTITLED1_EXECUTIONSERVICE_H


#include <atomic>
#include <map>
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
    int execId;

private:
    Logger log = *(new Logger("Fill Service"));
    std::mutex* mtx = new std::mutex();
    void reportExecution(Order& ordOne, Order& fromBook, std::map<std::string, double>& fillTable);
    double resolvePx(const Order &ordOne, const Order &fromBook, std::map<std::string, double>& fillTable) const;
    void buildExec(const Order &ordOne, double& avPx);
public:
    void execute(Order& orderOne, Order&fromBook, std::map<std::string, double>& fillTable);
    void cancel(Order& order);
};


#endif //UNTITLED1_EXECUTIONSERVICE_H
