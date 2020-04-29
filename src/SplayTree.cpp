//
// Created by Rohan on 4/28/2020.
//

#include "../include/SplayTree.h"

template<class T>
Node<T> *SplayTree::rightRotate(Node<T> *node)
{
    Node<T> *left = node->left;
    node->left = left->right;
    left->right = node;
    return left;
}

template<class T>
Node<T> *SplayTree::leftRotate(Node<T> *node)
{
    Node<T> *right = node->right;
    node->right = right->left;
    right->left = node;
    return right;
}

template<class T>
Node<T> *SplayTree::search(Node<T> *root, T &key)
{
    if (root == nullptr || root->key == key)
    {
        return root;
    }
    if (root->key > key)
    {
        if (root->left == nullptr) return root;

        if (root->left->key > key)
        {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (root->left->key < key)
        {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
            {
                root->left = leftRotate(root->left);
            }
        }
        if (root->left == nullptr)
        {
            return root;
        }
        return rightRotate(root);
    } else
    {
        if (root->right == nullptr)
        {
            return root;
        }
        if (root->right->key > key)
        {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
            {
                root->right = rightRotate(root->right);
            }
        } else if (root->right->key < key)
        {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        if (root->right == nullptr)
        {
            return root;
        }
        return leftRotate(root);
    }
}

template<class T>
Node<T> *SplayTree::insert(Node<T>* root, T &val)
{
    if (root == nullptr)
    {
        return new Node<T>(val);
    }
    if (root->key == val)
    {
        return root;
    }
    Node<T>* new_root = new Node(val);
    if (root->key < val)
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



