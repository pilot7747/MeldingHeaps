//
//  LeftistLikeHeap.h
//  MeldingHeaps
//
//  Created by Nikita Pavlichenko on 16.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef LeftistLikeHeap_h
#define LeftistLikeHeap_h


#pragma once
#include "IHeap.h"
#include "BinaryTree.h"

template<typename T>
class LeftistLikeHeap : public IHeap<T> {
public:
    T GetMin();
    T ExtractMin();
    void Union(IHeap<T> &heap);
    bool Empty();
    void Insert(T key);
    LeftistLikeHeap(T key);
    LeftistLikeHeap() {}
    ~LeftistLikeHeap() {DeleteTree(_root); _root = nullptr;}
protected:
    BinaryTree<T> _root = nullptr;
    virtual BinaryTree<T> _merge(BinaryTree<T> x, BinaryTree<T> y) = 0;
    static size_t _dist(BinaryTree<T> tree);
};

template<typename T>
void LeftistLikeHeap<T>::Insert(T key) {
    BinaryTree<T> tmp = make_binary_tree<T>(key);
    _root = _merge(_root, tmp);
}
template<typename T>
bool LeftistLikeHeap<T>::Empty() {
    return (_root == nullptr);
}
template<typename T>
T LeftistLikeHeap<T>::GetMin()  {
    if (_root == nullptr)
        throw "GetMin on empty heap";
    else
        return _root->key;
}

template<typename T>
void LeftistLikeHeap<T>::Union(IHeap<T> &heap) {
    LeftistLikeHeap<T> &cHeap = static_cast<LeftistLikeHeap<T>&>(heap);
    BinaryTree<T> tempRoot = _merge(_root, cHeap._root);
    _root = nullptr;
    cHeap._root = nullptr;
    _root = tempRoot;
}


template<typename T>
size_t LeftistLikeHeap<T>::_dist(BinaryTree<T> tree) {
    if (tree == nullptr)
        return 0;
    return tree->dist;
}


template<typename T>
T LeftistLikeHeap<T>::ExtractMin()  {
    if (_root == nullptr)
        throw "ExtractMin on empty heap";
    else {
        T ans = _root->key;
        _root = _merge(_root->left, _root->right);
        return ans;
    }
}


#endif /* LeftistLikeHeap_h */
