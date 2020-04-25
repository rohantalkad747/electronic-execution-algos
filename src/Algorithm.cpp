//
// Created by Rohan on 4/25/2020.
//

#include "../include/Algorithm.h"

void Algorithm::sendToRouter()
{
    Order child(this->algoConfig.getOrder());
    double px = this->getPrice();
    double leaves = this->getLeavesQuantity();
    child.setPrice(px);
    child.setQuantity(leaves);
    this->sprayRouter.route(child);
}


