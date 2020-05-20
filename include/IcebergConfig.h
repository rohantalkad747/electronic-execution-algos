//
// Created by Rohan on 4/27/2020.
//

#ifndef UNTITLED1_ICEBERGCONFIG_H
#define UNTITLED1_ICEBERGCONFIG_H

#include "AlgoConfig.h"

class IcebergConfig : public AlgoConfig {
private:
public:
    IcebergConfig(const Order &order, const RoutingConfig &routingConfig, long startTime, long endTime,
                  int icebergDisplay, double variance = -1) : AlgoConfig(order, routingConfig, startTime, endTime),
                                                              icebergDisplay(icebergDisplay),
                                                              displayVariance(variance) {}

private:
    int icebergDisplay;
public:
    int getIcebergDisplay() const {
        return icebergDisplay;
    }

    void setIcebergDisplay(int icebergDisplay) {
        IcebergConfig::icebergDisplay = icebergDisplay;
    }

    double getDisplayVariance() const {
        return displayVariance;
    }

    void setDisplayVariance(double displayVariance) {
        IcebergConfig::displayVariance = displayVariance;
    }

private:
    double displayVariance;
};

#endif //UNTITLED1_ICEBERGCONFIG_H
