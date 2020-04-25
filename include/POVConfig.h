//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_POVCONFIG_H
#define UNTITLED1_POVCONFIG_H

#include <vector>

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

private:
    double participation;
public:
    POVConfig(const std::vector<int> &histParticipation, double participation) : histParticipation(histParticipation),
                                                                                participation(participation)
    {}
};
#endif //UNTITLED1_POVCONFIG_H
