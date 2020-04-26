//
// Created by Rohan on 4/5/2020.
//

#ifndef UNTITLED1_VENUE_H
#define UNTITLED1_VENUE_H

#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <thread>
#include <future>
#include "VenueRank.h"
#include "Logger.h"
#include "TimeUtils.h"
#include "Order.h"


class Venue
{
public:
    explicit Venue(std::string name, bool available, std::vector<std::string> symbols)
            : name(name), available(available), symbols(symbols), probability(0.0), avgLatency(0),
              log(*(new Logger("Venue")))
    {}

    bool isAvailable() const
    {
        return available;
    }

    const void acceptOrder(Order &order)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(getAvgLatency()));
        std::string received = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count());
        log.info("Received order at " + name + " at " + received);
    }

    std::vector<std::string> getSymbols() const
    { return symbols; }

    void setExecutionProbability(double p)
    {
        probability = p;
    }

    double getExecutionProbability() const
    {
        return probability;
    }

    VenueRank getRanking(const std::string &symbol)
    {
        return rankMapping[symbol];
    }

    void setRanking(const std::string &symbol, const VenueRank &rank)
    {
        rankMapping[symbol] = rank;
    }

    const std::string &getName() const
    {
        return name;
    }

    double getProbability() const
    {
        return probability;
    }

    long getAvgLatency() const
    {
        return avgLatency;
    }

    void setAvgLatency(long avg)
    {
        avgLatency = avg;
    }

    const std::map<std::string, VenueRank> &getRankMapping() const
    {
        return rankMapping;
    }

private:
    std::string name;
    bool available;
    std::vector<std::string> symbols;
    double probability;
    std::map<std::string, VenueRank> rankMapping;
    long avgLatency;
    Logger log;

    friend std::ostream &operator<<(std::ostream &os, const Venue &venue)
    {
        os << " Venue [" << venue.name << ", " << venue.available << ", ";
        for (const auto &symbol : venue.symbols)
        {
            os << symbol << ", ";
        }
        os << "]";
        return os;
    }
};

#endif //UNTITLED1_VENUE_H
