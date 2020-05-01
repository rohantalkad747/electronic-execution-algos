//
// Created by Rohan on 4/29/2020.
//

#include <bits/shared_ptr.h>
#include "../include/FillService.h"
#include "../include/Execution.h"

void FillService::execute(Order &orderOne, Order &orderTwo)
{
    if (!orderOne.isTerminal() && !orderTwo.isTerminal())
    {
        int trgtQuantity = orderOne.getQuantity();
        int bookEntryQuantity = orderTwo.getQuantity();
        int executed = std::abs(trgtQuantity - bookEntryQuantity);
        orderOne.setQuantity(trgtQuantity - executed);
        orderTwo.setQuantity(bookEntryQuantity - executed);
        if (executed != 0)
        {
            reportExecution(executed, orderOne, orderTwo);
        }
    }
}

void FillService::reportExecution(int quantity, Order &ordOne, Order &ordTwo)
{
    std::shared_ptr<Execution*> exec = std::make_shared<>(new Execution());
}
