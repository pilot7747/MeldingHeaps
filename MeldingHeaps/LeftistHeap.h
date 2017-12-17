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
#include "LeftistLikeHeap.h"

template<typename T>
class LeftistHeap : public LeftistLikeHeap<T>{
public:
    ~LeftistHeap() {DeleteTree(this->_root); this->_root = nullptr;}
protected:
    BinaryTree<T> _merge(BinaryTree<T> x, BinaryTree<T> y) override;
};



template<typename T>
BinaryTree<T> LeftistHeap<T>::_merge(BinaryTree<T> x, BinaryTree<T> y) {
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;
    if (y->key < x->key)
        std::swap(x, y);
    x->right = _merge(x->right, y);
    if (LeftistLikeHeap<T>::_dist(x->right) > LeftistLikeHeap<T>::_dist(x->left)) {
        std::swap(x->left, x->right);
    }
    x->dist = std::min(LeftistLikeHeap<T>::_dist(x->left), LeftistLikeHeap<T>::_dist(x->right)) + 1;
    return x;
}


#endif /* LeftistHeap_h */
