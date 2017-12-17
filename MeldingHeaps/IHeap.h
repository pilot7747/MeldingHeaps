//
//  IHeap.h
//  MeldingHeaps
//
//  Created by Nikita Pavlichenko on 04.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#pragma once
template<typename T>
class IHeap {
public:
    virtual void Insert(T key) = 0;
    virtual T GetMin() = 0;
    virtual T ExtractMin() = 0;
    virtual void Union(IHeap<T> &heap) = 0;
    virtual bool Empty() = 0;
    virtual ~IHeap() {};
};
