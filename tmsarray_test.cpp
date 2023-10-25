// tmsarray_test.cpp
// Glenn G. Chappell
// 2023-10-25
//
// For CS 311 Fall 2023
// Test program for class template TESArray
// For Assignment 5, Exercise A
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, tmsarray.hpp

// Includes for code to be tested
#include "tmsarray.hpp"      // For class template TMSArray
#include "tmsarray.hpp"      // Double-inclusion check, for testing only

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
#include <cstddef>
using std::size_t;
#include <string>
using std::string;
#include <utility>
using std::move;
#include <vector>
using std::vector;
#include <algorithm>
using std::copy;
using std::equal;
#include <stdexcept>
using std::runtime_error;
#include <cassert>
// For assert

// Printable name for this test suite
const string test_suite_name =
    "class template TMSArray"
    " - CS 311 Assn 5, Ex A";


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


// class Counter
// Item type for counting ctor, dctor, op= calls, counting existing
//  objects, and possibly throwing on copy. Has operator< (which always
//  returns false), allowing it to be the value type of a sorted container.
// If static member _copyThrow is set, then copy ctor and copy assn throw
//  std::runtime_error. Exception object's "what" member is set to "C" by
//  the copy ctor and "A" by copy assn.
// Increments static data member _ctorCount on default construction and
//  successful copy construction. Increments static data member _assnCount
//  on successful copy assignment. Increments static data member
//  _dctorCount on destruction.
// Increments static data member _existing on construction, and decrements
//  it on destruction.
// Static data member _maxExisting is highest value of _existing since last
//  reset, or start of program if reset has never been called.
// Invariants:
//     Counter::_existing is number of existing objects of this class.
//     Counter::_ctorCount is number of successful ctor calls since
//      most recent call to reset, or start of program if reset has never
//      been called.
//     Counter::_dctorCount is (similarly) number of dctor calls.
//     Counter::_assnCount is (similarly) number of copy assn calls.
//     Counter::_maxExisting is (similarly) highest value _existing has
//      assumed.
class Counter {

// ***** Counter: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     (_ctorCount has been incremented.)
    //     (_existing has been incremented.)
    // Does not throw (No-Throw Guarantee)
    Counter()
    {
        ++_existing;
        if (_existing > _maxExisting)
            _maxExisting = _existing;
        ++_ctorCount;
    }

    // Dctor
    // Pre: None.
    // Post:
    //     (_dctorCount has been incremented.)
    //     (_existing has been decremented.)
    // Does not throw (No-Throw Guarantee)
    ~Counter()
    {
        --_existing;
        ++_dctorCount;
    }

    // Copy ctor
    // Throws std::runtime_error if _copyThrow.
    // Pre: None.
    // Post:
    //     (_ctorCount has been incremented.)
    //     (_existing has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter(const Counter & other)
    {
        (void)other;  // Avoid unused-parameter warnings
        if (_copyThrow)
            throw runtime_error("C");
        ++_existing;
        if (_existing > _maxExisting)
            _maxExisting = _existing;
        ++_ctorCount;
    }

    // Copy assignment
    // Throws std::runtime_error if _copyThrow.
    // Pre: None.
    // Post:
    //     Return value is *this.
    //     (_assnCount has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter & operator=([[maybe_unused]] const Counter & rhs)
    {
        if (_copyThrow)
            throw runtime_error("A");
        ++_assnCount;
        return *this;
    }

    // No move operations
    Counter(Counter && other) = delete;
    Counter & operator=(Counter && other) = delete;

// ***** Counter: Functions dealing with count *****
public:

    // reset
    // Pre: None.
    // Post:
    //     _maxExisting == _existing.
    //     _ctorCount == 0.
    //     _dctorCount == 0.
    //     _assnCount == 0.
    //     _copyThrow == shouldThrow.
    // Does not throw (No-Throw Guarantee)
    static void reset(bool shouldThrow = false)
    {
        _maxExisting = _existing;
        _ctorCount = 0;
        _dctorCount = 0;
        _assnCount = 0;
        _copyThrow = shouldThrow;
    }

    // getExisting
    // Pre: None.
    // Post:
    //     return == _existing.
    // Does not throw (No-Throw Guarantee)
    static size_t getExisting()
    { return _existing; }

    // getMaxExisting
    // Pre: None.
    // Post:
    //     return == _maxExisting.
    // Does not throw (No-Throw Guarantee)
    static size_t getMaxExisting()
    { return _maxExisting; }

    // getCtorCount
    // Pre: None.
    // Post:
    //     return == _ctorCount.
    // Does not throw (No-Throw Guarantee)
    static size_t getCtorCount()
    { return _ctorCount; }

    // getDctorCount
    // Pre: None.
    // Post:
    //     return == _dctorCount.
    // Does not throw (No-Throw Guarantee)
    static size_t getDctorCount()
    { return _dctorCount; }

    // getAssnCount
    // Pre: None.
    // Post:
    //     return == _assnCount.
    // Does not throw (No-Throw Guarantee)
    static size_t getAssnCount()
    { return _assnCount; }

    // setCopyThrow
    // Pre: None.
    // Post:
    //     _copyThrow == shouldThrow
    // Does not throw (No-Throw Guarantee)
    static void setCopyThrow(bool shouldThrow)
    { _copyThrow = shouldThrow; }

// ***** Counter: Data Members *****
private:

    static size_t _existing;     // # of existing objects
    static size_t _maxExisting;  // Max # of existing objects
    static size_t _ctorCount;    // # of successful (non-throwing) ctor calls
    static size_t _dctorCount;   // # of dctor calls
    static size_t _assnCount;    // # of successful (non-throwing) copy = calls
    static bool _copyThrow;      // true if copy operations (ctor, =) throw

};  // End class Counter

// Definition of static data member of class Counter
size_t Counter::_existing = size_t(0);
size_t Counter::_maxExisting = size_t(0);
size_t Counter::_ctorCount = size_t(0);
size_t Counter::_dctorCount = size_t(0);
size_t Counter::_assnCount = size_t(0);
bool Counter::_copyThrow = false;


