//
// Created by Rohan on 4/28/2020.
//

#ifndef UNTITLED1_SPLAYTREE_H
#define UNTITLED1_SPLAYTREE_H


#include <iostream>
#include "Node.h"

/**
 * A splay tree optimizes its internal structure such that the most recently
 * accessed elements cluster around the root. This data structure can
 * efficiently model an order book's price points (given that the prices
 * are not too too volatile).
 *
 * @author Rohan Talkad
 */
class SplayTree
{
private:
    template<class T> static Node<T>* leftRotate(Node<T> *node)
    {
        Node<T> *right = node->right;
        node->right = right->left;
        right->left = node;
        return right;
    }

    template<class T> static Node<T>* rightRotate(Node<T> *node)
    {
        Node<T> *left = node->left;
        node->left = left->right;
        left->right = node;
        return left;
    }

public:
    template<class T> static
    void printBT(const std::string& prefix, const Node<T>* node, bool isLeft)
    {

        if( node != nullptr )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "|---" : "^---" );

            // print the value of the node
            std::cout << node->key << std::endl;

            // enter the next tree level - left and right branch
            printBT( prefix + (isLeft ? "|   " : "   "), node->left, true);
            printBT( prefix + (isLeft ? "|   " : "   "), node->right, false);
        }
    }

    template<class T> static
    void printBT(const Node<T>* node)
    {
        printBT("", node, false);
    }

    template<class T> static Node<T>* insert(Node<T>* root, T &&val)
    {
        return insert(root, val);
    }


    template<class T> static Node<T>* insert(Node<T>* root, T &val)
    {
        if (root == nullptr)
        {
            return new Node<T>(val);
        }
        root = SplayTree::search<T>(root, val);
        if (root->key == val)
        {
            return root;
        }
        Node<T>* new_root = new Node<T>(val);
        if (root->key > val)
        {
            new_root->right = root;
            new_root->left = root->left;
            root->left = nullptr;
        }
        else
        {
            new_root->left = root;
            new_root->right = root->right;
            root->right = nullptr;
        }
        return new_root;
    }

    template<class T> static Node<T>* search(Node<T> *root, T&& key)
    {
        return search<T>(root, key);
    }

    template<class T> static Node<T>* search(Node<T> *root, T& key)
    {
        if (root == nullptr || root->key == key)
        {
            return root;
        }
        if (root->key > key)
        {
            if (root->left == nullptr)
            {
                return root;
            }
            if (root->left->key > key)
            {
                root->left->left = search<T>(root->left->left, key);
                root = rightRotate<T>(root);
            } else if (root->left->key < key)
            {
                root->left->right = search<T>(root->left->right, key);
                if (root->left->right != nullptr)
                {
                    root->left = leftRotate(root->left);
                }
            }
            if (root->left == nullptr)
            {
                return root;
            }
            return rightRotate<T>(root);
        } else
        {
            if (root->right == nullptr)
            {
                return root;
            }
            if (root->right->key > key)
            {
                root->right->left = search<T>(root->right->left, key);
                if (root->right->left != nullptr)
                {
                    root->right = rightRotate<T>(root->right);
                }
            } else if (root->right->key < key)
            {
                root->right->right = search<T>(root->right->right, key);
                root = leftRotate<T>(root);
            }
            if (root->right == nullptr)
            {
                return root;
            }
            return leftRotate<T>(root);
        }
    }
};


#endif //UNTITLED1_SPLAYTREE_H
