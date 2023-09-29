// hsscount_test.cpp
// Glenn G. Chappell
// 2023-09-29
//
// For CS 311 Fall 2023
// Test program for function hssCount
// For Assignment 4, Exercise A
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, hsscount.h, hsscount.cpp

// Includes for code to be tested
#include "hsscount.hpp"      // For hssCount
#include "hsscount.hpp"      // Double-inclusion check, for testing only

// Includes for the "doctest" unit-testing framework
#define DOCTEST_CONFIG_IMPLEMENT
                             // We write our own main
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
                             // Reduce compile time
#include "doctest.h"         // For doctest

// Includes for all test programs
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;

// Additional includes for this test program
// (None)

// Printable name for this test suite
const std::string test_suite_name =
    "function hssCount"
    " - CS 311 Assn 4, Ex A";

// *********************************************************************
// Helper Functions/Classes for This Test Program
// *********************************************************************


// class TypeCheck
// This class exists in order to have static member function "check",
// which takes a parameter of a given type, by reference. Objects of
// type TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//      returns true if the type of x is (MyType) or (const MyType),
//      otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // No default ctor
    TypeCheck() = delete;

    // Uncopyable. Do not define copy/move ctor/assn.
    TypeCheck(const TypeCheck &) = delete;
    TypeCheck(TypeCheck &&) = delete;
    TypeCheck<T> & operator=(const TypeCheck &) = delete;
    TypeCheck<T> & operator=(TypeCheck &&) = delete;

    // Compiler-generated dctor is used (but irrelevant).
    ~TypeCheck() = default;

public:

    // check
    // The function and function template below simulate a single
    // function that takes a single parameter, and returns true iff the
    // parameter has type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check([[maybe_unused]] const T & param)
    {
        return true;
    }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check([[maybe_unused]] const OtherType & param)
    {
        return false;
    }

};  // End class TypeCheck


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Return type" )
{
    INFO( "hssCount returns int by value" );
    [[maybe_unused]] int && rr(hssCount(2,2, 0,0, 0,1, 1,0));
        // by-value check
    REQUIRE( TypeCheck<int>::check(hssCount(2,2, 0,0, 0,1, 1,0)) );
}


