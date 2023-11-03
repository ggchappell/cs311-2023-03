// da6_test.cpp
// Glenn G. Chappell
// 2023-11-02
//
// For CS 311 Fall 2023
// Tests for Assignment 6 templates
// For Assignment 6, Exercises A, B
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, da6.hpp, llnode2.hpp

// Includes for code to be tested
#include "da6.hpp"           // For Assignment 6 templates
#include "da6.hpp"           // Double inclusion check, for testing only

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
#include "llnode2.hpp"       // For LLNode2
#include <cstddef>
using std::size_t;
#include <stdexcept>
using std::runtime_error;
#include <string>
using std::string;
#include <memory>
using std::unique_ptr;
#include <sstream>
using std::ostringstream;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <utility>
using std::pair;
using std::make_pair;
#include <ostream>
using std::ostream;
#include <stdexcept>
using std::out_of_range;

// Printable name for this test suite
const string test_suite_name =
    "Assignment 6 templates"
    " - CS 311 Assn 6, Ex A, B";


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


// print_list
// Given unique_ptr to Linked List, prints it to given output stream --
// or cout, if none is given -- a blank separating items, with a single
// trailing newline.
// Pre:
//     head points to empty-terminated Linked List, or is empty.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
//     ValType must have operator<< (stream insertion).
// Basic Guarantee
// Exception neutral
template <typename ValType>
void print_list(const unique_ptr<LLNode2<ValType>> & head,
                ostream & outstr = cout)
{
    auto p = head.get();
    while (p != nullptr)
    {
        outstr << p ->_data;
        p = p->_next.get();
        if (p != nullptr)
            outstr << " ";
    }
    outstr << endl;
}


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "reverseList: Size & items" )
{
    SUBCASE( "Empty list" )
    {
        unique_ptr<LLNode2<int>> head;
        reverseList(head);
        {
        INFO( "Empty list, reversed, should be empty" );
        REQUIRE( !head );
        }
    }

    SUBCASE( "List of size 1" )
    {
        unique_ptr<LLNode2<int>> head;
        push_front(head, 5);
        reverseList(head);
        {
        INFO( "List of size 1, reversed, should have size 1" );
        REQUIRE( size(head) == 1 );
        }

        ostringstream outs;
        print_list(head, outs);
        {
        INFO( "List of size 1, reversed, should have same item" );
        REQUIRE( outs.str() == "5\n" );
        }
    }

    SUBCASE( "List of size 2" )
    {
        unique_ptr<LLNode2<int>> head;
        push_front(head, 14);
        push_front(head, 6);
        reverseList(head);
        {
        INFO( "List of size 2, reversed, should have size 2" );
        REQUIRE( size(head) == 2 );
        }

        ostringstream outs;
        print_list(head, outs);
        {
        INFO( "List of size 2, reversed, should have reversed items" );
        REQUIRE( outs.str() == "14 6\n" );
        }
    }

    SUBCASE( "List of size 3" )
    {
        unique_ptr<LLNode2<int>> head;
        push_front(head, 10);
        push_front(head, 24);
        push_front(head, -3);
        reverseList(head);
        {
        INFO( "List of size 3, reversed, should have size 3" );
        REQUIRE( size(head) == 3 );
        }

        ostringstream outs;
        print_list(head, outs);
        {
        INFO( "List of size 3, reversed, should have reversed items" );
        REQUIRE( outs.str() == "10 24 -3\n" );
        }
    }

    SUBCASE( "List of size 4" )
    {
        unique_ptr<LLNode2<int>> head;
        push_front(head, 5);
        push_front(head, 8);
        push_front(head, 1);
        push_front(head, 6);
        reverseList(head);
        {
        INFO( "List of size 4, reversed, should have size 4" );
        REQUIRE( size(head) == 4 );
        }

        ostringstream outs;
        print_list(head, outs);
        {
        INFO( "List of size 4, reversed, should have reversed items" );
        REQUIRE( outs.str() == "5 8 1 6\n" );
        }
    }

    SUBCASE( "List of size 20" )
    {
        unique_ptr<LLNode2<int>> head;
        for (int i = 0; i < 20; ++i)
        {
            push_front(head, 3*i);
        }
        reverseList(head);
        {
        INFO( "List of size 20, reversed, should have size 20" );
        REQUIRE( size(head) == 20 );
        }

        ostringstream outs;
        print_list(head, outs);
        {
        INFO( "List of size 20, reversed, should have reversed items" );
        string s1 = "0 3 6 9 12 15 18 21 24 27 ";
        string s2 = "30 33 36 39 42 45 48 51 54 57\n";
        REQUIRE( outs.str() == s1+s2 );
        }
    }
}


