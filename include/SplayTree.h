//
// Created by Rohan on 4/28/2020.
//

#ifndef UNTITLED1_SPLAYTREE_H
#define UNTITLED1_SPLAYTREE_H


#include "Node.h"

/**
 * A splay tree optimizes its internal structure such that the most recently
 * accessed elements are cluster around the root. This data structure can
 * efficiently model an order book's price points (given that the prices
 * are not too too volatile).
 *
 * @author Rohan Talkad
 */
class SplayTree
{
public:
    template<class T> static Node<T>* insert(Node<T>* root, T& key);
    template<class T> static Node<T>* search(Node<T>* root, T& key);
private:
    template<class T> static Node<T>* leftRotate(Node<T>* node);
    template<class T> static Node<T>* rightRotate(Node<T>* node);
};


#endif //UNTITLED1_SPLAYTREE_H
