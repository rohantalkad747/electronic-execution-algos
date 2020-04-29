//
// Created by Rohan on 4/28/2020.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H


template<class T>
class Node
{
public:
    Node<T>(T& val) : key(val)
    {}

    Node<T>* newNode(T& val)
    {
        auto* nd = new Node<T>();
        nd->left = nd->right = nullptr;
        nd->data = val;
        return nd;
    }

    T key;
    Node<T>* left;
    Node<T>* right;
};


#endif //UNTITLED1_NODE_H
