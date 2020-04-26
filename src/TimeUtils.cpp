//
// Created by Rohan on 4/25/2020.
//

#include "../include/TimeUtils.h"

long TimeUtils::getSecondsSinceMidnight()
{
    auto now = std::chrono::system_clock::now();
    time_t tnow = std::chrono::system_clock::to_time_t(now);
    tm *date = std::localtime(&tnow);
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
    auto midnight = std::chrono::system_clock::from_time_t(std::mktime(date));
    return std::chrono::duration_cast<std::chrono::seconds>(now-midnight).count();
}

long TimeUtils::getCurTimeEpoch()
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}