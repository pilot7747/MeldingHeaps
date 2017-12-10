//
//  LeftistHeap.h
//  MeldingHeaps
//
//  Created by Никита on 05.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef LeftistHeap_h
#define LeftistHeap_h
#pragma once
#include "IHeap.h"
#include "BinaryTree.h"

template<typename T>
class LeftistHeap : public IHeap<T> {
public:
    void Insert(T key);
    T GetMin();
    T ExtractMin();
    void Union(IHeap<T> &heap);
    LeftistHeap(T key);
    LeftistHeap() {}
    ~LeftistHeap() {DeleteTree(_root); _root = nullptr;}
private:
    BinaryTree<T> _root = nullptr;
    static BinaryTree<T> merge(BinaryTree<T> x, BinaryTree<T> y);
    static size_t dist(BinaryTree<T> tree);
};

template<typename T>
T LeftistHeap<T>::GetMin()  {
    if (_root == nullptr)
        throw "GetMin on empty heap";
    else
        return _root->key;
}

template<typename T>
void LeftistHeap<T>::Union(IHeap<T> &heap) {
    LeftistHeap<T> &cHeap = static_cast<LeftistHeap<T>&>(heap);
    BinaryTree<T> tempRoot = merge(_root, cHeap._root);
    _root = nullptr;
    cHeap._root = nullptr;
    _root = tempRoot;
}

template<typename T>
void LeftistHeap<T>::Insert(T key) {
    BinaryTree<T> tmp = make_binary_tree<T>(key);
    _root = merge(_root, tmp);
}

template<typename T>
size_t LeftistHeap<T>::dist(BinaryTree<T> tree) {
    if (tree == nullptr)
        return 0;
    return tree->dist;
}

template<typename T>
BinaryTree<T> LeftistHeap<T>::merge(BinaryTree<T> x, BinaryTree<T> y) {
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;
    if (y->key < x->key)
        std::swap(x, y);
    x->right = merge(x->right, y);
    if (dist(x->right) > dist(x->left)) {
        /*bool nullFlag = false;
        if (x->left == nullptr)
            nullFlag = true;*/
        std::swap(x->left, x->right);
        /*if (nullFlag)
            x->right = nullptr;*/
    }
    x->dist = std::min(dist(x->left), dist(x->right)) + 1;
    return x;
}

template<typename T>
T LeftistHeap<T>::ExtractMin()  {
    if (_root == nullptr)
        throw "ExtractMin on empty heap";
    else {
        T ans = _root->key;
        _root = merge(_root->left, _root->right);
        return ans;
    }
}


#endif /* LeftistHeap_h */
