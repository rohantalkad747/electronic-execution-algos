//
// Created by Rohan Talkad on 2020-05-23.
//

#include <numeric>
#include "../include/Basket.h"

int Basket::leaves() const {
    int toTrade = std::accumulate(quantities.begin(), quantities.end(), 0);
    return toTrade - totalTraded;
}