// operator< (Counter)
// Dummy-ish operator<, forming a strict weak order for Counter class
// Returns false (which is legal for a strict weak order; all objects of
//  type Counter are equivalent).
// Pre: None.
// Post:
//     Return value == false.
// Does not throw (No-Throw Guarantee)
bool operator<([[maybe_unused]] const Counter & a,
               [[maybe_unused]] const Counter & b)
{
    return false;
}


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "TMSArray member types" )
{
    SUBCASE( "Member type value_type" )
    {
        {
        TMSArray<int>::value_type x1;
        [[maybe_unused]] int & r(x1);
        INFO( "TMSArray<int>::value_type must be int" );
        REQUIRE( TypeCheck<int>::check(x1) );
        }

        {
        TMSArray<string>::value_type x2;
        [[maybe_unused]] string & r(x2);
        INFO( "TMSArray<string>::value_type must be string" );
        REQUIRE( TypeCheck<string>::check(x2) );
        }
    }

    SUBCASE( "Member type size_type" )
    {
        {
        TMSArray<int>::size_type x1;
        [[maybe_unused]] size_t & r(x1);
        INFO( "TMSArray<int>::size_type must be size_t" );
        REQUIRE( TypeCheck<size_t>::check(x1) );
        }

        {
        TMSArray<string>::size_type x2;
        [[maybe_unused]] size_t & r(x2);
        INFO( "TMSArray<string>::size_type must be size_t" );
        REQUIRE( TypeCheck<size_t>::check(x2) );
        }
    }

    SUBCASE( "Member type iterator" )
    {
        {
        TMSArray<int>::iterator x1;
        [[maybe_unused]] int * & r(x1);
        INFO( "TMSArray<int>::iterator must be (int *)" );
        REQUIRE( TypeCheck<int *>::check(x1) );
        }

        {
        TMSArray<string>::iterator x2;
        [[maybe_unused]] string * & r(x2);
        INFO( "TMSArray<string>::iterator must be (string *)" );
        REQUIRE( TypeCheck<string *>::check(x2) );
        }
    }

    SUBCASE( "Member type const_iterator" )
    {
        {
        TMSArray<int>::const_iterator x1;
        [[maybe_unused]] const int * & r(x1);
        INFO( "TMSArray<int>::const_iterator must be (const int *)" );
        REQUIRE( TypeCheck<const int *>::check(x1) );
        }

        {
        TMSArray<string>::const_iterator x2;
        [[maybe_unused]] const string * & r(x2);
        INFO( "TMSArray<string>::const_iterator must be (const int *)" );
        REQUIRE( TypeCheck<const string *>::check(x2) );
        }
    }
}


TEST_CASE( "TMSArray function return types" )
{
    SUBCASE( "Member function copy= - return type" )
    {
        {
        const TMSArray<int> cti;
        TMSArray<int> ti;
        [[maybe_unused]] TMSArray<int> & r(ti = cti);
        INFO( "TMSArray<int> copy= returns TMSArray<int> by ref" );
        REQUIRE( TypeCheck<TMSArray<int>>::check(ti = cti) );
        }

        {
        const TMSArray<string> cts;
        TMSArray<string> ts;
        [[maybe_unused]] TMSArray<string> & r(ts = cts);
        INFO( "TMSArray<string> copy= returns TMSArray<string> by ref" );
        REQUIRE( TypeCheck<TMSArray<string>>::check(ts = cts) );
        }
    }

    SUBCASE( "Member function move= - return type" )
    {
        {
        TMSArray<int> ti1;
        TMSArray<int> ti2;
        TMSArray<int> ti3;
        [[maybe_unused]] TMSArray<int> & r(ti1 = std::move(ti2));
        INFO( "TMSArray<int> move= returns TMSArray<int> by ref" );
        REQUIRE( TypeCheck<TMSArray<int>>::check(ti2 = std::move(ti3)) );
        }

        {
        TMSArray<string> ts1;
        TMSArray<string> ts2;
        TMSArray<string> ts3;
        [[maybe_unused]] TMSArray<string> & r(ts1 = std::move(ts2));
        INFO( "TMSArray<string> move= returns TMSArray<string> by ref" );
        REQUIRE( TypeCheck<TMSArray<string>>::check(ts2 = std::move(ts3)) );
        }
    }

    SUBCASE( "Member function size - return type" )
    {
        {
        const TMSArray<int> cti(10);
        [[maybe_unused]] size_t && r(cti.size());
        INFO( "TMSArray<int> size returns size_t by value" );
        REQUIRE( TypeCheck<size_t>::check(cti.size()) );
        }

        {
        const TMSArray<string> cts(10);
        [[maybe_unused]] size_t && r(cts.size());
        INFO( "TTMArray<string> size returns size_t by value" );
        REQUIRE( TypeCheck<size_t>::check(cts.size()) );
        }
    }

    SUBCASE( "Member function empty - return type" )
    {
        {
        const TMSArray<int> cti(10);
        [[maybe_unused]] bool && r(cti.empty());
        INFO( "TMSArray<int> empty returns bool by value" );
        REQUIRE( TypeCheck<bool>::check(cti.empty()) );
        }

        {
        const TMSArray<string> cts(10);
        [[maybe_unused]] bool && r(cts.empty());
        INFO( "TMSArray<string> empty returns bool by value" );
        REQUIRE( TypeCheck<bool>::check(cts.empty()) );
        }
    }

    SUBCASE( "Member function bracket op - return type" )
    {
        {
        TMSArray<int> ti(10);
        [[maybe_unused]] int & r(ti[0]);
        INFO( "TMSArray<int> bracket op returns int by ref" );
        REQUIRE( TypeCheck<int>::check(ti[0]) );
        }

        {
        TMSArray<string> ts(10);
        [[maybe_unused]] string & r(ts[0]);
        INFO( "TMSArray<string> bracket op returns string by ref" );
        REQUIRE( TypeCheck<string>::check(ts[0]) );
        }

        {
        const TMSArray<int> cti(10);
        [[maybe_unused]] const int & r(cti[0]);
        INFO( "const TMSArray<int> bracket op returns const int by ref" );
        REQUIRE( TypeCheck<const int>::check(cti[0]) );
        }

        {
        const TMSArray<string> cts(10);
        [[maybe_unused]] const string & r(cts[0]);
        INFO( "const TMSArray<string> bracket op returns const string by ref" );
        REQUIRE( TypeCheck<const string>::check(cts[0]) );
        }
    }

    SUBCASE( "Member function begin - return type" )
    {
        {
        TMSArray<int> ti(10);
        [[maybe_unused]] int * && r(ti.begin());
        INFO( "TMSArray<int> begin returns (int *) by value" );
        REQUIRE( TypeCheck<int *>::check(ti.begin()) );
        }

        {
        TMSArray<string> ts(10);
        [[maybe_unused]] string * && r(ts.begin());
        INFO( "TMSArray<string> begin returns (string *) by value" );
        REQUIRE( TypeCheck<string *>::check(ts.begin()) );
        }

        {
        const TMSArray<int> cti(10);
        [[maybe_unused]] const int * && r(cti.begin());
        INFO( "const TMSArray<int> begin returns (const int *) by value" );
        REQUIRE( TypeCheck<const int *>::check(cti.begin()) );
        }

        {
        const TMSArray<string> cts(10);
        [[maybe_unused]] const string * && r(cts.begin());
        INFO( "const TMSArray<string> begin returns (const string *) by value" );
        REQUIRE( TypeCheck<const string *>::check(cts.begin()) );
        }
    }

    SUBCASE( "Member function end - return type" )
    {
        {
        TMSArray<int> ti(10);
        [[maybe_unused]] int * && r(ti.end());
        INFO( "TMSArray<int> end returns (int *) by value" );
        REQUIRE( TypeCheck<int *>::check(ti.end()) );
        }

        {
        TMSArray<string> ts(10);
        [[maybe_unused]] string * && r(ts.end());
        INFO( "TMSArray<string> end returns (string *) by value" );
        REQUIRE( TypeCheck<string *>::check(ts.end()) );
        }

        {
        const TMSArray<int> cti(10);
        [[maybe_unused]] const int * && r(cti.end());
        INFO( "const TMSArray<int> end returns (const int *) by value" );
        REQUIRE( TypeCheck<const int *>::check(cti.end()) );
        }

        {
        const TMSArray<string> cts(10);
        [[maybe_unused]] const string * && r(cts.end());
        INFO( "const TMSArray<string> end returns (const string *) by value" );
        REQUIRE( TypeCheck<const string *>::check(cts.end()) );
        }
    }

    SUBCASE( "Member function insert - return type" )
    {
        {
        TMSArray<int> ti(10);
        [[maybe_unused]] int * && r(ti.insert(ti.begin(), 1));
        INFO( "TMSArray<int> insert returns (int *) by value" );
        REQUIRE( TypeCheck<int *>::check(ti.insert(ti.begin(), 1)) );
        }

        {
        TMSArray<string> ts(10);
        [[maybe_unused]] string * && r(ts.insert(ts.begin(), string()));
        INFO( "TMSArray<string> insert returns (string *) by value" );
        REQUIRE( TypeCheck<string *>::check(ts.insert(ts.begin(), string())) );
        }
    }

    SUBCASE( "Member function erase - return type" )
    {
        {
        TMSArray<int> ti(10);
        [[maybe_unused]] int * && r(ti.erase(ti.begin()));
        INFO( "TMSArray<int> erase returns (int *) by value" );
        REQUIRE( TypeCheck<int *>::check(ti.erase(ti.begin())) );
        }

        {
        TMSArray<string> ts(10);
        [[maybe_unused]] string * && r(ts.erase(ts.begin()));
        INFO( "TMSArray<string> erase returns (string *) by value" );
        REQUIRE( TypeCheck<string *>::check(ts.erase(ts.begin())) );
        }
    }
}


