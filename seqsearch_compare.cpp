// seqsearch_compare.cpp  UNFINISHED
// Glenn G. Chappell
// 2023-09-24
//
// For CS 311 Fall 2023
// Compare Sequential Search with Binary Search
// Uses Binary Search implementation from binsearch2.cpp

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstdint>
using std::int_fast64_t;
#include <algorithm>
using std::is_sorted;
#include <utility>
using std::pair;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <string>
using std::string;
using std::to_string;
#include <iterator>
using std::begin;
using std::end;
using std::distance;
using std::next;
#include <cassert>
// For assert


// Type bignum
// Type of values used for large-ish integers
// Should be a signed integer type.
using bignum = int_fast64_t;


// binSearch
// Does Binary Search on a range specified with iterators. Returns true
// if findme was found (using equivalence) in range, false otherwise.
// Recursive.
// Requirements on types:
//     FDIter is a forward iterator type.
//     ValueType is the value type of FDIter.
//     ValueType has a public operator<.
//     operator< is a total order on ValueType.
// Pre:
//     [first, last) is a valid range.
//     Values in the range are sorted by < (ascending).
// Throws what & when a ValueType operation (op<) throws. If no
// ValueType operation throws, then binSearch does not throw.
template <typename FDIter, typename ValueType>
bool binSearch(FDIter first,      // [first, last) is range to search
               FDIter last,
               const ValueType & findme)
                                  // value to find
{
    auto size = distance(first, last);  // Size of range

    // BASE CASE

    if (size <= 1)
    {
        if (size == 0)
            return false;
        return !(*first < findme) && !(findme < *first);
            // Check equivalence
    }

    // RECURSIVE CASE

    // Get iterator to pivot: item in middle position of range
    auto pivotiter = next(first, size/2);

    if (findme < *pivotiter)
    {   // Recursively search first half of range
        return binSearch(first, pivotiter, findme);
    }
    else
    {   // Recursively search second half of range
        return binSearch(pivotiter, last, findme);
    }
}


// tryBinSearch
// Try a search using function binSearch with the given data & key.
// Print result.
// Pre:
//     Values in data are sorted by < (ascending).
//     expect is true if key is equivalent to an item in data, false
//      otherwise.
// Throws what & when binSearch throws. If binSearch does not throw,
// then tryBinSearch does not throw.
void tryBinSearch(const vector<bignum> & data,  // Data to search in
                  bignum key,                   // Key to search for
                  bool expect)                  // Expected result
{
    // Do search
    cout << "Doing Binary Search for: " << key;
    cout.flush();

    bool success = binSearch(begin(data), end(data), key);

    // Print result
    cout << " - result: " << (success ? "found" : "not found");
    if (success == expect)
    {
        cout << " [correct]";
    }
    else
    {
        cout << " [INCORRECT] ****************************************";
    }
    cout << endl;
}


// seqSearch
// Does Sequential Search on a range specified with iterators. Returns
// true if findme was found (using equality) in range, false otherwise.
// Requirements on types:
//     FDIter is a forward iterator type.
//     ValueType is the value type of FDIter.
//     ValueType has a public operator==.
// Pre:
//     [first, last) is a valid range.
// Throws what & when a ValueType operation (op==) throws. If no
// ValueType operation throws, then seqSearch does not throw.
template <typename FDIter, typename ValueType>
bool seqSearch(FDIter first,      // [first, last) is range to search
               FDIter last,
               const ValueType & findme)
                                  // value to find
{
    return false;  // DUMMY
    // TODO: WRITE THIS!!!
}


// trySeqSearch
// Try a search using function seqSearch with the given data & key.
// Print result.
// Pre:
//     expect is true if key is equal to an item in data, false
//      otherwise.
// Throws what & when seqSearch throws. If seqSearch does not throw,
// then trySeqSearch does not throw.
void trySeqSearch(const vector<bignum> & data,  // Data to search in
                  bignum key,                   // Key to search for
                  bool expect)                  // Expected result
{
    // Do search
    cout << "Doing Sequential Search for: " << key;
    cout.flush();

    bool success = seqSearch(begin(data), end(data), key);

    // Print result
    cout << " - result: " << (success ? "found" : "not found");
    if (success == expect)
    {
        cout << " [correct]";
    }
    else
    {
        cout << " [INCORRECT] ****************************************";
    }
    cout << endl;
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// intWithSep
// Return string form of given integer with a separator (default: ",")
// every 3 digits.
// intWithSep(-123456789) returns "-123,456,789"s.
// intWithSep(1234567, ".") returns "1.234.567"s.
// Requirements on Types:
//     IntType must be an integer type.
template <typename IntType>
string intWithSep(IntType num,               // Integer to stringify
                  const string & sep = ",")  // Separator
{
    const auto SPACING = 3;  // How many digits between separators
    auto result = to_string(num);
    auto pos = result.size();
    while (pos > SPACING + (num < 0))
    {
        pos -= SPACING;
        result.insert(pos, sep);
    }
    return result;
}


// Main program
// Do several searches using binSearch, then do the same searches with
// seqSearch. Print results.
int main()
{
    // Size of dataset - CHANGE THIS! - MUST BE GREATER THAN 100
    const size_t SIZE = 500'000'000;
    cout << "If this program is too slow/fast, then change the value of"
         << "\n";
    cout << "SIZE, in function main, appropriately" << endl;
    cout << endl;

    assert(SIZE > 100);

    // Initialize data to search
    cout << "Initializing data, SIZE = "
         << intWithSep(SIZE)
         << " ... ";
    cout.flush();

    vector<bignum> data;
    data.reserve(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
        data.push_back(10*bignum(i));
    assert(is_sorted(begin(data), end(data)));

    cout << "DONE" << "\n";
    cout << endl;

    // List of searches to do
    const vector<pair<bignum, bool>> searchfor {
        { 10,            true },  // search key, expect success?
        { 1000,          true },
        { (SIZE/10)*10,  true },
        { (SIZE/2)*10,   true },
        { (SIZE-1)*10,   true },
        { -1,            false },
        { 11,            false },
        { (SIZE/2)*10+1, false },
        { (SIZE*10),     false }
    };

    // Wait for user before Binary Search calls
    cout << "Press ENTER for Binary Search calls ";
    userPause();
    cout << endl;

    // Do Binary Search calls
    for (const auto & p : searchfor)
    {
        tryBinSearch(data, p.first, p.second);
    }
    cout << endl;

    // Wait for user before Sequential Search calls
    cout << "Press ENTER for Sequential Search calls ";
    userPause();
    cout << endl;

    // Do Sequential Search calls
    for (const auto & p : searchfor)
    {
        trySeqSearch(data, p.first, p.second);
    }
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

