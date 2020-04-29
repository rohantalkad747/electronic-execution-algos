//
// Created by Rohan on 4/28/2020.
//

#ifndef UNTITLED1_SPLAYTREE_H
#define UNTITLED1_SPLAYTREE_H


#include "Node.h"

/**
 * A splay tree optimizes the tree such that the most recently accessed
 * elements are at hovering around at the root. This data structure can
 * efficiently model an order book's price points (given that the prices
 * are not too too volatile).
 *
 * @author Rohan Talkad
 */
template<class T>
class SplayTree
{
private:
    Node<T>* root;
    Node<T>* insert(Node<T>* root, T& val);
    Node<T>* search(Node<T>* root, T& key);
    Node<T>* leftRotate(Node<T>* node);
    Node<T>* rightRotate(Node<T>* node);
};


#endif //UNTITLED1_SPLAYTREE_H
