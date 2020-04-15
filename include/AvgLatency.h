//
// Created by Rohan on 4/14/2020.
//

#include <vector>
#include <time.h>

#ifndef UNTITLED1_THOR_H
#define UNTITLED1_THOR_H

#endif //UNTITLED1_THOR_H

class AvgLatency
{
public:
    long getLatencyAdjustment();

    void setHistLatency(std::vector<long> hist)
    {
        histLatency = hist;
    }

    void setTodayLatency(std::vector<long> today)
    {
        todayLatency = today;
    }

private:
    std::vector<long> histLatency;
    std::vector<long> todayLatency;
};