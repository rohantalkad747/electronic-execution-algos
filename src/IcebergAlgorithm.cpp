//
// Created by Rohan on 4/27/2020.
//

#include "../include/IcebergAlgorithm.h"
#include "../include/AntiGaming.h"
#include "../include/IcebergConfig.h"


void IcebergAlgorithm::executeAlgo()
{
    init();
    triggerNextDisplay();
}

void IcebergAlgorithm::triggerNextDisplay()
{
    if (this->algoActive())
    {
        this->sendToRouter();
    }
}

void IcebergAlgorithm::init()
{
    auto   *icebergConfig = dynamic_cast<IcebergConfig *>(this->algoConfig);
    int    display        = icebergConfig->getIcebergDisplay();
    double variance       = icebergConfig->getDisplayVariance();
    if (variance > 0)
    {
        int delta = variance * display;
        this->upper = display + delta;
        this->lower = display - delta;
    }
}


double IcebergAlgorithm::getPrice()
{
    return this->algoConfig->getOrder().getPrice();
}

int IcebergAlgorithm::getLeavesQuantity()
{
    auto *icebergConfig = dynamic_cast<IcebergConfig *>( this->algoConfig);
    int  display;
    int  rawDisplay     = icebergConfig->getIcebergDisplay();
    if (icebergConfig->getDisplayVariance() > 0)
    {
        display = AntiGaming::randomize(this->lower, this->upper);
    }
    else
    {
        display = rawDisplay;
    }
    return std::min(display, this->algoConfig->getOrder().getQuantity() - this->sharesTraded);
}
