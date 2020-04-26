//
// Created by Rohan on 4/25/2020.
//
#define CONFIG_CATCH_MAIN
#include "catch.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include "../include/Order.h"
#include "../include/VenueManager.h"
#include "../include/SprayRouter.h"
#include "../include/AvgLatency.h"
#include "../include/Algorithm.h"
#include "../include/TWAPAlgorithm.h"
#include "../include/TWAPConfig.h"
#include "../include/TimeUtils.h"
#include "../include/VWAPConfig.h"
#include "../include/VWAPAlgorithm.h"


VenueManager createVenueManager();
void testSprayRouter();
void testTWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice);
void testVWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice, std::vector<int> histVol);

template<class T>
std::vector<T> seedVector(int a, int b, int amt);

template<class T>
std::vector<T> seedVector(int a, int b, int amt)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(a, b);
    std::vector<T> histPrice = *(new std::vector<T>());
    histPrice.reserve(amt);
    for (int i = 0; i < amt; i++)
    {
        histPrice.push_back(distr(eng));
    }
    return histPrice;
}

int main()
{
    VenueManager vm = createVenueManager();
    SprayRouter sr(vm);
    std::vector<double> histPrice = seedVector<double>(88, 93, 86400);
    testTWAP(vm, sr, histPrice);
    std::vector<int> histVol = seedVector<int>(20, 40, 86400);
//    testVWAP(vm, sr, histPrice, histVol);
}

void testVWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice, std::vector<int> histVol)
{
    Order order(OrderSide::BUY, "GOOG", 100000, OrderType::MARKET, -1, TimeInForce::DAY);
    long curTime = TimeUtils::getCurTimeEpoch();
    RoutingConfig routingConfig = RoutingConfig::getSOR(RoutingType::SPRAY);
    VWAPConfig* vwapConfig = new VWAPConfig(order, 0, curTime, curTime + 30, 5, routingConfig,histVol, histPrice);
    AlgoConfig* algoConfig = ((AlgoConfig*) vwapConfig);
    VWAPAlgorithm* algo = new VWAPAlgorithm(algoConfig, sr, vm);
    algo->executeAlgo();
}

void testTWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice)
{
    Order order(OrderSide::BUY, "JPM", 100000, OrderType::MARKET, -1, TimeInForce::DAY);
    long curTime = TimeUtils::getCurTimeEpoch();
    RoutingConfig routingConfig = RoutingConfig::getSOR(RoutingType::SPRAY);
    TWAPConfig* twapCfg = new TWAPConfig(order, 0, curTime,curTime + 30, 5, histPrice, routingConfig);
    AlgoConfig* algoConfig = ((AlgoConfig*) twapCfg);
    TWAPAlgorithm* algo = new TWAPAlgorithm(algoConfig, sr, vm);
    algo->executeAlgo();
}

void testSprayRouter(VenueManager vm)
{
    Logger Log("Main");
    SprayRouter sr(vm);

    std::vector<Order> orders;
    for (int i = 50; i < 100; i++)
    {
        bool odd = (i & 1) == 1;
        Order prnt(odd ? OrderSide::BUY : OrderSide::SELL, odd ? "IBM" : "GOOG", i, OrderType::MARKET, odd ? 110 : 1500,
                   TimeInForce::DAY);
        orders.push_back(prnt);
    }

    int ncount = 0;
    for (auto &order : orders)
    {
        Log.info("=======================================");
        Log.info("order-count:", ++ncount);
        sr.route(order);
        Log.info("=======================================");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Mock execution
        order.setQuantity(order.getQuantity() - order.getQuantity());
    }

    Log.info("done.");
}

VenueManager createVenueManager()
{
    VenueRank vr1(0.1, 0.5, 0.1, 0.5, 0.5);
    VenueRank vr2(0.2, 0.5, 0.3, 0.4, 0.2);
    VenueRank vr3(0.3, 0.5, 0.5, 0.3, 0.2);
    VenueRank vr4(0.4, 0.5, 0.4, 0.2, 0.1);
    VenueRank vr5(0.3, 0.5, 0.5, 0.2, 0.3);

    std::vector<Venue> venues;

    Venue v1("DPa", true, {"IBM", "GOOG", "JPM"});
    v1.setRanking("IBM", vr1);
    v1.setRanking("GOOG", vr2);
    v1.setRanking("JPM", vr5);
    v1.setAvgLatency(25);
    venues.push_back(v1);

    Venue v2("DPb", true, {"IBM", "GOOG"});
    v2.setRanking("IBM", vr3);
    v2.setRanking("GOOG", vr4);
    v2.setRanking("JPM", vr3);
    v2.setAvgLatency(35);
    venues.push_back(v2);

    Venue v3("DPc", true, {"IBM", "GOOG", "JPM"});
    v3.setRanking("IBM", vr3);
    v3.setRanking("GOOG", vr3);
    v3.setRanking("JPM", vr4);
    v3.setAvgLatency(5);
    venues.push_back(v3);

    Venue v4("DPd", true, {"IBM", "GOOG", "MSFT", "JPM"});
    v4.setRanking("IBM", vr3);
    v4.setRanking("GOOG", vr2);
    v4.setRanking("MSFT", vr1);
    v4.setRanking("JPM", vr1);
    v1.setAvgLatency(3);
    venues.push_back(v4);

    return *(new VenueManager(venues));
}