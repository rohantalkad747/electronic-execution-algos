//
// Created by Rohan on 4/25/2020.
//
#define CONFIG_CATCH_MAIN

#include "catch.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include "../src/BasketWave.cpp"
#include "../include/Order.h"
#include "../include/VenueManager.h"
#include "../include/SprayRouter.h"
#include "../include/AvgLatency.h"
#include "../include/TWAPAlgorithm.h"
#include "../include/ParticipateAlgorithm.h"
#include "../include/TWAPConfig.h"
#include "../include/SplayTree.h"
#include "../include/VWAPConfig.h"
#include "../include/VWAPAlgorithm.h"
#include "../include/ParticipateConfig.h"
#include "../include/IcebergConfig.h"
#include "../include/IcebergAlgorithm.h"
#include "../include/Basket.h"
#include "../include/BasketServer.h"
#include "../include/BasketWave.h"


VenueManager createVenueManager();

void testSprayRouter(const VenueManager &vm);

void testTWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice);

void testVWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice, std::vector<int> histVol);

void testPOV(const VenueManager &vm, SprayRouter &sr, std::vector<int> histVol);


void testSplayTree();

void testBasket(const VenueManager &vm);

template<class T>
std::vector<T> seedVector(int a, int b, int amt);

void testAlgos(const VenueManager &vm);

void testIceberg(const VenueManager &manager, const SprayRouter &router);

void testOrderBook(VenueManager manager);

template<class T>
std::vector<T> seedVector(int a, int b, int amt)
{
    std::random_device              rd;
    std::mt19937                    eng(rd());
    std::uniform_int_distribution<> distr(a, b);
    std::vector<T>                  target = *(new std::vector<T>());
    target.reserve(amt);
    for (int i = 0; i < amt; i++)
    {
        target.push_back(distr(eng));
    }
    return target;
}

int main()
{
    VenueManager vm = createVenueManager();
    testAlgos(vm);
//    testSprayRouter(vm);
//    testSplayTree();
//    testOrderBook(vm);
}

void testOrderBook(VenueManager vm)
{
    std::vector venues = vm.venues("JPM");
    Venue       v      = venues[0];
    for (int    i      = 10; i < 20; i++)
    {
        bool  odd = (i & 1) == 1;
        Order prnt(odd ? OrderSide::BUY : OrderSide::SELL, odd ? "JPM" : "GOOG", i, OrderType::LIMIT, odd ? 110 : 1500,
                   TimeInForce::DAY, odd ? LiquidityIndicator::ADD : LiquidityIndicator::REMOVE);
        v.acceptOrder(prnt);
    }
    for (int    i      = 30; i < 50; i++)
    {
        bool  odd = (i & 1) == 1;
        Order prnt(odd ? OrderSide::BUY : OrderSide::SELL, odd ? "JPM" : "GOOG", i, OrderType::MARKET, -1,
                   TimeInForce::DAY, LiquidityIndicator::BOTH);
        v.acceptOrder(prnt);
    }
}

void testAlgos(const VenueManager &vm)
{
    SprayRouter         sr(vm);
    std::vector<double> histPrice = seedVector<double>(88, 93, 86400);
    std::vector<int>    histVol   = seedVector<int>(20, 40, 86400);
//    testTWAP(vm, sr, histPrice);
//    testVWAP(vm, sr, histPrice, histVol);
//    testPOV(vm, sr, histVol);
//    testIceberg(vm, sr);
    testBasket(vm);
}

void testIceberg(const VenueManager &manager, const SprayRouter &router)
{
    Order         order(OrderSide::BUY, "GOOG", 150000, OrderType::LIMIT, 1200.99, TimeInForce::DAY);
    long          curTime        = TimeUtils::getCurTimeEpoch();
    RoutingConfig routingConfig  = RoutingConfig::getSOR(RoutingType::SPRAY);
    auto          *icebergConfig = new IcebergConfig(order, routingConfig, curTime, curTime + 30, 20000, 0.35);
    AlgoConfig    *algoConfig    = ((AlgoConfig *) icebergConfig);
    auto          *algo          = new IcebergAlgorithm(algoConfig, manager);
    algo->executeAlgo();
    while (algo->algoActive())
    {
        algo->triggerNextDisplay();
        std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(500)));
    }
    std::cout << "Iceberg algo executed! " << std::endl;
}

void testVWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice, std::vector<int> histVol)
{
    Order         order(OrderSide::BUY, "GOOG", 100000, OrderType::MARKET, -1, TimeInForce::DAY);
    long          curTime       = TimeUtils::getCurTimeEpoch();
    RoutingConfig routingConfig = RoutingConfig::getSOR(RoutingType::SPRAY);
    auto          *vwapConfig   = new VWAPConfig(order, 0, curTime, curTime + 30, 5, routingConfig, histVol, histPrice);
    AlgoConfig    *algoConfig   = ((AlgoConfig *) vwapConfig);
    auto          *algo         = new VWAPAlgorithm(algoConfig, vm);
    algo->executeAlgo();
}

void testTWAP(const VenueManager &vm, const SprayRouter &sr, std::vector<double> histPrice)
{
    Order         order(OrderSide::BUY, "JPM", 100000, OrderType::MARKET, -1, TimeInForce::DAY);
    long          curTime       = TimeUtils::getCurTimeEpoch();
    RoutingConfig routingConfig = RoutingConfig::getSOR(RoutingType::SPRAY);
    auto          *twapCfg      = new TWAPConfig(order, 0, curTime, curTime + 30, 5, histPrice, routingConfig);
    AlgoConfig    *algoConfig   = ((AlgoConfig *) twapCfg);
    auto          *algo         = new TWAPAlgorithm(algoConfig, vm);
    algo->executeAlgo();
}

void testSprayRouter(VenueManager vm)
{
    Logger      Log("Main");
    SprayRouter sr(vm);

    std::vector<Order> orders;
    for (int           i = 50; i < 100; i++)
    {
        bool  odd = (i & 1) == 1;
        Order prnt(odd ? OrderSide::BUY : OrderSide::SELL, odd ? "IBM" : "GOOG", i, OrderType::MARKET, -1,
                   TimeInForce::DAY);
        orders.push_back(prnt);
    }

    int       ncount = 0;
    for (auto &order : orders)
    {
        Log.info("=======================================");
        Log.info("order-count:", ++ncount);
        sr.route(order);
        Log.info("=======================================");
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

void testPOV(const VenueManager &manager, SprayRouter &sr, std::vector<int> histVol)
{
    Order         order(OrderSide::BUY, "GOOG", 1000, OrderType::LIMIT, 1282, TimeInForce::DAY);
    long          curTime       = TimeUtils::getCurTimeEpoch();
    RoutingConfig routingConfig = RoutingConfig::getSOR(RoutingType::SPRAY);
    auto          *povCOnfig    = new ParticipateConfig(order, 0, curTime, curTime + 600000, 5, routingConfig, histVol,
                                                        0.20);
    AlgoConfig    *algoConfig   = ((AlgoConfig *) povCOnfig);
    auto          *algo         = new ParticipateAlgorithm(algoConfig, manager);
    algo->executeAlgo();
}

void testSplayTree()
{
    auto      *rt = new Node<int>(0);
    for (int  i   = 0; i < 10; i++)
    {
        rt = SplayTree::insert<int>(rt, ((i & 1) == 1) ? i - 1 : i + 1);
    }
    Node<int> *fv = SplayTree::search<int>(rt, 5);
    assert (fv->key == 5);
    Node<int> *zero = SplayTree::search<int>(fv, 0);
    assert (zero->key == 0);
}

void testBasket(const VenueManager &vm)
{
    Raptor                 raptor(vm);
    BasketDB               basketDb;
    BasketServer           bs(raptor, basketDb, BasketServerStatus::ACTIVE);
    Basket                 *basket       = bs.createTradableBasket(
            "QRA90A901J",
            {"IBM", "JPM", "GOOG"},
            {250000, 700000, 31250},
            {OrderSide::BUY, OrderSide::BUY, OrderSide::SELL}
    );
    std::vector<double>    prices        = {315.23, 90.50, 1400.50};
    std::vector<OrderType> orderTypes    = {OrderType::LIMIT, OrderType::LIMIT};
    AlgorithmType          algorithmType = AlgorithmType::NONE;
    auto* logger = new Logger("Test");
    logger->info("WAVE 1: 50% OF THE BASKET");
    bs.createWave(
            basket->getBasketId(),
            0.50,
            new OrderConfig(RoutingConfig::getSOR(RoutingType::SPRAY)),
            &algorithmType,
            prices,
            orderTypes,
            LotSizing::ROUND,
            Rounding::UP
    );
    logger->info("WAVE 2: 25% OF THE BASKET");
    bs.createWave(
            basket->getBasketId(),
            0.25,
            new OrderConfig(RoutingConfig::getSOR(RoutingType::SPRAY)),
            &algorithmType,
            prices,
            orderTypes,
            LotSizing::ROUND,
            Rounding::UP
    );
}

