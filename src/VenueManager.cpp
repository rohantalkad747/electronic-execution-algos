//
// Created by Rohan on 4/4/2020.
//

#include "../include/VenueManager.h"

void VenueManager::add_venue(const Venue &venue)
{
    Log.info("adding venue:", venue.getName());
    Venues.push_back(venue);
}

void VenueManager::remove_venue(Venue &venue)
{
    const std::string& name = venue.getName();
    Log.info("removing venue:", name);
    if (Venues.empty())
    {
        return;
    }
    iterateAndRemove(name);
}

void VenueManager::iterateAndRemove(const std::string &name)
{
    for (auto it = Venues.begin(); it != Venues.end(); )
    {
        Venue v = *it;
        if ( name == v.getName())
        {
            Venues.erase(it);
            Log.info("Removed venue: ", name);
        }
        else
        {
            it++;
        }
    }
}

std::vector<Venue> VenueManager::venues(const std::string &symbol)
{
    std::vector<Venue> venues = SymbolVenues[ symbol ];
    if (venues.empty())
    {
        return venues;
    }
    double totalRank = 0.0;
    for (auto v : venues)
    {
        VenueRank vr = v.getRanking( symbol );
        totalRank += vr.getRank();
    }
    std::vector<Venue> rankings;
    for (auto v : venues)
    {
        VenueRank vr = v.getRanking( symbol );
        double executionProbability = vr.getRank() / totalRank;
        v.setExecutionProbability(executionProbability);
        rankings.push_back(v);
        Log.info("Added ranking for venue:", v.getName());
    }
    return rankings;
}

/*
*	Send Order to a Venue (Market)
*/
void VenueManager::send_order(const Venue & venue, const Order & order)
{
    Log.info("order sent to venue:", venue.getName());
}

/*
*	Process Ack/Fill from Venue (Market)
*/
void VenueManager::process_exec(const Execution & exec)
{
    Log.info("recevied exec:", exec.exec_id());
}