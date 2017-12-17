//
//  StlMeldingHeap.h
//  MeldingHeaps
//
//  Created by Nikita Pavlichenko on 06.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef StlMeldingHeap_h
#define StlMeldingHeap_h

#pragma once
#include <set>

template<typename T>
class StlMeldingHeap : public IHeap<T> {
public:
    void Insert(T key);
    T GetMin();
    T ExtractMin();
    void Union(IHeap<T> &heap);
    bool Empty();
    StlMeldingHeap(T key);
    StlMeldingHeap() {}
    ~StlMeldingHeap() {}
private:
    std::set<T> _container;
};

template<typename T>
bool StlMeldingHeap<T>::Empty() {
    return _container.empty();
}
template<typename T>
void StlMeldingHeap<T>::Union(IHeap<T> &heap) {
    StlMeldingHeap &tempHeap = static_cast<StlMeldingHeap&>(heap);
    _container.insert(tempHeap._container.begin(), tempHeap._container.end());
    tempHeap._container.clear();
}

template<typename T>
T StlMeldingHeap<T>::GetMin() {
    if (_container.size() == 0)
        throw "GetMin on empty heap";
    return *_container.begin();
}

template<typename T>
T StlMeldingHeap<T>::ExtractMin() {
    if (_container.size() == 0)
        throw "ExtractMin on empty heap";
    T ans = *_container.begin();
    _container.erase(_container.begin());
    return ans;
}

template<typename T>
void StlMeldingHeap<T>::Insert(T key) {
    _container.insert(key);
}
#endif /* StlMeldingHeap_h */
