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
#include "LeftistLikeHeap.h"

template<typename T>
class SkewHeap : public LeftistLikeHeap<T>{
public:
    ~SkewHeap() {DeleteTree(this->_root); this->_root = nullptr;}
protected:
    BinaryTree<T> _merge(BinaryTree<T> x, BinaryTree<T> y);
};


template<typename T>
BinaryTree<T> SkewHeap<T>::_merge(BinaryTree<T> x, BinaryTree<T> y) {
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;
    if (y->key < x->key)
        std::swap(x, y);
    x->right = _merge(x->right, y);
    std::swap(x->left, x->right);
    x->dist = std::min(LeftistLikeHeap<T>::_dist(x->left), LeftistLikeHeap<T>::_dist(x->right)) + 1;
    return x;
}


#endif /* SkewHeap_h */
