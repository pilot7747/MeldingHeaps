//
//  testGenerator.cpp
//  MeldingHeaps
//
//  Created by Никита on 06.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//
#pragma once
#include <cstdio>
#include <random>
#include <string>
#include <vector>
#include <iostream>

std::string generateTest(size_t size, std::ostream &out) {
    std::vector<size_t> heapSizes;
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> getOperation(0, 7);
    std::uniform_int_distribution<int> getNumber(INT_MIN, INT_MAX);
    for (int i = 0; i < size / 1000 + 1; ++i) {
        out << 0 << std::endl ;
        size_t nowSize = 0;
        for (int j = 0; j < 2 * size; ++j) {
            int operation = getOperation(e1);
            if (operation < 6) {
                out << 1 << ' ' << getNumber(e1) << std::endl;
                ++nowSize;
            } else if (operation == 6) {
                if (nowSize > 0)
                    out << 2 << std::endl;
            } else {
                if (nowSize > 0) {
                    out << 3 << std::endl;
                    --nowSize;
                }
            }
        }
        heapSizes.push_back(nowSize);
    }
    return "хуй";
}

int main() {
    
    return 0;
}
