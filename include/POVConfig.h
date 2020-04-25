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

    float getParticipation() const
    {
        return participation;
    }

    void setParticipation(float participation)
    {
        POVConfig::participation = participation;
    }

private:
    float participation;
public:
    POVConfig(const std::vector<int> &histParticipation, float participation) : histParticipation(histParticipation),
                                                                                participation(participation)
    {}
};
#endif //UNTITLED1_POVCONFIG_H
