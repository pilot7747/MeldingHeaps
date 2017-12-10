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
public: class Node;
private: Node head;
    
public:
    BinomialHeap() : head() {}
    void Insert(T val);
    T GetMin();
    T ExtractMin();
    void Union(IHeap<T> &heap);
private:
    static std::size_t safeLeftShift(std::size_t val, int shift);
    void merge(Node *other);
    
public: class Node final {
public:
    T value;
    int rank;
    
    Node *down;
    Node *next;
    
    Node() : value(), rank(-1), down(nullptr), next(nullptr) {}
    
    Node(const T &val) : value(val), rank(0), down(nullptr), next(nullptr) {}
    Node(T &&val) : value(std::move(val)), rank(0), down(nullptr), next(nullptr) {}
    ~Node() {
        delete down;
        delete next;
    }
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

};

template<typename T>
void BinomialHeap<T>::Insert(T val) {
    merge(new BinomialHeap<T>::Node(val));
}

template<typename T>
T BinomialHeap<T>::GetMin() {
    if (head.next == nullptr)
        throw "Empty heap";
    const T *result = nullptr;
    for (const Node *node = head.next; node != nullptr; node = node->next) {
        if (result == nullptr || node->value < *result)
            result = &node->value;
    }
    return *result;
}

template<typename T>
T BinomialHeap<T>::ExtractMin() {
    if (head.next == nullptr)
        throw "Empty heap";
    T *min = nullptr;
    Node *nodeBeforeMin = nullptr;
    for (Node *prevNode = &head; ; ) {
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
    merge(minNode->removeRoot());
    T result = std::move(*min);
    delete minNode;
    return result;
}

template<typename T>
void BinomialHeap<T>::Union(IHeap<T> &other) {
    BinomialHeap<T> &cHeap = static_cast<BinomialHeap<T>&>(other);
    if (&cHeap == this)
        throw "Merging with self";
    merge(cHeap.head.next);
    cHeap.head.next = nullptr;
}

template<typename T>
void BinomialHeap<T>::merge(Node *other) {
    assert(head.rank == -1);
    assert(other == nullptr || other->rank >= 0);
    Node *self = head.next;
    head.next = nullptr;
    Node *prevTail = nullptr;
    Node *tail = &head;
    
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
            tail->rank++;
        } else
            throw "Assertion error";
    }
}

template<typename T>
std::size_t BinomialHeap<T>::safeLeftShift(std::size_t val, int shift) {
    if (shift < 0)
        throw "Negative shift";
    for (int i = 0; i < shift && val != 0; i++)
        val <<= 1;
    return val;
}

#endif /* BinomialHeap2_h */
