// squarer_test.cpp  SKELETON
// Glenn G. Chappell
// 2023-11-28
//
// For CS 311 Fall 2023
// Test program for class Squarer
// For Assignment 8, Exercise B
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, squarer.hpp

// Includes for code to be tested
#include "squarer.hpp"       // For class Squarer

// Includes for the "doctest" unit-testing framework
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
                             // doctest writes main for us
#include "doctest.h"         // For doctest framework


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE("Squarer: 7")
{
    Squarer sq;
    int arg = 7;
    int result = 499;  // WRONG!!!
    INFO(arg << " squared is " << result);
    REQUIRE(sq(arg) == result);
}