TEST_CASE( "TMSArray noexcept" )
{
    TMSArray<Counter> tc1;
    TMSArray<Counter> tc2;

    SUBCASE( "noexcept - move ctor" )
    {
        INFO( "Move ctor must be noexcept" );
        REQUIRE( noexcept(TMSArray<Counter>(std::move(tc1))) );
    }

    SUBCASE( "noexcept - move assignment" )
    {
        INFO( "Move assignment must be noexcept" );
        REQUIRE( noexcept(tc2 = std::move(tc1)) );
    }

    SUBCASE( "noexcept - dctor" )
    {
        INFO( "Dctor must be noexcept" );
        REQUIRE( noexcept(tc1.~TMSArray()) );
    }

    SUBCASE( "noexcept - swap" )
    {
        INFO( "Member function swap must be noexcept" );
        REQUIRE( noexcept(tc2.swap(tc1)) );
    }

    SUBCASE( "NOT noexcept - copy ctor" )
    {
        INFO( "Copy ctor must NOT be noexcept" );
        REQUIRE_FALSE( noexcept(TMSArray<Counter>(tc1)) );
    }

    SUBCASE( "NOT noexcept - ctor from size" )
    {
        INFO( "Ctor from size must NOT be noexcept" );
        REQUIRE_FALSE( noexcept(TMSArray<Counter>(100)) );
    }

    SUBCASE( "NOT noexcept - copy assignment" )
    {
        INFO( "Copy assignment must NOT be noexcept" );
        REQUIRE_FALSE( noexcept(tc2 = tc1) );
    }

    SUBCASE( "NOT noexcept - resize" )
    {
        INFO( "Member resize must NOT be noexcept" );
        REQUIRE_FALSE( noexcept(tc1.resize(100)) );
    }

    SUBCASE( "NOT noexcept - insert" )
    {
        INFO( "Member insert must NOT be noexcept" );
        REQUIRE_FALSE( noexcept(tc1.insert(tc1.begin(), Counter())) );
    }

    SUBCASE( "NOT noexcept - push_back" )
    {
        INFO( "Member push_back must NOT be noexcept" );
        REQUIRE_FALSE( noexcept(tc1.push_back(Counter())) );
    }
}


TEST_CASE( "TMSArray default ctor, size, empty" )
{
    SUBCASE( "Default ctor" )
    {
        const TMSArray<int> cti;
        {
        INFO( "Default constructed TMSArray has size 0" );
        REQUIRE( cti.size() == size_t(0) );
        }
        {
        INFO( "Default constructed TMSArray is empty" );
        REQUIRE( cti.empty() );
        }
        {
        INFO( "Default constructed TMSArray: begin == end" );
        REQUIRE( cti.begin() == cti.end() );
        }
    }
}


TEST_CASE( "TMSArray ctor from size, size, empty, begin, end" )
{
    SUBCASE( "Ctor from size - size 0" )
    {
        const size_t SIZE = size_t(0);
        const TMSArray<int> cti(SIZE);
        {
        INFO( "TMSArray constructed with size " << SIZE << ": size" );
        REQUIRE( cti.size() == SIZE );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << " is empty" );
        REQUIRE( cti.empty() );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << ": begin == end" );
        REQUIRE( cti.begin() == cti.end() );
        }
    }

    SUBCASE( "Ctor from size - small size" )
    {
        const size_t SIZE = size_t(1);
        const TMSArray<int> cti(SIZE);
        {
        INFO( "TMSArray constructed with size " << SIZE << ": size" );
        REQUIRE( cti.size() == SIZE );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << " is not empty" );
        REQUIRE_FALSE( cti.empty() );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << ": begin" );
        REQUIRE( cti.begin() == &cti[0] );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << ": end" );
        REQUIRE( cti.end() == cti.begin() + SIZE );
        }
    }

    SUBCASE( "Ctor from size - large size" )
    {
        const size_t SIZE = size_t(50000000);
        const TMSArray<int> cti(SIZE);
        {
        INFO( "TMSArray constructed with size " << SIZE << ": size" );
        REQUIRE( cti.size() == SIZE );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << " is not empty" );
        REQUIRE_FALSE( cti.empty() );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << ": begin" );
        REQUIRE( cti.begin() == &cti[0] );
        }
        {
        INFO( "TMSArray constructed with size " << SIZE << ": end" );
        REQUIRE( cti.end() == cti.begin() + SIZE );
        }
    }
}


TEST_CASE( "TMSArray bracket operator" )
{
    SUBCASE( "Bracket op" )
    {
        const size_t SIZE = size_t(10);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }

        {
        INFO( "Bracket op (non-const) - check values" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( ti[i] == 15-int(i)*int(i) );
        }
        }

        ti[2] = 1000;
        {
        INFO( "Bracket op (non-const) - check values after changing a value" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ti[i] == (i == size_t(2) ? 1000 : 15-int(i)*int(i)) );
        }
        }

        // Make const version, no copy
        const TMSArray<int> & ctiref = ti;
        {
        INFO( "Bracket op (const) - check values" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ctiref[i] == (i == size_t(2) ? 1000 : 15-int(i)*int(i)) );
        }
        }
    }
}


