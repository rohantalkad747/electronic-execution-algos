//
// Created by Rohan on 4/29/2020.
//

#include "../include/PricePoint.h"

void PricePoint::addOrder(const Order &order)
{
    std::lock_guard grd(*(this->mtx_));
    int quantity = order.getQuantity();
    this->incSize(quantity);
    this->incVolume(quantity);
    this->orders.push_back(order);
}

bool PricePoint::operator>(const PricePoint &rhs) const
{
    return price > rhs.price;
}

bool PricePoint::operator<(const PricePoint &rhs) const
{
    return price < rhs.price;
}

bool PricePoint::operator==(const PricePoint &rhs) const
{
    return price == rhs.price;
}

bool PricePoint::operator!=(const PricePoint &rhs) const
{
    return rhs.price != this->price;
}

bool PricePoint::operator<=(const PricePoint &rhs) const
{
    return this->price <= rhs.price;
}

bool PricePoint::operator>=(const PricePoint &rhs) const
{
    return this->price >= rhs.price;
}

double PricePoint::getPrice() const
{
    return price;
}

void PricePoint::setPrice(double price)
{
    PricePoint::price = price;
}
