//
// Created by Rohan on 4/29/2020.
//

#ifndef UNTITLED1_FILLSERVICE_H
#define UNTITLED1_FILLSERVICE_H


#include "Order.h"

/**
 * Handles filling orders and reporting executions
 * to a post-execution listener, which routes a FIX
 * message back to the broker.
 */
class FillService
{
public:
    void execute(Order& orderOne, Order&orderTwo);
    void reportExecution(int quantity, Order& ordOne, Order& ordTwo);
};


#endif //UNTITLED1_FILLSERVICE_H