TEST_CASE( "TMSArray copy ctor" )
{
    SUBCASE( "Copy ctor - separate arrays" )
    {
        const size_t SIZE = size_t(10);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }

        // Make const version, no copy
        const TMSArray<int> & ctiref(ti);
        // Make copy (copy ctor)
        TMSArray<int> ticopy(ctiref);

        {
        INFO( "Copy ctor - check size of copy" );
        REQUIRE( ticopy.size() == SIZE );
        }

        {
        INFO( "Copy ctor - check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( ticopy[i] == 15-int(i)*int(i) );
        }
        }

        // Change original
        ti[2] = 1000;

        {
        INFO( "Copy ctor - change original, check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( ticopy[i] == 15-int(i)*int(i) );
        }
        }

        {
        INFO( "Copy ctor - change original, check values of original" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ti[i] == (i == size_t(2) ? 1000 : 15-int(i)*int(i)) );
        }
        }

        // Change copy
        ticopy[3] = 2000;

        {
        INFO( "Copy ctor - change copy, check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ticopy[i] == (i == size_t(3) ? 2000 : 15-int(i)*int(i)) );
        }
        }

        {
        INFO( "Copy ctor - change copy, check values of original" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ti[i] == (i == size_t(2) ? 1000 : 15-int(i)*int(i)) );
        }
        }
    }

    SUBCASE( "Copy ctor - destroy original" )
    {
        const size_t SIZE = size_t(10);
        TMSArray<int> * tip = new TMSArray<int>(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            (*tip)[i] = 15-int(i)*int(i);
        }

        // Make copy (copy ctor)
        TMSArray<int> ticopy(*tip);
        // Destroy original
        delete tip;

        {
        INFO( "Copy ctor - check size of copy" );
        REQUIRE( ticopy.size() == SIZE );
        }

        {
        INFO( "Copy ctor - check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( ticopy[i] == 15-int(i)*int(i) );
        }
        }
    }
}


TEST_CASE( "TMSArray copy assignment operator" )
{
    SUBCASE( "Copy= - separate arrays" )
    {
        const size_t SIZE = size_t(10);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }

        // Make const version, no copy
        const TMSArray<int> & ctiref(ti);
        // Make copy (copy assn)
        TMSArray<int> ticopy;
        ticopy = ctiref;

        {
        INFO( "Copy= - check size of copy" );
        REQUIRE( ticopy.size() == SIZE );
        }

        {
        INFO( "Copy= - check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( ticopy[i] == 15-int(i)*int(i) );
        }
        }

        // Change original
        ti[2] = 1000;

        {
        INFO( "Copy= - change original, check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( ticopy[i] == 15-int(i)*int(i) );
        }
        }

        {
        INFO( "Copy= - change original, check values of original" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ti[i] == (i == size_t(2) ? 1000 : 15-int(i)*int(i)) );
        }
        }

        // Change copy
        ticopy[3] = 2000;

        {
        INFO( "Copy= - change copy, check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ticopy[i] == (i == size_t(3) ? 2000 : 15-int(i)*int(i)) );
        }
        }

        {
        INFO( "Copy= - change copy, check values of original" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ti[i] == (i == size_t(2) ? 1000 : 15-int(i)*int(i)) );
        }
        }
    }

    SUBCASE( "Copy= - destroy original" )
    {
        const size_t SIZE = size_t(10);
        TMSArray<int> * tip = new TMSArray<int>(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            (*tip)[i] = 15-int(i)*int(i);
        }

        // Make copy (copy assn)
        TMSArray<int> ticopy;
        ticopy = *tip;
        // Destroy original
        delete tip;

        {
        INFO( "Copy ctor - check size of copy" );
        REQUIRE( ticopy.size() == SIZE );
        }

        {
        INFO( "Copy ctor - check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( ticopy[i] == 15-int(i)*int(i) );
        }
        }
    }
}


TEST_CASE( "TMSArray move ctor" )
{
    SUBCASE( "Move ctor - destroy original" )
    {
        const size_t SIZE = size_t(10);
        TMSArray<int> * tip = new TMSArray<int>(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            (*tip)[i] = 15-int(i)*int(i);
        }

        // Make copy (move ctor)
        size_t sizeold = tip->size();
        int * dataold = tip->begin();
        TMSArray<int> timove(std::move(*tip));

        {
        INFO( "Move= - check size of original" );
        REQUIRE( tip->size() == size_t(0) );
        }
        {
        INFO( "Move= - check address of original array" );
        REQUIRE( tip->begin() == nullptr );
        }

        {
        INFO( "Move= - check size of copy" );
        REQUIRE( timove.size() == sizeold );
        }
        {
        INFO( "Move= - check address of copy array" );
        REQUIRE( timove.begin() == dataold );
        }

        // Destroy original
        delete tip;

        {
        INFO( "Move ctor - check size of copy (again)" );
        REQUIRE( timove.size() == SIZE );
        }

        {
        INFO( "Move ctor - check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( timove[i] == 15-int(i)*int(i) );
        }
        }
    }
}


TEST_CASE( "TMSArray move assignment operator" )
{
    SUBCASE( "Move= - destroy original" )
    {
        const size_t SIZE = size_t(10);
        TMSArray<int> * tip = new TMSArray<int>(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            (*tip)[i] = 15-int(i)*int(i);
        }

        // Make copy (move assn)
        size_t sizeold = tip->size();
        int * dataold = tip->begin();
        TMSArray<int> timove;
        size_t sizenew = timove.size();
        int * datanew = timove.begin();
        timove = std::move(*tip);

        {
        INFO( "Move= - check size of original" );
        REQUIRE( tip->size() == sizenew );
        }
        {
        INFO( "Move= - check address of original array" );
        REQUIRE( tip->begin() == datanew );
        }

        {
        INFO( "Move= - check size of copy" );
        REQUIRE( timove.size() == sizeold );
        }
        {
        INFO( "Move= - check address of copy array" );
        REQUIRE( timove.begin() == dataold );
        }

        // Destroy original
        delete tip;

        {
        INFO( "Move= - check size of copy (again)" );
        REQUIRE( timove.size() == SIZE );
        }

        {
        INFO( "Move= - check values of copy" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE ( timove[i] == 15-int(i)*int(i) );
        }
        }
    }
}


