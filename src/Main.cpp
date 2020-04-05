#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "../include/Order.h"
#include "../include/VenueManager.h"
#include "../include/SerialRouter.h"

VenueManager create_venue_manager();

int main()
{
    Logger Log("Main");

    VenueManager vm = create_venue_manager();

    SerialRouter sr(vm);

    std::vector<Order> orders;
    for (int i = 50; i < 100; i++)
    {
        bool odd = (i & 1) == 1;
        Order prnt(odd ? OrderSide::BUY : OrderSide::SELL, odd ? "IBM" : "GOOG", i, OrderType::MARKET, odd ? 110 : 1500, TimeInForce::DAY);
        orders.push_back(prnt);
    }

    int ncount = 0;
    for (auto & order : orders)
    {
        Log.info("=======================================");
        Log.info("order-count:", ++ncount);
        sr.route( order );
        Log.info("=======================================");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Mock execution
        order.setQuantity(order.getQuantity() - order.getQuantity());
    }

    Log.info("done.");
}

VenueManager create_venue_manager()
{
    VenueRank vr1(0.1, 0.5, 0.1, 0.5, 0.5);
    VenueRank vr2(0.2, 0.5, 0.3, 0.4, 0.2);
    VenueRank vr3(0.3, 0.5, 0.5, 0.3, 0.2);
    VenueRank vr4(0.4, 0.5, 0.4, 0.2, 0.1);

    std::vector<Venue> venues;

    Venue v1( "DPa", true, {"IBM", "GOOG"} );
    v1.setRanking("IBM", vr1);
    v1.setRanking("GOOG", vr2);
    venues.push_back( v1 );

    Venue v2( "DPb", true, {"IBM", "GOOG"} );
    v2.setRanking("IBM", vr3);
    v2.setRanking("GOOG", vr4);
    venues.push_back( v2 );

    Venue v3( "DPc", true, {"IBM", "GOOG"} );
    v3.setRanking("IBM", vr3);
    v3.setRanking("GOOG", vr3);
    venues.push_back( v3 );

    Venue v4( "DPd", true, {"IBM", "GOOG", "MSFT"} );
    v4.setRanking("IBM", vr3);
    v4.setRanking("GOOG", vr2);
    v4.setRanking("MSFT", vr1);
    venues.push_back( v4 );

    VenueManager vm( venues );
    return vm;
}
