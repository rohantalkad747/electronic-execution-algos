//
// Created by Rohan on 4/5/2020.
//

#ifndef UNTITLED1_ORDERSTATUS_H
#define UNTITLED1_ORDERSTATUS_H


enum class OrderStatus : char {
    NEW = '1',
    PARTIAL = '2',
    FILLED =  '4',
    REJECTED = '8',
    EXPIRE = 'C'
};


#endif //UNTITLED1_ORDERSTATUS_H
