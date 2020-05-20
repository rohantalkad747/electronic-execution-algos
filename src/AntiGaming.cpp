//
// Created by Rohan on 4/26/2020.
//

#include "../include/AntiGaming.h"

long AntiGaming::randomize(long a, long b)
{
    static std::random_device       rd;
    std::mt19937                    eng(rd());
    std::uniform_int_distribution<> distr(a, b);
    return distr(eng);
}