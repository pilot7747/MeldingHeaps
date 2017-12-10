//
//  testGenerator.h
//  MeldingHeaps
//
//  Created by Никита on 09.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef tests_h
#define tests_h

#pragma once
#include <cstdio>
#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

void generateTest(size_t size, std::string filename) {
    std::ofstream out;
    out.open(filename);
    std::vector<size_t> heapSizes;
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> getOperation(0, 7);
    std::uniform_int_distribution<int> getNumber(INT_MIN, INT_MAX);
    out << size / 1000 + 1 << std::endl;
    for (int i = 0; i < size / 1000 + 1; ++i) {
        out << 0 << std::endl << 2 * size << std::endl ;
        size_t nowSize = 0;
        for (int j = 0; j < 2 * size; ++j) {
            int operation = getOperation(e1);
            if (operation < 6) {
                out << 1 << ' ' << getNumber(e1) << std::endl;
                ++nowSize;
            } else if (operation == 6) {
                if (nowSize > 0)
                    out << 2 << std::endl;
                else
                    --j;
            } else {
                if (nowSize > 0) {
                    out << 3 << std::endl;
                    --nowSize;
                }
                else
                    --j;
            }
        }
        heapSizes.push_back(nowSize);
    }
    size_t nowSize = heapSizes[0];
    for (int i = 0; i < heapSizes.size() - 1; ++i) {
        out << 4 << ' ' << i + 1 << std::endl;
        nowSize += heapSizes[i + 1];
        out << nowSize / 2 << std::endl;
        size_t sz = nowSize / 2;
        for (int j = 0; j < sz; ++j) {
            int operation = getOperation(e1);
            if (operation < 6) {
                out << 1 << ' ' << getNumber(e1) << std::endl;
                ++nowSize;
            } else if (operation == 6) {
                if (nowSize > 0)
                    out << 2 << std::endl;
                else
                    --j;
            } else {
                if (nowSize > 0) {
                    out << 3 << std::endl;
                    --nowSize;
                }
                else
                    --j;
            }
        }
    }
    out.close();
    //return "test" + std::to_string(number) + ".txt";
}

template<class T, class stl>
std::string checkTest(const std::string filename) {
    std::ios_base::sync_with_stdio(false);
    std::ifstream ifs;
    ifs.open(filename);
    //std::freopen(filename.c_str(), "r", stdin);
    //std::cout << filename;
    int n;
    //using std::ifs;
    int steps = 0;
    ifs >> n; ++steps;
    std::vector<T> heaps(n);
    std::vector<stl> stlHeaps(n);
    for (int k = 0; k < n; ++k) {
        int command;
        ifs >> command; ++steps;
        if (command == 0) {
            size_t numOfcom;
            ifs >> numOfcom; ++steps;
            for (int i = 0; i < numOfcom; ++i) {
                ifs >> command; ++steps;
                if (command == 1) {
                    int num;
                    ifs >> num;
                    heaps[k].Insert(num);
                    stlHeaps[k].Insert(num);
                } else if (command == 2) {
                    int res = heaps[k].GetMin();
                    int ans = stlHeaps[k].GetMin();
                    if (res != ans) {
                        std::string error = "Error on line "; error += steps; error += "on operation "; error += command; error += ". Expected "; error += ans; error += " instead of "; error += res; error += ".";
                        ifs.close();
                        return error;
                    }
                } else {
                    int res = heaps[k].ExtractMin();
                    int ans = stlHeaps[k].ExtractMin();
                    if (res != ans) {
                        std::string error = "Error on line "; error += steps; error += "on operation "; error += command; error += ". Expected "; error += ans; error += " instead of "; error += res; error += ".";
                        ifs.close();
                        return error;
                    }
                }
            }
            //heaps.push_back(heap);
            //stlHeaps.push_back(stlHeap);
        }
    }
    for (int k = 0; k < heaps.size() - 1; ++k) {
        int com, heapNum;
        ifs >> com >> heapNum; ++steps;
        heaps[0].Union(heaps[heapNum]);
        stlHeaps[0].Union(stlHeaps[heapNum]);
        int numOfComs;
        ifs >> numOfComs; ++steps;
        for (int i = 0; i < numOfComs; ++i) {
            int command;
            ifs >> command; ++steps;
            if (command == 1) {
                int num;
                ifs >> num;
                heaps[0].Insert(num);
                stlHeaps[0].Insert(num);
            } else if (command == 2) {
                int res = heaps[0].GetMin();
                int ans = stlHeaps[0].GetMin();
                if (res != ans) {
                    std::string error = "Error on line "; error += steps; error += "on operation "; error += command; error += ". Expected "; error += ans; error += " instead of "; error += res; error += ".";
                    ifs.close();
                    return error;
                }
            } else {
                int res = heaps[0].ExtractMin();
                int ans = stlHeaps[0].ExtractMin();
                if (res != ans) {
                    std::string error = "Error on line "; error += steps; error += "on operation "; error += command; error += ". Expected "; error += ans; error += " instead of "; error += res; error += ".";
                    ifs.close();
                    return error;
                }
            }
        }
    }
    //
    ifs.close();
    return "ok";
}

#endif /* tests_h */
