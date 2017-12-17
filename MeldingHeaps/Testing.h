//
//  Testing.h
//  MeldingHeaps
//
//  Created by Никита on 16.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef Testing_h
#define Testing_h
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "IHeap.h"
#include "StlMeldingHeap.h"
#include "Stopwatch.h"

struct Operation {
    int addingNum;
    bool Add = false;
    bool GetMin = false;
    bool ExtractMin = false;
    
    void createRandomOperation(size_t &nowSize) {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> getOperation(0, 7);
        std::uniform_int_distribution<int> getNumber(INT_MIN, INT_MAX);
        int operation = getOperation(e1); //Getting number of operation
        //We want more addition operations than getting or extracting the minimum. So we use 1-6 numbers for additions, 7 for getting the minimum and 8 for extracting the minimum.
        if (operation < 6 || nowSize == 0) {
            addingNum = getNumber(e1);
            Add = true;
            ++nowSize;
        } else if (operation == 6) {
                GetMin = true;
        } else {
            ExtractMin = true;
            --nowSize;
        }
    }
};

typedef std::vector<Operation> Test;


class TestGenerator {
public:
    Test createRandomTest(size_t size) {
        Test t;
        size_t nowSize = 0;
        for (int i = 0; i < size; ++i) {
            Operation op;
            op.createRandomOperation(nowSize);
            t.push_back(op);
        }
        return t;
    }
    Test randomAdding(size_t size) {
        Test t;
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> getNumber(INT_MIN, INT_MAX);
        for (int i = 0; i < size; ++i) {
            Operation op;
            op.Add = true;
            op.addingNum = getNumber(e1);
            t.push_back(op);
        }
        return t;
    }
    
    Test consecutiveAdding(size_t size) {
        Test t;
        for (int i = 0; i < size; ++i) {
            Operation op;
            op.Add = true;
            op.addingNum = i;
            t.push_back(op);
        }
        return t;
    }
    
    Test stableAdding(size_t size, int num) {
        Test t;
        for (int i = 0; i < size; ++i) {
            Operation op;
            op.Add = true;
            op.addingNum = num;
            t.push_back(op);
        }
        return t;
    }
};

struct TestResult {
    bool passed = true;
    double time = 0;
    void comb(const TestResult &res) {
        passed = (passed && res.passed);
        time += res.time;
    }
};

class TestChecker {
public:
     TestResult testPassed(IHeap<int> *heap, StlMeldingHeap<int> *example, Test test) {
         TestResult ans;
         Stopwatch stopwatch;
         stopwatch.start();
         std::vector<int> heapAns = doTest(heap, test);
         ans.time = stopwatch.circle();
         std::vector<int> answer = doTest(example, test);
         ans.passed = (heapAns == answer);
         return ans;
    }
    TestResult clearing(IHeap<int> *heap, StlMeldingHeap<int> *example) {
        TestResult ans;
        Stopwatch stopwatch;
        stopwatch.start();
        std::vector<int> heapAns;
        while (!heap->Empty()) {
            heapAns.push_back(heap->ExtractMin());
        }
        ans.time = stopwatch.circle();
        
        std::vector<int> answer;
        while (!example->Empty()) {
            answer.push_back(example->ExtractMin());
        }
        ans.passed = (heapAns == answer);
        return ans;
    }
private:
    std::vector<int> doTest(IHeap<int> *heap, Test test) {
        std::vector<int> ans;
        for (Test::iterator it = test.begin(); it != test.end(); ++it) {
            if (it->Add) {
                heap->Insert(it->addingNum);
            } else if (it->GetMin) {
                ans.push_back(heap->GetMin());
            } else {
                ans.push_back(heap->ExtractMin());
            }
        }
        return ans;
    }
};

class Tester {
public:
    std::string startTest(size_t size) {
        const size_t optimalHeapNum = 10;
        std::vector<IHeap<int>*> leftist(optimalHeapNum);
        std::vector<IHeap<int>*> skew(optimalHeapNum);
        std::vector<IHeap<int>*> binomial(optimalHeapNum);
        for (int i = 0; i < optimalHeapNum; ++i) {
            LeftistHeap<int> lef;
            /*IHeap<int> *p = &lef;
            p->Insert(1);*/
            SkewHeap<int> skw;
            BinomialHeap<int> bnml;
            leftist[i] = new LeftistHeap<int>();
            skew[i] = new SkewHeap<int>();
            binomial[i] = new BinomialHeap<int>();
        }
        TestResult res;
        res = fullyRandom(leftist, size);
        if (!res.passed)
            return "LeftisHeap has a bug";
        std::cout << "Time for leftist heap: " << res.time << std::endl;
        
        res = fullyRandom(skew, size);
        if (!res.passed)
            return "SkewHeap has a bug";
        std::cout << "Time for skew heap: " << res.time << std::endl;
        
        res = fullyRandom(binomial, size);
        if (!res.passed)
            return "BinomialHeap has a bug";
        std::cout << "Time for binomial heap: " << res.time << std::endl;
        
        res = withClearing(leftist, size);
        if (!res.passed)
            return "LeftisHeap has a bug";
        std::cout << "Time for leftist heap: " << res.time << std::endl;
        
        res = withClearing(skew, size);
        if (!res.passed)
            return "SkewHeap has a bug";
        std::cout << "Time for skew heap: " << res.time << std::endl;
        
        res = withClearing(binomial, size);
        if (!res.passed)
            return "BinomialHeap has a bug";
        std::cout << "Time for binomial heap: " << res.time << std::endl;
        
        return "passed";
    }
    
private:
    TestResult fullyRandom(std::vector<IHeap<int>*> &heaps, size_t size) {
        return randomOrWithClearing(heaps, size, 0);
    }
    //--Same but with fully clearing of heap--
    TestResult withClearing(std::vector<IHeap<int>*> &heaps, size_t size) {
       return randomOrWithClearing(heaps, size, 1);
    }
    TestResult randomOrWithClearing(std::vector<IHeap<int>*> &heaps, size_t size, int type) {
        TestResult ans;
        ans.passed = true;
        std::vector<StlMeldingHeap<int>*> exampleHeaps(heaps.size());
        std::vector<StlMeldingHeap<int>*>::iterator exmpIt = exampleHeaps.begin();
        for (; exmpIt != exampleHeaps.end(); ++exmpIt) {
            *exmpIt = new StlMeldingHeap<int>();
        }
        exmpIt = exampleHeaps.begin() + 1;
        for (std::vector<IHeap<int>*>::iterator it = heaps.begin() + 1; it != heaps.end(); ++it) {
            if (heaps.front()->Empty()) {
                Test t = _generator.createRandomTest(size);
                TestResult res;
                res = _checker.testPassed(heaps.front(), exampleHeaps.front(), t);
                ans = res;
            } else {
                Test t = _generator.createRandomTest(size);
                TestResult res;
                res = _checker.testPassed(*it, *exmpIt, t);
                ans.comb(res);
                
                heaps.front()->Union(**it);
                exampleHeaps.front()->Union(**exmpIt);
                if (type == 0) {
                    t = _generator.createRandomTest(size / 2);
                    res = _checker.testPassed(heaps.front(), exampleHeaps.front(), t);
                } else if (type == 1) {
                    res = _checker.clearing(heaps.front(), exampleHeaps.front());
                }
                ans.comb(res);
            }
            ++exmpIt;
        }
        return ans;
    }
    TestGenerator _generator;
    TestChecker _checker;
};
#endif /* Testing_h */
