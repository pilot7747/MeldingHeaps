//
//  SkewHeap.h
//  MeldingHeaps
//
//  Created by Никита on 10.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef SkewHeap_h
#define SkewHeap_h

#pragma once
#include "IHeap.h"
#include "BinaryTree.h"

template<typename T>
class SkewHeap : public IHeap<T> {
public:
    void Insert(T key);
    T GetMin();
    T ExtractMin();
    void Union(IHeap<T> &heap);
    SkewHeap(T key);
    SkewHeap() {}
    ~SkewHeap() {DeleteTree(_root); _root = nullptr;}
private:
    BinaryTree<T> _root = nullptr;
    static BinaryTree<T> merge(BinaryTree<T> x, BinaryTree<T> y);
    static size_t dist(BinaryTree<T> tree);
};

template<typename T>
T SkewHeap<T>::GetMin()  {
    if (_root == nullptr)
        throw "GetMin on empty heap";
    else
        return _root->key;
}

template<typename T>
void SkewHeap<T>::Union(IHeap<T> &heap) {
    SkewHeap<T> &cHeap = static_cast<SkewHeap<T>&>(heap);
    BinaryTree<T> tempRoot = merge(_root, cHeap._root);
    _root = nullptr;
    cHeap._root = nullptr;
    _root = tempRoot;
}

template<typename T>
void SkewHeap<T>::Insert(T key) {
    BinaryTree<T> tmp = make_binary_tree<T>(key);
    _root = merge(_root, tmp);
}

template<typename T>
size_t SkewHeap<T>::dist(BinaryTree<T> tree) {
    if (tree == nullptr)
        return 0;
    return tree->dist;
}

template<typename T>
BinaryTree<T> SkewHeap<T>::merge(BinaryTree<T> x, BinaryTree<T> y) {
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;
    if (y->key < x->key)
        std::swap(x, y);
    x->right = merge(x->right, y);
    std::swap(x->left, x->right);
    x->dist = std::min(dist(x->left), dist(x->right)) + 1;
    return x;
}

template<typename T>
T SkewHeap<T>::ExtractMin()  {
    if (_root == nullptr)
        throw "ExtractMin on empty heap";
    else {
        T ans = _root->key;
        _root = merge(_root->left, _root->right);
        return ans;
    }
}


#endif /* SkewHeap_h */