TEST_CASE( "reverseList: Other requirements" )
{
    SUBCASE( "No value-type operations" )
    {
        const int SIZE = 1000;  // Size of list

        Counter::reset();
        unique_ptr<LLNode2<Counter>> head;
        for (int i = 0; i < SIZE; ++i)
            push_front(head, Counter());
        Counter::reset();
        reverseList(head);

        {
        INFO( "reverseList does no value-type construction" );
        REQUIRE( Counter::getCtorCount() == 0 );
        }
        {
        INFO( "reverseList does no value-type destruction" );
        REQUIRE( Counter::getDctorCount() == 0 );
        {
        }
        INFO( "reverseList does no value-type assignment" );
        REQUIRE( Counter::getAssnCount() == 0 );
        }
    }
}


TEST_CASE( "SlowMap: Member function return Types" )
{
    SUBCASE( "Member function empty - return type")
    {
        {
        const SlowMap<int, string> m;
        bool && r(m.empty());
        (void)r;  // Avoid unused-variable warning
        INFO( "const SlowMap<T,U>::empty returns bool by val" );
        REQUIRE( TypeCheck<bool>::check(m.empty()) );
        }

        {
        SlowMap<int, string> m;
        bool && r(m.empty());
        (void)r;  // Avoid unused-variable warning
        INFO( "non-const SlowMap<T,U>::empty returns bool by val" );
        REQUIRE( TypeCheck<bool>::check(m.empty()) );
        }
    }

    SUBCASE( "Member function size - return type")
    {
        {
        const SlowMap<int, string> m;
        size_t && r(m.size());
        (void)r;  // Avoid unused-variable warning
        INFO( "const SlowMap<T,U>::size returns size_t by val" );
        REQUIRE( TypeCheck<size_t>::check(m.size()) );
        }

        {
        SlowMap<int, string> m;
        size_t && r(m.size());
        (void)r;  // Avoid unused-variable warning
        INFO( "non-const SlowMap<T,U>::size returns size_t by val" );
        REQUIRE( TypeCheck<size_t>::check(m.size()) );
        }
    }

    SUBCASE( "Member function get - return type")
    {
        {
        SlowMap<int, string> m;
        m.set(1, "abc");
        const SlowMap<int, string> & cm(m);
        const string & r(cm.get(1));
        (void)r;  // Avoid unused-variable warning
        INFO( "const SlowMap<int,string>::get returns string"
              " by ref-to-const" );
        REQUIRE( TypeCheck<const string &>::check(cm.get(1)) );
        }

        {
        SlowMap<int, string> m;
        m.set(1, "abc");
        string & r(m.get(1));
        (void)r;  // Avoid unused-variable warning
        INFO( "non-const SlowMap<int,string>::get returns string"
              " by ref" );
        REQUIRE( TypeCheck<string &>::check(m.get(1)) );
        }

        {
        SlowMap<int, int> m;
        m.set(1, 2);
        const SlowMap<int, int> & cm(m);
        const int & r(cm.get(1));
        (void)r;  // Avoid unused-variable warning
        INFO( "const SlowMap<int,int>::get returns int"
              " by ref-to-const" );
        REQUIRE( TypeCheck<const int &>::check(cm.get(1)) );
        }

        {
        SlowMap<int, int> m;
        m.set(1, 2);
        int & r(m.get(1));
        (void)r;  // Avoid unused-variable warning
        INFO( "non-const SlowMap<int,int>::get returns int by ref" );
        REQUIRE( TypeCheck<int &>::check(m.get(1)) );
        }

        {
        SlowMap<string, string> m;
        m.set("xyz", "abc");
        const SlowMap<string, string> & cm(m);
        const string & r(cm.get("xyz"));
        (void)r;  // Avoid unused-variable warning
        INFO( "const SlowMap<string,string>::get returns string"
              " by ref-to-const" );
        REQUIRE( TypeCheck<const string &>::check(cm.get("xyz")) );
        }

        {
        SlowMap<string, string> m;
        m.set("xyz", "abc");
        string & r(m.get("xyz"));
        (void)r;  // Avoid unused-variable warning
        INFO( "non-const SlowMap<string,string>::get returns string"
              " by ref" );
        REQUIRE( TypeCheck<string &>::check(m.get("xyz")) );
        }
    }
}


