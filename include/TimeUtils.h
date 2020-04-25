//
// Created by Rohan on 4/25/2020.
//

#ifndef UNTITLED1_TIMEUTILS_H
#define UNTITLED1_TIMEUTILS_H


#include <chrono>

class TimeUtils
{
public:
    static long getCurTimeEpochMs()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    static void wait(long ms)
    {
        while (TimeUtils::getCurTimeEpochMs() <= ms);
    }
};


#endif //UNTITLED1_TIMEUTILS_H
