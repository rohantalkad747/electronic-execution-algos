//
// Created by Rohan on 4/29/2020.
//

#ifndef UNTITLED1_PRICEPOINT_H
#define UNTITLED1_PRICEPOINT_H


#include <vector>
#include <mutex>
#include "Order.h"

class PricePoint
{
public:
    int getVolume() const
    {
        return volume;
    }

    void incVolume(int v)
    {
        PricePoint::volume += v;
    }

    int getSize() const
    {
        return size;
    }

    void incSize(int inc)
    {
        PricePoint::size += inc;
    }

    const std::vector<Order> &getOrders() const
    {
        return orders;
    }

    void setOrders(const std::vector<Order> &orders)
    {
        PricePoint::orders = orders;
    }

    static PricePoint* of(const Order& order)
    {
        PricePoint* p = new PricePoint();
        p->price = order.getPrice();
        return p;
    }

    void addOrder(const Order& order);

    bool operator<(const PricePoint &rhs) const;

    bool operator>(const PricePoint &rhs) const;

    bool operator<=(const PricePoint &rhs) const;

    bool operator>=(const PricePoint &rhs) const;

    bool operator==(const PricePoint &rhs) const;

    bool operator!=(const PricePoint &rhs) const;

private:
    int volume;
    int size;
public:
    double getPrice() const;

    void setPrice(double price);

private:
    double price;
    std::vector<Order> orders;
    std::mutex mtx_;

};



#endif //UNTITLED1_PRICEPOINT_H