TEST_CASE( "SlowMap: set, get, erase" )
{
    SUBCASE( "Empty SlowMap" )
    {
        SlowMap<int, string> m;
        const SlowMap<int, string> cm;

        {
            INFO( "empty #1 returns true for empty SlowMap" );
            REQUIRE( m.empty() );
        }
        {
            INFO( "size #1 returns 0 for empty SlowMap" );
            REQUIRE( m.size() == 0 );
        }
        {
            INFO( "present #1 on empty SlowMap returns false" );
            REQUIRE( m.present(1) == false );
        }
        {
            INFO( "present #2 on empty SlowMap returns false" );
            REQUIRE( m.present(100) == false );
        }
        {
            INFO( "empty #2 returns true for empty SlowMap" );
            REQUIRE( m.empty() );
        }
        {
            INFO( "size #2 returns 0 for empty SlowMap" );
            REQUIRE( m.size() == 0 );
        }
        {
            INFO( "get throws out_of_range for empty SlowMap" );
            try
            {
                m.get(1);
                REQUIRE(false);
            }
            catch(out_of_range & e)
            {
                REQUIRE(true);
                INFO( "'what' member of exception is not empty" );
                REQUIRE(e.what() != "");
            }
            catch(...)
            {
                REQUIRE(false);
            }
        }
        {
            INFO( "get throws out_of_range for empty const SlowMap" );
            try
            {
                cm.get(1);
                REQUIRE(false);
            }
            catch(out_of_range & e)
            {
                REQUIRE(true);
                INFO( "'what' member of exception is not empty" );
                REQUIRE(e.what() != "");
            }
            catch(...)
            {
                REQUIRE(false);
            }
        }
    }

    SUBCASE( "Size 1 SlowMap" )
    {
        SlowMap<int, string> m;
        m.set(100, "abc");
        const SlowMap<int, string> & cm(m);

        {
            INFO( "empty returns false for size 1 SlowMap" );
            REQUIRE( !m.empty() );
        }
        {
            INFO( "size returns 1 for size-1 SlowMap" );
            REQUIRE( m.size() == 1 );
        }
        {
            INFO( "present #1 on size-1 SlowMap returns nullptr" );
            REQUIRE( m.present(1) == false );
        }
        {
            INFO( "present #2 on size-1 SlowMap returns true" );
            REQUIRE( m.present(100) == true );
        }
        {
            INFO( "get #1 on size-1 SlowMap throws out_of_range" );
            try
            {
                m.get(1);
                REQUIRE(false);
            }
            catch (out_of_range & e)
            {
                REQUIRE(true);
                INFO( "'what' member of exception is not empty" );
                REQUIRE(e.what() != "");
            }
            catch (...)
            {
                REQUIRE(false);
            }
        }
        {
            INFO( "get #2 on size-1 SlowMap returns value" );
            auto v = m.get(100);
            REQUIRE(v == "abc");
        }
        {
            INFO( "get #1 on size-1 const SlowMap"
                  "throws out_of_range" );
            try
            {
                cm.get(1);
                REQUIRE(false);
            }
            catch (out_of_range & e)
            {
                REQUIRE(true);
                INFO( "'what' member of exception is not empty" );
                REQUIRE(e.what() != "");
            }
            catch (...)
            {
                REQUIRE(false);
            }
        }
        {
            INFO( "get #2 on size-1 const SlowMap returns value" );
            auto v = cm.get(100);
            REQUIRE(v == "abc");
        }
    }

    SUBCASE( "Size 2 SlowMap" )
    {
        SlowMap<int, string> m;
        m.set(100, "abc");
        m.set(101, "def");

        {
            INFO( "empty returns false for size 2 SlowMap" );
            REQUIRE( !m.empty() );
        }
        {
            INFO( "size returns 2 for size-2 SlowMap" );
            REQUIRE( m.size() == 2 );
        }
        {
            INFO( "present #1 on size-2 SlowMap returns false" );
            REQUIRE( m.present(1) == false );
        }
        {
            INFO( "get #1 on size-2 SlowMap throws out_of_range" );
            try
            {
                m.get(1);
                REQUIRE(false);
            }
            catch (out_of_range & e)
            {
                REQUIRE(true);
                INFO( "'what' member of exception is not empty" );
                REQUIRE(e.what() != "");
            }
            catch (...)
            {
                REQUIRE(false);
            }
        }
        {
            INFO( "present #2 on size-2 SlowMap returns true" );
            REQUIRE( m.present(100) == true );
        }
        {
            INFO( "get #2 on size-2 SlowMap returns value inserted" );
            REQUIRE( m.get(100) == "abc" );
        }
        {
            INFO( "present #3 on size-2 SlowMap returns true" );
            REQUIRE( m.present(101) == true );
        }
        {
            INFO( "get #3 on size-2 SlowMap returns value inserted" );
            REQUIRE( m.get(101) == "def" );
        }
        {
            INFO( "present #4 on size-2 SlowMap returns false" );
            REQUIRE( m.present(200) == false );
        }
    }

    SUBCASE( "Modifying value in map" )
    {
        SlowMap<int, string> m;
        m.set(100, "abc");
        m.set(101, "def");

        {
            INFO( "get #1 on size-2 SlowMap returns value inserted" );
            REQUIRE( m.get(100) == "abc" );
        }
        {
            INFO( "get #2 on size-2 SlowMap returns value inserted" );
            REQUIRE( m.get(101) == "def" );
        }

        m.get(100) = "x";

        {
            INFO( "get #1 on size-2 SlowMap returns new value" );
            REQUIRE( m.get(100) == "x" );
        }
        {
            INFO( "get #2 on size-2 SlowMap returns original value" );
            REQUIRE( m.get(101) == "def" );
        }
    }

    SUBCASE( "Larger map, with erase calls" )
    {
        const int SIZE = 1000;  // Size for loops
        SlowMap<int, int> m;
        for (int i = 0; i < SIZE*2; ++i)
        {
            m.set(i, 2*i);
        }

        {
            INFO( "Size is correct after inserts" );
            REQUIRE( m.size() == SIZE*2 );
        }

        for (int i = 0; i < SIZE*2; i += 2)
        {
            m.erase(i);
        }

        {
            INFO( "Size is correct after erase" );
            REQUIRE( m.size() == SIZE );
        }

        {
            INFO( "present #1 returns false" );
            REQUIRE( m.present(10) == false );
        }
        {
            INFO( "get #1 throws out_of_range" );
            try
            {
                m.get(10);
                REQUIRE(false);
            }
            catch (out_of_range & e)
            {
                REQUIRE(true);
                INFO( "'what' member of exception is not empty" );
                REQUIRE(e.what() != "");
            }
            catch (...)
            {
                REQUIRE(false);
            }
        }
        {
            INFO( "present #2 returns true" );
            REQUIRE( m.present(11) == true );
        }
        {
            INFO( "get #2 returns inserted value" );
            REQUIRE( m.get(11) == 22 );
        }

        m.erase(11);

        {
            INFO( "present #2 returns false after single erase" );
            REQUIRE( m.present(11) == false );
        }
        {
            INFO( "get #2 throws out_of_range after single erase" );
            try
            {
                m.get(11);
                REQUIRE(false);
            }
            catch (out_of_range & e)
            {
                REQUIRE(true);
                INFO( "'what' member of exception is not empty" );
                REQUIRE(e.what() != "");
            }
            catch (...)
            {
                REQUIRE(false);
            }
        }
        {
            INFO( "Size is correct after single erase" );
            REQUIRE( m.size() == SIZE-1 );
        }

        m.set(11, 72);

        {
            INFO( "present #2 returns true after single insert" );
            REQUIRE( m.present(11) == true );
        }
        {
            INFO( "get #2 returns inserted value after single insert" );
            REQUIRE( m.get(11) == 72 );
        }
    }
}