TEST_CASE( "n x 1 and 1 x n boards" )
{
    SUBCASE( "All 3 x 1 boards" )
    {
        REQUIRE( hssCount(3,1, 0,0, 1,0, 2,0) == 1 );
        REQUIRE( hssCount(3,1, 0,0, 2,0, 1,0) == 1 );
        REQUIRE( hssCount(3,1, 1,0, 0,0, 2,0) == 0 );
        REQUIRE( hssCount(3,1, 1,0, 2,0, 0,0) == 0 );
        REQUIRE( hssCount(3,1, 2,0, 0,0, 1,0) == 1 );
        REQUIRE( hssCount(3,1, 2,0, 1,0, 0,0) == 1 );
    }

    SUBCASE( "All 1 x 3 boards" )
    {
        REQUIRE( hssCount(1,3, 0,0, 0,1, 0,2) == 1 );
        REQUIRE( hssCount(1,3, 0,0, 0,2, 0,1) == 1 );
        REQUIRE( hssCount(1,3, 0,1, 0,0, 0,2) == 0 );
        REQUIRE( hssCount(1,3, 0,1, 0,2, 0,0) == 0 );
        REQUIRE( hssCount(1,3, 0,2, 0,0, 0,1) == 1 );
        REQUIRE( hssCount(1,3, 0,2, 0,1, 0,0) == 1 );
    }

    SUBCASE( "All 4 x 1 boards" )
    {
        REQUIRE( hssCount(4,1, 0,0, 1,0, 2,0) == 0 );
        REQUIRE( hssCount(4,1, 0,0, 1,0, 3,0) == 1 );
        REQUIRE( hssCount(4,1, 0,0, 2,0, 1,0) == 0 );
        REQUIRE( hssCount(4,1, 0,0, 2,0, 3,0) == 0 );
        REQUIRE( hssCount(4,1, 0,0, 3,0, 1,0) == 1 );
        REQUIRE( hssCount(4,1, 0,0, 3,0, 2,0) == 0 );
        REQUIRE( hssCount(4,1, 1,0, 0,0, 2,0) == 0 );
        REQUIRE( hssCount(4,1, 1,0, 0,0, 3,0) == 0 );
        REQUIRE( hssCount(4,1, 1,0, 2,0, 0,0) == 0 );
        REQUIRE( hssCount(4,1, 1,0, 2,0, 3,0) == 0 );
        REQUIRE( hssCount(4,1, 1,0, 3,0, 0,0) == 0 );
        REQUIRE( hssCount(4,1, 1,0, 3,0, 2,0) == 0 );
        REQUIRE( hssCount(4,1, 2,0, 0,0, 1,0) == 0 );
        REQUIRE( hssCount(4,1, 2,0, 0,0, 3,0) == 0 );
        REQUIRE( hssCount(4,1, 2,0, 1,0, 0,0) == 0 );
        REQUIRE( hssCount(4,1, 2,0, 1,0, 3,0) == 0 );
        REQUIRE( hssCount(4,1, 2,0, 3,0, 0,0) == 0 );
        REQUIRE( hssCount(4,1, 2,0, 3,0, 1,0) == 0 );
        REQUIRE( hssCount(4,1, 3,0, 0,0, 1,0) == 0 );
        REQUIRE( hssCount(4,1, 3,0, 0,0, 2,0) == 1 );
        REQUIRE( hssCount(4,1, 3,0, 1,0, 0,0) == 0 );
        REQUIRE( hssCount(4,1, 3,0, 1,0, 2,0) == 0 );
        REQUIRE( hssCount(4,1, 3,0, 2,0, 0,0) == 1 );
        REQUIRE( hssCount(4,1, 3,0, 2,0, 1,0) == 0 );
    }

    SUBCASE( "All 1 x 4 boards" )
    {
        REQUIRE( hssCount(1,4, 0,0, 0,1, 0,2) == 0 );
        REQUIRE( hssCount(1,4, 0,0, 0,1, 0,3) == 1 );
        REQUIRE( hssCount(1,4, 0,0, 0,2, 0,1) == 0 );
        REQUIRE( hssCount(1,4, 0,0, 0,2, 0,3) == 0 );
        REQUIRE( hssCount(1,4, 0,0, 0,3, 0,1) == 1 );
        REQUIRE( hssCount(1,4, 0,0, 0,3, 0,2) == 0 );
        REQUIRE( hssCount(1,4, 0,1, 0,0, 0,2) == 0 );
        REQUIRE( hssCount(1,4, 0,1, 0,0, 0,3) == 0 );
        REQUIRE( hssCount(1,4, 0,1, 0,2, 0,0) == 0 );
        REQUIRE( hssCount(1,4, 0,1, 0,2, 0,3) == 0 );
        REQUIRE( hssCount(1,4, 0,1, 0,3, 0,0) == 0 );
        REQUIRE( hssCount(1,4, 0,1, 0,3, 0,2) == 0 );
        REQUIRE( hssCount(1,4, 0,2, 0,0, 0,1) == 0 );
        REQUIRE( hssCount(1,4, 0,2, 0,0, 0,3) == 0 );
        REQUIRE( hssCount(1,4, 0,2, 0,1, 0,0) == 0 );
        REQUIRE( hssCount(1,4, 0,2, 0,1, 0,3) == 0 );
        REQUIRE( hssCount(1,4, 0,2, 0,3, 0,0) == 0 );
        REQUIRE( hssCount(1,4, 0,2, 0,3, 0,1) == 0 );
        REQUIRE( hssCount(1,4, 0,3, 0,0, 0,1) == 0 );
        REQUIRE( hssCount(1,4, 0,3, 0,0, 0,2) == 1 );
        REQUIRE( hssCount(1,4, 0,3, 0,1, 0,0) == 0 );
        REQUIRE( hssCount(1,4, 0,3, 0,1, 0,2) == 0 );
        REQUIRE( hssCount(1,4, 0,3, 0,2, 0,0) == 1 );
        REQUIRE( hssCount(1,4, 0,3, 0,2, 0,1) == 0 );
    }

    SUBCASE( "Various n x 1 boards with n > 4" )
    {
        REQUIRE( hssCount(  5,1,   0,0,   1,0,   4,0) == 1 );
        REQUIRE( hssCount(  5,1,   2,0,   0,0,   4,0) == 0 );
        REQUIRE( hssCount(  7,1,   2,0,   0,0,   4,0) == 0 );
        REQUIRE( hssCount(  8,1,   7,0,   6,0,   0,0) == 1 );
        REQUIRE( hssCount( 20,1,   0,0,  19,0,   1,0) == 1 );
        REQUIRE( hssCount( 25,1,  24,0,   0,0,  22,0) == 0 );
        REQUIRE( hssCount(299,1, 298,0,   0,0, 297,0) == 1 );
        REQUIRE( hssCount(299,1, 297,0, 298,0,   0,0) == 0 );
    }

    SUBCASE( "Various 1 x n boards with n > 4" )
    {
        REQUIRE( hssCount(1,  5, 0,  4, 0,  3, 0,0) == 1 );
        REQUIRE( hssCount(1,  5, 0,  0, 0,  1, 0,4) == 1 );
        REQUIRE( hssCount(1,  6, 0,  1, 0,  5, 0,0) == 0 );
        REQUIRE( hssCount(1,  6, 0,  5, 0,  0, 0,4) == 1 );
        REQUIRE( hssCount(1, 33, 0, 15, 0,  0, 0,1) == 0 );
        REQUIRE( hssCount(1, 50, 0,  0, 0, 49, 0,1) == 1 );
        REQUIRE( hssCount(1,298, 0,296, 0,297, 0,0) == 0 );
        REQUIRE( hssCount(1,299, 0,  0, 0,298, 0,1) == 1 );
    }
}


