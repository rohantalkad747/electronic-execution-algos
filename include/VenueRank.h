//
// Created by Rohan on 4/5/2020.
//

#define RHTV_TS 1
#define MHTV 2
#define ITV 4
#define PII 8

#ifndef UNTITLED1_VENUERANK_H
#define UNTITLED1_VENUERANK_H


class VenueRank
{
public:
    void setVenueTradingCost(double venueTradingCost)
    {
        venueTradingCost = venueTradingCost;
    }

    void incRouterHistoricTradingVolume(double routerHistoricTradingVolume)
    {
        while ((locks & RHTV_TS) == RHTV_TS);
        locks |= RHTV_TS;
        VenueRank::routerHistoricTradingVolume += routerHistoricTradingVolume;
        locks &= ~RHTV_TS;
    }

    void incMarketHistoricTradingVolume(double marketHistoricTradingVolume)
    {
        while ((locks & MHTV) == MHTV);
        locks |= MHTV;
        VenueRank::marketHistoricTradingVolume += marketHistoricTradingVolume;
        locks &= ~MHTV;
    }

    void incImmediateTradingVolume(double immediateTradingVolume)
    {
        while ((locks & ITV) == ITV);
        locks |= ITV;
        VenueRank::immediateTradingVolume += immediateTradingVolume;
        locks &= ~ITV;
    }

    void incPriceImprovementIndicator(double priceImprovementIndicator)
    {
        while ((locks & PII) == PII);
        locks |= PII;
        VenueRank::priceImprovementIndicator += priceImprovementIndicator;
        locks &= ~PII;
    }

    double getRank() const
    {
        return (venueTradingCost * 0.15) + (routerHistoricTradingVolume * 0.2)
               + (marketHistoricTradingVolume * 0.1) + (priceImprovementIndicator * 0.15)
               + (immediateTradingVolume * 0.4);
    }

    explicit VenueRank() : venueTradingCost(0.0), routerHistoricTradingVolume(0.0),
                           marketHistoricTradingVolume(0.0), immediateTradingVolume(0.0), priceImprovementIndicator(0.0)
    {}

    explicit VenueRank(double vtc, double rhtv, double mhtv, double ita, double pii) :
            venueTradingCost(vtc), routerHistoricTradingVolume(rhtv), marketHistoricTradingVolume(mhtv),
            immediateTradingVolume(ita), priceImprovementIndicator(pii)
    {}

private:

    unsigned volatile char locks = 0;
    double venueTradingCost;
    double routerHistoricTradingVolume;
    double marketHistoricTradingVolume;
    double immediateTradingVolume;
    double priceImprovementIndicator;


};


#endif //UNTITLED1_VENUERANK_H