TEST_CASE( "TMSArray resize" )
{
    SUBCASE( "resize smaller" )
    {
        const size_t SIZE = size_t(10);
        const size_t SIZE2 = size_t(5);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }
        int * savedata = ti.begin();

        // Resize
        ti.resize(SIZE2);

        {
        INFO( "resize - check size" );
        REQUIRE( ti.size() == SIZE2 );
        }
        {
        INFO( "resize - check address of array" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "resize - check values" );
        for (size_t i = 0; i < SIZE2; ++i)
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "resize same size" )
    {
        const size_t SIZE = size_t(10);
        const size_t SIZE2 = size_t(10);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }
        int * savedata = ti.begin();

        // Resize
        ti.resize(SIZE2);

        {
        INFO( "resize - check size" );
        REQUIRE( ti.size() == SIZE2 );
        }
        {
        INFO( "resize - check address of array" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "resize - check values" );
        for (size_t i = 0; i < SIZE2; ++i)
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "resize a little larger" )
    {
        const size_t SIZE = size_t(10);
        const size_t SIZE2 = size_t(15);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }

        // Resize
        ti.resize(SIZE2);
        ti[SIZE2-1] = 1000;  // Do a write, just for fun

        {
        INFO( "resize - check size" );
        REQUIRE( ti.size() == SIZE2 );
        }
        {
        INFO( "resize - check values" );
        for (size_t i = 0; i < SIZE; ++i)  // SIZE, not SIZE2
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "resize a lot larger" )
    {
        const size_t SIZE = size_t(10);
        const size_t SIZE2 = size_t(50000000);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }
        int * savedata = ti.begin();

        // Resize
        ti.resize(SIZE2);
        ti[SIZE2-1] = 1000;  // Do a write, just for fun

        {
        INFO( "resize - check size" );
        REQUIRE( ti.size() == SIZE2 );
        }
        {
        INFO( "resize - check address of array" );
        REQUIRE( ti.begin() != savedata );
        }
        {
        INFO( "resize - check values" );
        for (size_t i = 0; i < SIZE; ++i)  // SIZE, not SIZE2
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "Multiple resize-one-bigger calls" )
    {
        const size_t SIZE = size_t(10);
        const size_t SIZE2 = size_t(100000);
        TMSArray<int> ti(SIZE);
        for (size_t i = 0; i < SIZE; ++i)
        {
            ti[i] = 15-int(i)*int(i);
        }

        // Do resizing
        int realloccount = 0;       // # of times realloc-&-copy done
        bool realloctwice = false;  // Did realloc-&-copy 2x in a row?
        bool realloclast = false;   // Was realloc-&-copy just done?
        for (size_t i = SIZE+1; i <= SIZE2; ++i)
        {
            int * savedata = ti.begin();
            ti.resize(i);
            if (i == size_t(1000))  // Do a write during resizes
                ti[i-size_t(1)] = 1000;
            bool reallocdone = (ti.begin() != savedata);  // realloc-&-copy?
            if (reallocdone)
            {
                ++realloccount;
                if (realloclast)
                    realloctwice = true;
            }
            realloclast = reallocdone;
        }
        {
        INFO( "Many resizes - how many reallocate-and-copy ops" );
        REQUIRE( realloccount >= 3 );
        REQUIRE( realloccount <= 50 );
        }
        {
        INFO( "Many resizes - never reallocate-and-copy 2x in a row" );
        REQUIRE_FALSE( realloctwice );
        }
        {
        INFO( "Many resizes - check size" );
        REQUIRE( ti.size() == SIZE2 );
        }
        {
        INFO( "Many resizes - check values" );
        for (size_t i = 0; i < SIZE; ++i)  // SIZE, not SIZE2
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        REQUIRE( ti[999] == 1000 );
        }
        {
        INFO( "Many resizes - check begin, end" );
        REQUIRE( ti.begin() == &ti[0] );
        REQUIRE( ti.end() == ti.begin() + SIZE2 );
        }
    }
}


