//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_POVCONFIG_H
#define UNTITLED1_POVCONFIG_H

#include <vector>
#include "TimingContext.h"

class POVConfig : public TimingContext
{
private:
    std::vector<int> histParticipation;
public:
    const std::vector<int> &getHistParticipation() const
    {
        return histParticipation;
    }

    void setHistParticipation(const std::vector<int> &histParticipation)
    {
        POVConfig::histParticipation = histParticipation;
    }

    double getParticipation() const
    {
        return participation;
    }

    void setParticipation(double participation)
    {
        POVConfig::participation = participation;
    }

    /**
     *
     * @param order
     * @param initialDelay
     * @param startTime
     * @param endTime
     * @param interval
     * @param routingType
     * @param histParticipation
     * @param participation
     */
    POVConfig(const Order &order, long initialDelay, long startTime, long endTime, long interval,
              const RoutingConfig &routingType, const std::vector<int> &histParticipation, double participation)
            : TimingContext(order, initialDelay, startTime, endTime, interval, routingType),
              histParticipation(histParticipation), participation(participation)
    {}

private:
    double participation;
};

#endif //UNTITLED1_POVCONFIG_H
