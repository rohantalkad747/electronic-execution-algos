//
// Created by Rohan on 4/4/2020.
//

#include <thread>
#include "../include/VenueManager.h"

void VenueManager::add_venue(const Venue &venue) {
    Log.info("adding venue:", venue.getName());
    Venues.push_back(venue);
}

void VenueManager::sendOrder(std::string &venueName, Order &order) {
    int i = -1;
    Venue *v;
    std::vector<Venue> venues = this->venues(order.getSymbol());
    while (++i < venues.size()) {
        if ((v = &(venues[i]))->getName() == venueName) {
            if (v->isAvailable()) {
                v->acceptOrder(order);
                Log.info("Order sent to venue:", v->getName());
            }
            throw *(new std::exception);
        }
    }
}

void VenueManager::remove_venue(Venue &venue) {
    const std::string &name = venue.getName();
    Log.info("removing venue:", name);
    if (Venues.empty()) {
        return;
    }
    iterateAndRemove(name);
}

void VenueManager::iterateAndRemove(const std::string &name) {
    for (auto it = Venues.begin(); it != Venues.end();) {
        Venue v = *it;
        if (name == v.getName()) {
            Venues.erase(it);
            Log.info("Removed venue: ", name);
        } else {
            it++;
        }
    }
}

std::vector<Venue> VenueManager::venues(const std::string &symbol) {
    std::vector<Venue> venues = SymbolVenues[symbol];
    if (venues.empty()) {
        return venues;
    }
    double totalRank = 0.0;
    for (auto v : venues) {
        VenueRank vr = v.getRanking(symbol);
        totalRank += vr.getRank();
    }
    std::vector<Venue> rankings;
    for (auto v : venues) {
        double rank = v.getRanking(symbol).getRank();
        double executionProbability = rank / totalRank;
        v.setExecutionProbability(executionProbability);
        rankings.push_back(v);
    }
    return rankings;
}

void VenueManager::process_exec(const Execution &exec) {
    Log.info("Received exec:", exec.exec_id());
}

void VenueManager::init() {
    for (const auto &v : Venues) {
        Log.info("v:", v.getName());
        std::vector<std::string> symbols = v.getSymbols();
        for (const auto &symbol : symbols) {
            std::vector<Venue> venues = SymbolVenues[symbol];
            venues.push_back(v);
            Log.info("Adding to symbol:", symbol);
            SymbolVenues[symbol] = venues;
        }
    }
}
