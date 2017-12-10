//
//  main.cpp
//  MeldingHeaps
//
//  Created by Nikita Pavlichenko on 04.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//
#include <iostream>
#include <gtest/gtest.h>
#include "BinomialHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include "StlMeldingHeap.h"
#include "IHeap.h"
#include "tests.h"
#include <fstream>
#include "Stopwatch.h"

class SimpleTests : public ::testing::Test {
public:
    Stopwatch stopwatch;
};

class StressTests : public ::testing::Test {
public:
    Stopwatch stopwatch;
};


//--------TESTING------

//-------SIMPLE TESTING -----------
TEST_F(SimpleTests, size15) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test15.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test15.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test15.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}

TEST_F(SimpleTests, size100) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test100.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test100.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test100.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}

TEST_F(SimpleTests, size1000) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test1000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test1000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test1000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}
TEST_F(SimpleTests, size2000) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test2000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test2000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test2000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}

//----------STRESS TESTING-----------
TEST_F(StressTests, size5000) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test5000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test5000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test5000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}

TEST_F(StressTests, size6000) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test6000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test6000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test6000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}

TEST_F(StressTests, size7000) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test7000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test7000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test7000.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}

TEST_F(StressTests, size10001) {
    stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test10001.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test10001.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test10001.txt");
    ASSERT_EQ(check, "ok");
     std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;
}


int main(int argc, char **argv) {
    
    //----------GENERATING TESTS. COMMENT THIS SECTION IF TESTS HAVE BEEN GENERATED ALREADY-------
    
    //Simple
    generateTest(15, "test15.txt");
    generateTest(100, "test100.txt");
    generateTest(1000, "test1000.txt");
    generateTest(1001, "test2000.txt");
    
    //Stress
    generateTest(5000, "test5000.txt");
    generateTest(6000, "test6000.txt");
    generateTest(7000, "test7000.txt");
    generateTest(10001, "test10001.txt");
    
    //------------------------------------------------------------
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