TEST_CASE( "SlowMap: traverse" )
{
    SUBCASE( "Traverse of empty map" )
    {
        SlowMap<int, int> m;
        vector<pair<int, int>> expected {
        };

        vector<pair<int, int>> data;
        m.traverse(
            [&](int k, int v)
            { data.push_back(make_pair(k, v)); }
        );
        sort(data.begin(), data.end());
        REQUIRE( data == expected );
    }

    SUBCASE( "Traverse of size-1 map" )
    {
        SlowMap<int, int> m;
        m.set(5, 7);
        vector<pair<int, int>> expected {
            { 5, 7 }
        };

        vector<pair<int, int>> data;
        m.traverse(
            [&](int k, int v)
            { data.push_back(make_pair(k, v)); }
        );
        sort(data.begin(), data.end());
        REQUIRE( data == expected );
    }

    SUBCASE( "Traverse of size-4 map" )
    {
        SlowMap<int, int> m;
        m.set(5, 7);
        m.set(8, 3);
        m.set(1, 8);
        m.set(7, 4);
        vector<pair<int, int>> expected {
            { 1, 8 },
            { 5, 7 },
            { 7, 4 },
            { 8, 3 }
        };

        vector<pair<int, int>> data;
        m.traverse(
            [&](int k, int v)
            { data.push_back(make_pair(k, v)); }
        );
        sort(data.begin(), data.end());
        REQUIRE( data == expected );
    }

    SUBCASE( "Traverse of map after inserts & erase" )
    {
        const int SIZE = 1000;  // Size for loops
        SlowMap<int, int> m;
        for (int i = 0 ; i < SIZE*4; ++i)
        {
            m.set(i, 3*i);
        }
        for (int i = 0; i < SIZE*4; i += 2 )
        {
            m.erase(i);
        }
        for (int i = SIZE*10; i < SIZE*12; ++i)
        {
            m.set(i, 3*i);
        }
        for (int i = 3; i < SIZE*4; i += 4)
        {
            m.erase(i);
        }
        for (int i = SIZE*10; i < SIZE*12; i += 2)
        {
            m.erase(i);
        }

        vector<pair<int, int>> expected;
        for (int i = 1; i < SIZE*4; i += 4)
        {
            expected.push_back(make_pair(i, i*3));
        }
        for (int i = SIZE*10+1; i < SIZE*12; i += 2)
        {
            expected.push_back(make_pair(i, i*3));
        }

        vector<pair<int, int>> data;
        m.traverse(
            [&](int k, int v)
            { data.push_back(make_pair(k, v)); }
        );
        sort(data.begin(), data.end());
        REQUIRE( data == expected );
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
        cout << "BEGIN tests for " << test_suite_name << "\n"
             << endl;
        dtresult = dtcontext.run();
        cout << "END tests for " << test_suite_name << "\n"
             << endl;
    }

    // If we want to do something else here, then we need to check
    // context.shouldExit() first.

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from doctest
    return dtresult;
}

