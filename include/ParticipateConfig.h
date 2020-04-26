//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_PARTICIPATECONFIG_H
#define UNTITLED1_PARTICIPATECONFIG_H

#include <vector>
#include "TimingContext.h"

class ParticipateConfig : public TimingContext
{
private:
    std::vector<int> histVolume;
public:
    const std::vector<int> &getHistVolume() const
    {
        return histVolume;
    }

    void setHistVolume(const std::vector<int> &histVolume)
    {
        ParticipateConfig::histVolume = histVolume;
    }

public:
    double getParticipation() const
    {
        return participation;
    }

    void setParticipation(double participation)
    {
        ParticipateConfig::participation = participation;
    }

    /**
     *
     * @param order
     * @param initialDelay
     * @param startTime
     * @param endTime
     * @param interval
     * @param routingType
     * @param participation
     */
    ParticipateConfig(const Order &order, long initialDelay, long startTime, long endTime, long interval,
                      const RoutingConfig &routingType, std::vector<int> histVolume, double participation)
            : TimingContext(order, initialDelay, startTime, endTime, interval, routingType),
              histVolume(histVolume), participation(participation)
    {}

private:
    double participation;
};

#endif //UNTITLED1_PARTICIPATECONFIG_H