TEST_CASE( "TMSArray insert" )
{
    const size_t SIZE = size_t(10);
    TMSArray<int> ti_original(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
    {
        ti_original[i] = 15-int(i)*int(i);
    }

    SUBCASE( "insert at end" )
    {
        TMSArray<int> ti = ti_original;
        ti.insert(ti.end(), 1000);

        {
        INFO( "insert - check size" );
        REQUIRE( ti.size() == SIZE+1 );
        }
        {
        INFO( "insert - check values" );
        for (size_t i = 0; i < SIZE+1; ++i)
        {
            if (i == SIZE)
                REQUIRE( ti[i] == 1000 );
            else
                REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "insert at beginning" )
    {
        TMSArray<int> ti = ti_original;
        ti.insert(ti.begin(), 1000);

        {
        INFO( "insert - check size" );
        REQUIRE( ti.size() == SIZE+1 );
        }
        {
        INFO( "insert - check values" );
        for (size_t i = 0; i < SIZE+1; ++i)
        {
            if (i == 0)
                REQUIRE( ti[i] == 1000 );
            else
                REQUIRE( ti[i] == 15-(int(i)-1)*(int(i)-1) );
        }
        }
    }

    SUBCASE( "insert in middle" )
    {
        TMSArray<int> ti = ti_original;
        auto result = ti.insert(ti.begin()+5, 1000);

        {
        INFO( "insert - check size" );
        REQUIRE( ti.size() == SIZE+1 );
        }
        {
        INFO( "insert - check values" );
        for (size_t i = 0; i < SIZE+1; ++i)
        {
            if (i < 5)
                REQUIRE( ti[i] == 15-int(i)*int(i) );
            else if (i == 5)
                REQUIRE( ti[i] == 1000 );
            else
                REQUIRE( ti[i] == 15-(int(i)-1)*(int(i)-1) );
        }
        }
        {
        INFO( "insert - check return value" );
        REQUIRE( result == ti.begin()+5 );
        }
    }

    SUBCASE( "Multiple insert-at-end calls" )
    {
        const size_t SIZE2 = size_t(100000);
        TMSArray<int> ti = ti_original;

        // Create expected data
        vector<int> v(ti_original.begin(), ti_original.end());
        for (size_t i = SIZE+1; i <= SIZE2; ++i)
        {
            v.insert(v.end(), 70000-(int(i)-1));
        }
        assert (v.size() == SIZE2);

        // Do inserting
        int realloccount = 0;       // # of times realloc-&-copy done
        bool realloctwice = false;  // Did realloc-&-copy 2x in a row?
        bool realloclast = false;   // Was realloc-&-copy just done?
        for (size_t i = SIZE+1; i <= SIZE2; ++i)
        {
            int * savedata = ti.begin();
            auto result = ti.insert(ti.end(), 70000-int(ti.size()));
            bool reallocdone = (ti.begin() != savedata);  // realloc-&-copy?
            if (reallocdone)
            {
                ++realloccount;
                if (realloclast)
                    realloctwice = true;
                {
                INFO( "Many inserts - check return value on reallocate-and-copy" );
                REQUIRE( result == ti.end()-1 );
                }
            }
            realloclast = reallocdone;
        }
        {
        INFO( "Many inserts - how many reallocate-and-copy ops" );
        REQUIRE( realloccount >= 3 );
        REQUIRE( realloccount <= 50 );
        }
        {
        INFO( "Many inserts - reallocate-and-copy never done 2x in a row" );
        REQUIRE_FALSE( realloctwice );
        }
        {
        INFO( "Many inserts - check size" );
        REQUIRE( ti.size() == SIZE2 );
        }
        {
        INFO( "Many inserts - check values" );
        REQUIRE( equal(v.begin(), v.end(), ti.begin()) );
        }
        {
        INFO( "Many inserts - check begin, end" );
        REQUIRE( ti.begin() == &ti[0] );
        REQUIRE( ti.end() == ti.begin() + SIZE2 );
        }
    }
}


TEST_CASE( "TMSArray erase" )
{
    const size_t SIZE = size_t(10);
    TMSArray<int> ti_original(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
    {
        ti_original[i] = 15-int(i)*int(i);
    }

    SUBCASE( "erase at end" )
    {
        TMSArray<int> ti = ti_original;
        int * savedata = ti.begin();
        ti.erase(ti.end()-1);

        {
        INFO( "erase - no reallocate-and-copy" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "erase - check size" );
        REQUIRE( ti.size() == SIZE-1 );
        }
        {
        INFO( "erase - check values" );
        for (size_t i = 0; i < SIZE-1; ++i)
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "erase at beginning" )
    {
        TMSArray<int> ti = ti_original;
        int * savedata = ti.begin();
        ti.erase(ti.begin());

        {
        INFO( "erase - no reallocate-and-copy" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "erase - check size" );
        REQUIRE( ti.size() == SIZE-1 );
        }
        {
        INFO( "erase - check values" );
        for (size_t i = 0; i < SIZE-1; ++i)
        {
            REQUIRE( ti[i] == 15-(int(i)+1)*(int(i)+1) );
        }
        }
    }

    SUBCASE( "erase in middle" )
    {
        TMSArray<int> ti = ti_original;
        int * savedata = ti.begin();
        auto result = ti.erase(ti.begin()+5);

        {
        INFO( "erase - no reallocate-and-copy" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "erase - check size" );
        REQUIRE( ti.size() == SIZE-1 );
        }
        {
        INFO( "erase - check values" );
        for (size_t i = 0; i < SIZE-1; ++i)
        {
            if (i < 5)
                REQUIRE( ti[i] == 15-int(i)*int(i) );
            else
                REQUIRE( ti[i] == 15-(int(i)+1)*(int(i)+1) );
        }
        }
        {
        INFO( "erase - check return value" );
        REQUIRE( result == ti.begin()+5 );
        }
    }

    SUBCASE( "Multiple erase-at-end calls" )
    {
        const size_t SIZE2 = size_t(100000);
        TMSArray<int> ti(SIZE2);
        copy(ti_original.begin(), ti_original.end(), ti.begin());

        // Do removing
        int * savedata = ti.begin();
        for (size_t i = SIZE2; i > SIZE; --i)
        {
            ti.erase(ti.end()-1);
        }

        {
        INFO( "Many erases - no reallocate-and-copy" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "Many erases - check size" );
        REQUIRE( ti.size() == SIZE );
        }
        {
        INFO( "Many erases - check values" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
        {
        INFO( "Many erases - check begin, end" );
        REQUIRE( ti.begin() == &ti[0] );
        REQUIRE( ti.end() == ti.begin() + SIZE );
        }
    }
}


TEST_CASE( "TMSArray insert & erase" )
{
    SUBCASE( "Several insert & erase calls" )
    {
        vector<int> v { 1, 3, 4, 2, 6, 8, 7, 4, 5 };
        TMSArray<int> ti(v.size());
        copy(v.begin(), v.end(), ti.begin());

        // Data: 1 3 4 2 6 8 7 4 5
        ti.erase(ti.begin());
        // Data: 3 4 2 6 8 7 4 5
        ti.erase(ti.begin()+7);
        // Data: 3 4 2 6 8 7 4
        ti.insert(ti.begin()+2, 11);
        // Data: 3 4 11 2 6 8 7 4
        ti.erase(ti.begin()+6);
        // Data: 3 4 11 2 6 8 4
        ti.insert(ti.begin(), 12);
        // Data: 12 3 4 11 2 6 8 4
        ti.insert(ti.begin()+8, 13);
        // Data: 12 3 4 11 2 6 8 4 13
        ti.erase(ti.begin()+6);
        // Data: 12 3 4 11 2 6 4 13
        ti.erase(ti.begin()+2);
        // Data: 12 3 11 2 6 4 13
        ti.erase(ti.begin()+5);
        // Data: 12 3 11 2 6 13
        ti.insert(ti.begin()+4, 14);
        // Data: 12 3 11 2 14 6 13
        ti.erase(ti.begin()+2);
        // Data: 12 3 2 14 6 13
        ti.insert(ti.begin(), 15);
        // Data: 15 12 3 2 14 6 13

        vector<int> v2 { 15, 12, 3, 2, 14, 6, 13 };

        {
        INFO( "insert + erase - check size" );
        REQUIRE( ti.size() == v2.size() );
        }
        {
        INFO( "insert + erase - check values" );
        for (size_t i = 0; i < v2.size(); ++i)
        {
            REQUIRE( ti[i] == v2[i] );
        }
        }
    }
}


TEST_CASE( "TMSArray push_back" )
{
    const size_t SIZE = size_t(10);
    TMSArray<int> ti_original(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
    {
        ti_original[i] = 15-int(i)*int(i);
    }

    SUBCASE( "Single push_back" )
    {
        TMSArray<int> ti = ti_original;
        ti.push_back(1000);

        {
        INFO( "push_back - check size" );
        REQUIRE( ti.size() == SIZE+1 );
        }
        {
        INFO( "push_back - check values" );
        for (size_t i = 0; i < SIZE+1; ++i)
        {
            if (i == SIZE)
                REQUIRE( ti[i] == 1000 );
            else
                REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "Multiple push_back calls" )
    {
        const size_t SIZE2 = size_t(100000);
        TMSArray<int> ti = ti_original;

        // Create expected data
        vector<int> v(ti_original.begin(), ti_original.end());
        for (size_t i = SIZE+1; i <= SIZE2; ++i)
        {
            v.push_back(70000-(int(i)-1));
        }
        assert (v.size() == SIZE2);

        // Do push_back calls
        int realloccount = 0;       // # of times realloc-&-copy done
        bool realloctwice = false;  // Did realloc-&-copy 2x in a row?
        bool realloclast = false;   // Was realloc-&-copy just done?
        for (size_t i = SIZE+1; i <= SIZE2; ++i)
        {
            int * savedata = ti.begin();
            ti.push_back(70000-int(ti.size()));
            bool reallocdone = (ti.begin() != savedata);  // realloc-&-copy?
            if (reallocdone)
            {
                ++realloccount;
                if (realloclast)
                    realloctwice = true;
            }
            realloclast = reallocdone;
        }
        {
        INFO( "Many push_back calls - how many reallocate-and-copy ops" );
        REQUIRE( realloccount >= 3 );
        REQUIRE( realloccount <= 50 );
        }
        {
        INFO( "Many push_back calls - never reallocate-and-copy 2x in a row" );
        REQUIRE_FALSE( realloctwice );
        }
        {
        INFO( "Many push_back calls - check size" );
        REQUIRE( ti.size() == SIZE2 );
        }
        {
        INFO( "Many push_back calls - check values" );
        REQUIRE( equal(v.begin(), v.end(), ti.begin()) );
        }
        {
        INFO( "Many push_back calls - check begin, end" );
        REQUIRE( ti.begin() == &ti[0] );
        REQUIRE( ti.end() == ti.begin() + SIZE2 );
        }
    }
}


TEST_CASE( "TMSArray pop_back" )
{
    const size_t SIZE = size_t(10);
    TMSArray<int> ti_original(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
    {
        ti_original[i] = 15-int(i)*int(i);
    }

    SUBCASE( "Single pop_back" )
    {
        TMSArray<int> ti = ti_original;
        int * savedata = ti.begin();
        ti.pop_back();

        {
        INFO( "pop_back - no reallocate-and-copy" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "pop_back - check size" );
        REQUIRE( ti.size() == SIZE-1 );
        }
        {
        INFO( "pop_back - check values" );
        for (size_t i = 0; i < SIZE-1; ++i)
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
    }

    SUBCASE( "Multiple pop_back calls" )
    {
        const size_t SIZE2 = size_t(100000);
        TMSArray<int> ti(SIZE2);
        copy(ti_original.begin(), ti_original.end(), ti.begin());

        // Do removing
        int * savedata = ti.begin();
        for (size_t i = SIZE2; i > SIZE; --i)
        {
            ti.pop_back();
        }

        {
        INFO( "Many pop_back calls - no reallocate-and-copy" );
        REQUIRE( ti.begin() == savedata );
        }
        {
        INFO( "Many pop_back calls - check size" );
        REQUIRE( ti.size() == SIZE );
        }
        {
        INFO( "Many pop_back calls - check values" );
        for (size_t i = 0; i < SIZE; ++i)
        {
            REQUIRE( ti[i] == 15-int(i)*int(i) );
        }
        }
        {
        INFO( "Many pop_back calls - check begin, end" );
        REQUIRE( ti.begin() == &ti[0] );
        REQUIRE( ti.end() == ti.begin() + SIZE );
        }
    }
}


TEST_CASE( "TMSArray push_back & pop_back" )
{
    SUBCASE( "Many push_back & pop_back calls" )
    {
        vector<int> v { 1, 3, 4, 2, 6, 8, 7, 4, 5 };
        TMSArray<int> ti(v.size());
        copy(v.begin(), v.end(), ti.begin());
        const int BIGCOUNT = 100000;

        ti.pop_back();
        ti.pop_back();
        ti.pop_back();
        for (int i = 0; i < BIGCOUNT+2; ++i)
        {
            ti.push_back(11);
        }
        ti.push_back(-100);
        for (int i = 0; i < BIGCOUNT+1; ++i)
        {
            ti.pop_back();
        }
        for (int i = 0; i < BIGCOUNT+1; ++i)
        {
            ti.push_back(12);
        }
        for (int i = 0; i < BIGCOUNT; ++i)
        {
            ti.pop_back();
        }
        for (int i = 0; i < BIGCOUNT+2; ++i)
        {
            ti.push_back(13);
        }
        for (int i = 0; i < BIGCOUNT; ++i)
        {
            ti.pop_back();
        }

        vector<int> v2 { 1, 3, 4, 2, 6, 8, 11, 11, 12, 13, 13 };

        {
        INFO( "push_back + pop_back - check size" );
        REQUIRE( ti.size() == v2.size() );
        }
        {
        INFO( "push_back + pop_back - check values" );
        for (size_t i = 0; i < v2.size(); ++i)
        {
            REQUIRE( ti[i] == v2[i] );
        }
        }
    }
}


TEST_CASE( "TMSArray swap" )
{
    SUBCASE( "swap" )
    {
        const size_t SIZE1 = size_t(10);
        const size_t SIZE2 = size_t(1000);
        TMSArray<int> ti1(SIZE1);
        for (size_t i = 0; i < SIZE1; ++i)
        {
            ti1[i] = int(i)*int(i);
        }
        TMSArray<int> ti2(SIZE2);
        for (size_t i = 0; i < SIZE2; ++i)
        {
            ti2[i] = 100-int(i);
        }

        // Do swap
        int * savedata1 = ti1.begin();
        int * savedata2 = ti2.begin();
        ti1.swap(ti2);

        {
        INFO( "swap - check size of array #1" );
        REQUIRE( ti1.size() == SIZE2 );
        }
        {
        INFO( "swap - check address of array #1" );
        REQUIRE( ti1.begin() == savedata2 );
        }
        {
        INFO( "swap - check values of array #1" );
        for (size_t i = 0; i < SIZE2; ++i)
        {
            REQUIRE( ti1[i] == 100-int(i) );
        }
        }

        {
        INFO( "swap - check size of array #2" );
        REQUIRE( ti2.size() == SIZE1 );
        }
        {
        INFO( "swap - check address of array #2" );
        REQUIRE( ti2.begin() == savedata1 );
        }
        {
        INFO( "swap - check values of array #2" );
        for (size_t i = 0; i < SIZE1; ++i)
        {
            REQUIRE( ti2[i] == int(i)*int(i) );
        }
        }
    }
}


TEST_CASE( "TMSArray ctor/dctor count" )
{
    SUBCASE( "Ctor/dctor calls on construction by size, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        size_t objectcount;  // Ctor calls - dctor calls
        {
            const size_t SIZE = size_t(1000);
            const TMSArray<Counter> tc(SIZE);
            ctorcount = Counter::getCtorCount();
            dctorcount = Counter::getDctorCount();
            {
            INFO( "Number of ctor calls for container creation is about size" );
            REQUIRE( ctorcount >= SIZE );
            REQUIRE( ctorcount <= 2*SIZE+50 );
            }
            {
            INFO( "Number of dctor calls for container creation is small" );
            REQUIRE( dctorcount <= ctorcount );
            REQUIRE( dctorcount <= 2 );
            }

            objectcount = ctorcount - dctorcount;
            Counter::reset();
        }
        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "No value-type objects constructed on container destruction" );
        REQUIRE( ctorcount == 0 );
        }
        {
        INFO( "All value-type objects destroyed on container destruction" );
        REQUIRE( dctorcount == objectcount );
        }
    }

    SUBCASE( "Ctor/dctor calls on default construction, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        size_t objectcount;  // Ctor calls - dctor calls
        {
            const size_t SIZE = size_t(0);
            const TMSArray<Counter> tc;
            ctorcount = Counter::getCtorCount();
            dctorcount = Counter::getDctorCount();
            {
            INFO( "Number of ctor calls for container creation is about size" );
            //REQUIRE( ctorcount >= SIZE );  // Null test
            REQUIRE( ctorcount <= 2*SIZE+50 );
            }
            {
            INFO( "Number of dctor calls for container creation is small" );
            REQUIRE( dctorcount <= ctorcount );
            REQUIRE( dctorcount <= 2 );
            }

            objectcount = ctorcount - dctorcount;
            Counter::reset();
        }
        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "No value-type objects constructed on container destruction" );
        REQUIRE( ctorcount == 0 );
        }
        {
        INFO( "All value-type objects destroyed on container destruction" );
        REQUIRE( dctorcount == objectcount );
        }
    }

    SUBCASE( "Ctor/dctor calls on copy construction, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        size_t objectcount;  // Ctor calls - dctor calls
        {
            const TMSArray<Counter> tc;
            const TMSArray<Counter> tc2;

            ctorcount = Counter::getCtorCount();
            dctorcount = Counter::getDctorCount();
            objectcount = ctorcount - dctorcount;
            Counter::reset();
        }
        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "No value-type objects constructed on container destruction" );
        REQUIRE( ctorcount == 0 );
        }
        {
        INFO( "All value-type objects destroyed on container destruction" );
        REQUIRE( dctorcount == objectcount );
        }
    }

    SUBCASE( "Ctor/dctor calls on copy assignment, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        size_t objectcount;  // Ctor calls - dctor calls
        {
            const TMSArray<Counter> tc;
            TMSArray<Counter> tc2;
            tc2 = tc;

            ctorcount = Counter::getCtorCount();
            dctorcount = Counter::getDctorCount();
            objectcount = ctorcount - dctorcount;
            Counter::reset();
        }
        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "No value-type objects constructed on container destruction" );
        REQUIRE( ctorcount == 0 );
        }
        {
        INFO( "All value-type objects destroyed on container destruction" );
        REQUIRE( dctorcount == objectcount );
        }
    }

    SUBCASE( "Ctor/dctor calls on move construction, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        size_t objectcount;  // Ctor calls - dctor calls
        {
            TMSArray<Counter> tc;
            const TMSArray<Counter> tc2(std::move(tc));

            ctorcount = Counter::getCtorCount();
            dctorcount = Counter::getDctorCount();
            objectcount = ctorcount - dctorcount;
            Counter::reset();
        }
        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "No value-type objects constructed on container destruction" );
        REQUIRE( ctorcount == 0 );
        }
        {
        INFO( "All value-type objects destroyed on container destruction" );
        REQUIRE( dctorcount == objectcount );
        }
    }

    SUBCASE( "Ctor/dctor calls on move assignment, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        size_t objectcount;  // Ctor calls - dctor calls
        {
            TMSArray<Counter> tc;
            TMSArray<Counter> tc2;
            tc2 = std::move(tc);

            ctorcount = Counter::getCtorCount();
            dctorcount = Counter::getDctorCount();
            objectcount = ctorcount - dctorcount;
            Counter::reset();
        }
        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "No value-type objects constructed on container destruction" );
        REQUIRE( ctorcount == 0 );
        }
        {
        INFO( "All value-type objects destroyed on container destruction" );
        REQUIRE( dctorcount == objectcount );
        }
    }

    SUBCASE( "Ctor/dctor calls on swap, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        size_t objectcount;  // Ctor calls - dctor calls
        {
            TMSArray<Counter> tc1;
            TMSArray<Counter> tc2;

            ctorcount = Counter::getCtorCount();
            dctorcount = Counter::getDctorCount();
            objectcount = ctorcount - dctorcount;
            Counter::reset();

            tc1.swap(tc2);

            ctorcount = Counter::getDctorCount();
            dctorcount = Counter::getDctorCount();
            {
            INFO( "No value-type objects constructed on container swap" );
            REQUIRE( ctorcount == 0 );
            }
            {
            INFO( "No value-type objects destroyed on container swap" );
            REQUIRE( dctorcount == 0 );
            }

            Counter::reset();
        }
        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "No value-type objects constructed on container destruction" );
        REQUIRE( ctorcount == 0 );
        }
        {
        INFO( "All value-type objects destroyed on container destruction" );
        REQUIRE( dctorcount == objectcount );
        }
    }

    SUBCASE( "Ctor/dctor calls on resize, destruction" )
    {
        Counter::reset();
        size_t ctorcount;    // Number of ctor calls
        size_t dctorcount;   // Number of dctor calls
        bool throws;         // Does a resize throw
        {
            TMSArray<Counter> tc(10);

            // Resize much larger
            {
                try
                {
                    tc.resize(50000000);
                    throws = false;
                }
                catch (...)
                {
                    throws = true;
                }
            }
        }

        {
        INFO( "resize normally does not throw" );
        REQUIRE_FALSE( throws );
        }

        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();
        {
        INFO( "resize has no memory leak" );
        REQUIRE( ctorcount == dctorcount );
        }
    }
}


