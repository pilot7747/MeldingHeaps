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
#include "Testing.h"
#include <fstream>
#include "Stopwatch.h"

class SimpleTests : public ::testing::Test {
public:
    Stopwatch stopwatch;
    Tester tester;
};

class StressTests : public ::testing::Test {
public:
    Stopwatch stopwatch;
    Tester tester;
};


//--------TESTING------

//-------SIMPLE TESTING -----------
TEST_F(SimpleTests, size15) {
    ASSERT_EQ(tester.startTest(15), "passed");
}

TEST_F(SimpleTests, size100) {
    
}

TEST_F(SimpleTests, size1000) {
    
}
TEST_F(SimpleTests, size2000) {

}

//----------STRESS TESTING-----------
TEST_F(StressTests, size5000) {
 
}

TEST_F(StressTests, size6000) {
 
}

TEST_F(StressTests, size7000) {

}

TEST_F(StressTests, size10001) {
    /*stopwatch.start();
    
    std::string check = checkTest<LeftistHeap<int>, StlMeldingHeap<int>>("test10001.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for leftist heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<SkewHeap<int>, StlMeldingHeap<int>>("test10001.txt");
    ASSERT_EQ(check, "ok");
    std::cout << "Time for skew heap: " << stopwatch.circle() << std::endl;
    
    check = checkTest<BinomialHeap<int>, StlMeldingHeap<int>>("test10001.txt");
    ASSERT_EQ(check, "ok");
     std::cout << "Time for binomial heap: " << stopwatch.circle() << std::endl;*/
}


int main(int argc, char **argv) {
    
    //----------GENERATING TESTS. COMMENT THIS SECTION IF TESTS HAVE BEEN GENERATED ALREADY-------
    
    //Simple
    /*std::cout << "Tests generation: " << std::endl;
    
    generateTest(15, "test15.txt");
    generateTest(100, "test100.txt");
    generateTest(1000, "test1000.txt");
    generateTest(2000, "test2000.txt");
    
    //Stress
    generateTest(5000, "test5000.txt");
    generateTest(6000, "test6000.txt");
    generateTest(7000, "test7000.txt");
    generateTest(10001, "test10001.txt");*/
    
    //------------------------------------------------------------
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

