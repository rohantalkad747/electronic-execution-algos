//
// Created by Rohan on 4/14/2020.
//

#include <chrono>
#include "../include/AvgLatency.h"

long AvgLatency::getLatencyAdjustment()
{
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    int index = aTime->tm_hour;
    if (index < this->todayLatency.size())
    {
        this->histLatency[index];
    }
    return 0.3 * this->histLatency[index] + 0.7 * this->todayLatency[index];
}