TEST_CASE( "TMSArray exceptions" )
{
    bool throws;
    bool throws_proper_type;
    size_t ctorcount;
    size_t dctorcount;

    SUBCASE( "Exceptions - copy ctor" )
    {
        Counter::reset(true);
        {
            const TMSArray<Counter> tc(10);

            try
            {
                TMSArray<Counter> tc2(tc);
                throws_proper_type = false;
            }
            catch (runtime_error & e)
            {
                throws_proper_type = true;
            }
            catch (...)
            {
                throws_proper_type = false;
            }
        }

        {
        INFO( "Copy ctor is exception-neutral" );
        REQUIRE( throws_proper_type );
        }

        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "Copy ctor has no memory leak" );
        REQUIRE( ctorcount == dctorcount );
        }
    }

    SUBCASE( "Exceptions - copy=" )
    {
        Counter::reset(true);
        {
            const TMSArray<Counter> tc(10);

            try
            {
                TMSArray<Counter> tc2;
                tc2 = tc;
                throws_proper_type = false;
            }
            catch (runtime_error & e)
            {
                throws_proper_type = true;
            }
            catch (...)
            {
                throws_proper_type = false;
            }
        }

        {
        INFO( "Copy assn is exception-neutral" );
        REQUIRE( throws_proper_type );
        }

        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();

        {
        INFO( "Copy assn has no memory leak" );
        REQUIRE( ctorcount == dctorcount );
        }
    }

    SUBCASE( "Exceptions - move ctor" )
    {
        Counter::reset(true);  // Copy operations throw
        {
            TMSArray<Counter> tc(10);

            try
            {
                TMSArray<Counter> tc2(std::move(tc));
                throws = false;
            }
            catch (...)
            {
                throws = true;
            }
        }

        {
        INFO( "Move ctor does not throw" );
        REQUIRE_FALSE( throws );
        }

        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();
        {
        INFO( "Move ctor has no memory leak" );
        REQUIRE( ctorcount == dctorcount );
        }
    }

    SUBCASE( "Exceptions - move=" )
    {
        Counter::reset(true);  // Copy operations throw
        {
            TMSArray<Counter> tc(10);

            try
            {
                TMSArray<Counter> tc2;
                tc2 = std::move(tc);
                throws = false;
            }
            catch (...)
            {
                throws = true;
            }
        }

        {
        INFO( "Move assn does not throw" );
        REQUIRE_FALSE( throws );
        }

        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();
        {  // Copy operations throw
        INFO( "Move assn has no memory leak" );
        REQUIRE( ctorcount == dctorcount );
        }
    }

    SUBCASE( "Exceptions - resize" )
    {
        Counter::reset(true);
        {
            TMSArray<Counter> tc(10);

            // Resize smaller
            {
                try
                {
                    tc.resize(5);
                    throws = false;
                }
                catch (...)
                {
                    throws = true;
                }
            }

            {
            INFO( "resize smaller does not throw" );
            REQUIRE_FALSE( throws );
            }

            // Resize much larger
            {
                try
                {
                    tc.resize(50000000);
                    throws_proper_type = false;
                }
                catch (runtime_error & e)
                {
                    throws_proper_type = true;
                }
                catch (...)
                {
                    throws_proper_type = false;
                }
            }
        }

        {
        INFO( "resize is exception-neutral" );
        REQUIRE( throws_proper_type );
        }

        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();
        {
        INFO( "resize has no memory leak" );
        REQUIRE( ctorcount == dctorcount );
        }
    }

    SUBCASE( "Exceptions - swap" )
    {
        Counter::reset(true);
        {
            TMSArray<Counter> tc1(10);
            TMSArray<Counter> tc2(1000);

            try
            {
                tc1.swap(tc2);
                throws = false;
            }
            catch (...)
            {
                throws = true;
            }
        }

        {
        INFO( "swap does not throw" );
        REQUIRE_FALSE( throws );
        }

        ctorcount = Counter::getCtorCount();
        dctorcount = Counter::getDctorCount();
        {
        INFO( "swap has no memory leak" );
        REQUIRE( ctorcount == dctorcount );
        }
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