TEST_CASE( "Small boards" )
{
    SUBCASE( "Various small boards" )
    {
        REQUIRE( hssCount(2,2, 0,0, 1,0, 1,1) ==   1 );
        REQUIRE( hssCount(2,2, 1,0, 1,1, 0,0) ==   1 );
        REQUIRE( hssCount(5,2, 1,0, 1,1, 0,0) ==   0 );
        REQUIRE( hssCount(5,2, 1,0, 0,0, 4,0) ==  12 );
        REQUIRE( hssCount(2,6, 0,1, 1,1, 0,0) ==   0 );
        REQUIRE( hssCount(2,6, 0,1, 0,0, 1,4) ==  16 );
        REQUIRE( hssCount(3,3, 2,0, 1,0, 0,2) ==  12 );
        REQUIRE( hssCount(3,5, 0,0, 1,1, 2,4) == 355 );
    }
}


TEST_CASE( "Larger boards" )
{
    SUBCASE( "Various larger boards" )
    {
        REQUIRE( hssCount(4,4, 0,2, 2,1, 3,3) ==   181 );
        REQUIRE( hssCount(8,2, 1,0, 1,1, 0,0) ==     0 );
        REQUIRE( hssCount(8,2, 1,0, 0,0, 5,0) ==    96 );
        REQUIRE( hssCount(2,8, 0,1, 1,1, 0,0) ==     0 );
        REQUIRE( hssCount(2,8, 0,1, 0,0, 1,4) ==    64 );
        REQUIRE( hssCount(7,3, 0,0, 0,1, 5,0) == 11649 );
        REQUIRE( hssCount(7,3, 4,2, 6,2, 1,0) ==  9268 );
    }
}


TEST_CASE( "Slide Examples" )
{
    SUBCASE( "Examples from \"Thoughts on Assignment 4\" slides" )
    {
        REQUIRE( hssCount(4,2, 1,0, 0,0, 3,1) ==     4 );
        REQUIRE( hssCount(3,2, 2,0, 1,0, 2,1) ==     2 );
        REQUIRE( hssCount(4,1, 1,0, 0,0, 3,0) ==     0 );
        REQUIRE( hssCount(5,4, 4,3, 4,2, 0,0) == 40887 );
    }
}


// *********************************************************************
// Main Program
// *********************************************************************


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Run all tests. Prompt for ENTER before exiting.
int main(int argc,
         char *argv[])
{
    doctest::Context dtcontext;
                             // Primary doctest object
    int dtresult;            // doctest return code; for return by main

    // Handle command line
    dtcontext.applyCommandLine(argc, argv);
    dtresult = 0;            // doctest flags no command-line errors
                             //  (strange but true)

    if (!dtresult)           // Continue only if no command-line error
    {
        // Run test suites
        cout << "BEGIN tests for " << test_suite_name << "\n" << endl;
        dtresult = dtcontext.run();
        cout << "END tests for " << test_suite_name << "\n" << endl;
    }

    // If we want to do something else here, then we need to check
    // dtcontext.shouldExit() first.

    // Wait for user
    std::cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from doctest
    return dtresult;
}

