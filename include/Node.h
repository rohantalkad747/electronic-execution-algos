//
// Created by Rohan on 4/28/2020.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H


template<class T>
class Node {
public:
    explicit Node<T>(T &val) : key(val) {}

    explicit Node<T>(T &&val) : key(val) {}

    Node<T> *newNode(T &val) {
        auto *nd = new Node<T>();
        nd->data = val;
        return nd;
    }

    T key;
    // Default
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
};


#endif //UNTITLED1_NODE_H
