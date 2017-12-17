//
//  BinomialHeap.h
//  MeldingHeaps
//
//  Created by Nikita Pavlichenko on 10.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef BinomialHeap2_h
#define BinomialHeap2_h
#pragma once
#include "IHeap.h"
#include <cassert>
#include <cstddef>
#include <utility>



template <typename T>
class BinomialHeap final : public IHeap<T> {
public:
    BinomialHeap() : _head() {}
    ~BinomialHeap() {
        _DeleteTree(_head.next);
        _DeleteTree(_head.down);
    }
    void Insert(T val);
    T GetMin();
    T ExtractMin();
    void Union(IHeap<T> &heap);
    bool Empty();
    class Node final {
    public:
        T value;
        int rank;
        Node *down;
        Node *next;
        Node() : value(), rank(-1), down(nullptr), next(nullptr) {}
        Node(const T &val) : value(val), rank(0), down(nullptr), next(nullptr) {}
        Node(T &&val) : value(std::move(val)), rank(0), down(nullptr), next(nullptr) {}
        Node *removeRoot() {
            assert(next == nullptr);
            Node *node = down;
            down = nullptr;
            Node *result = nullptr;
            while (node != nullptr) {
                Node *next = node->next;
                node->next = result;
                result = node;
                node = next;
            }
            return result;
        }
    };
    
private:
    void _DeleteTree(Node* root);
    void _merge(Node *other);
    Node _head;
};

template<typename T>
void BinomialHeap<T>::Insert(T val) {
    _merge(new BinomialHeap<T>::Node(val));
}

template<typename T>
bool BinomialHeap<T>::Empty() {
    return (_head.next == nullptr);
}

template<typename T>
T BinomialHeap<T>::GetMin() {
    if (_head.next == nullptr)
        throw "Empty heap";
    const T *result = nullptr;
    for (const Node *node = _head.next; node != nullptr; node = node->next) {
        if (result == nullptr || node->value < *result)
            result = &node->value;
    }
    return *result;
}

template<typename T>
T BinomialHeap<T>::ExtractMin() {
    if (_head.next == nullptr)
        throw "Empty heap";
    T *min = nullptr;
    Node *nodeBeforeMin = nullptr;
    for (Node *prevNode = &_head; ; ) {
        Node *node = prevNode->next;
        if (node == nullptr)
            break;
        if (min == nullptr || node->value < *min) {
            min = &node->value;
            nodeBeforeMin = prevNode;
        }
        prevNode = node;
    }
    assert(min != nullptr && nodeBeforeMin != nullptr);
    
    Node *minNode = nodeBeforeMin->next;
    assert(min == &minNode->value);
    nodeBeforeMin->next = minNode->next;
    minNode->next = nullptr;
    _merge(minNode->removeRoot());
    T result = std::move(*min);
    delete minNode;
    return result;
}

template<typename T>
void BinomialHeap<T>::Union(IHeap<T> &other) {
    BinomialHeap<T> &cHeap = static_cast<BinomialHeap<T>&>(other);
    if (&cHeap == this)
        throw "Merging with self";
    _merge(cHeap._head.next);
    cHeap._head.next = nullptr;
}

template<typename T>
void BinomialHeap<T>::_merge(Node *other) {
    assert(_head.rank == -1);
    assert(other == nullptr || other->rank >= 0);
    Node *self = _head.next;
    _head.next = nullptr;
    Node *prevTail = nullptr;
    Node *tail = &_head;
    
    while (self != nullptr || other != nullptr) {
        Node *node;
        if (other == nullptr || (self != nullptr && self->rank <= other->rank)) {
            node = self;
            self = self->next;
        } else {
            node = other;
            other = other->next;
        }
        node->next = nullptr;
        
        assert(tail->next == nullptr);
        if (tail->rank < node->rank) {
            prevTail = tail;
            tail->next = node;
            tail = node;
        } else if (tail->rank == node->rank + 1) {
            assert(prevTail != nullptr);
            node->next = tail;
            prevTail->next = node;
            prevTail = node;
        } else if (tail->rank == node->rank) {
            if (node->value < tail->value) {
                std::swap(node->value, tail->value);
                std::swap(node->down, tail->down);
            }
            node->next = tail->down;
            tail->down = node;
            ++tail->rank;
        } else
            throw "Assertion error";
    }
}

template<typename T>
void BinomialHeap<T>::_DeleteTree(BinomialHeap<T>::Node* root) {
    if (root == nullptr)
        return;
    if(root->next != nullptr) _DeleteTree(root->next);
    if(root->down != nullptr) _DeleteTree(root->down);
    delete root;
}

#endif /* BinomialHeap2_h */
