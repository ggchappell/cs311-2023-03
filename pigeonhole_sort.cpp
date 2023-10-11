// pigeonhole_sort.cpp
// Glenn G. Chappell
// 2023-10-10
//
// For CS 311 Fall 2023
// Pigeonhole Sort for 3-digit numbers

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <utility>
using std::swap;
#include <iterator>
using std::begin;
using std::end;
using std::distance;
#include <algorithm>
using std::move;
#include <chrono>
// Everything from <chrono> is preceded by std::
#include <cassert>
// For assert


// Size of large datasets
const size_t BIGSIZE = 100'000'000;

// Values in datasets range from 0 to MAXVAL
const int MAXVAL = 999;
// MAXVAL is relatively small here, because pigeonholeSort needs to make
// one bucket for each value 0 .. MAXVAL.


// pigeonholeSort
// Sorts a sequence of 3-digit nonnegative ints, using Pigeonhole Sort.
// Requirements on Types:
//     FDIter is be a forward iterator type.
//     FDIter must have value type int.
// Pre:
//     [first, last) is a valid range.
//     Each item in [first, last) is 0..999 (nonnegative, 3-digit)
template <typename FDIter>
void pigeonholeSort(FDIter first, FDIter last)
{
    // Setup buckets
    assert (MAXVAL > 0);
    const size_t NUM_BUCKETS = 1 + MAXVAL;  // Keys for Pigeonhole Sort:
                                            //  0 .. MAXVAL
    vector<vector<int>> buckets(NUM_BUCKETS);
                                   // Vector of buckets
    size_t size = distance(first, last);
    for (auto & b : buckets)
    {
        b.reserve(size);
    }

    // Place each item in the appropriate bucket (stable!)
    for (auto it = first; it != last; ++it)
    {
        int key = *it;
        buckets[key].push_back(key);
    }

    // Move each bucket back to original list, one after the other
    auto movespot = first;
    for (auto & b : buckets)  // Non-const so we can move
    {
        movespot = move(begin(b), end(b), movespot);
    }
}


// *********************************************************************
// Code to Call Sorting Function
//
// Place sorting call in function doSort!!!
// *********************************************************************


// timesec
// Returns time in seconds since the epoch. Resolution is nanoseconds,
// if the system provides this.
// Requires #include <chrono>.
double timesec()
{
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch());
    return static_cast<double>(nanos.count())/1.e9;
}


// doSort
// Wrapper function for our sorting algorithm. Sorts given range with
// messages before & after. Prints elapsed time.
//
// PLACE CALL TO THE PROPER SORTING ALGORITHM IN INDICATED LOCATION!!!
//
// Requirements on Types:
//     Same as sorting function.
// Pre:
//     Same as sorting function.
// Throws what & when sorting function throws.
template<typename Iter>
void doSort(Iter first,
            Iter last)
{
    // Message: before
    cout << "  Sorting ... ";
    cout.flush();

    // Get starting time
    double starttime = timesec();

    // *********************************************************
    // * THE FOLLOWING MUST BE THE APPROPRIATE SORTING CALL!!! *
    // *********************************************************
    pigeonholeSort(first, last);

    // Get ending time
    double endtime = timesec();

    // Message: after
    cout << "DONE" << endl;
    cout << "  Elapsed time: " << endtime-starttime << " (sec)" << endl;
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


// trySort_small
// Call doSort on small dataset. Values range from 0 to MAXVAL (global).
// Pre:
//    Preconditions, if any, for sorting call made by doSort.
void trySort_small()
{
    // Unprocessed version of dataset to sort
    auto rawdata = { 123456, 34, 0, 56, 2, 654321, 123, 1, 0, 99 };

    // Initial message
    cout << "Sorting trial: Small dataset\n";
    cout << "Size = " << intWithSep(rawdata.size()) << "\n";
    cout << "\n";

    // Make dataset
    vector<int> data;
    for (auto x : rawdata)
    {
        assert (x >= 0);
        data.push_back(x % (1+MAXVAL));
    }

    // Print initial data
    cout << "  Before:\n";
    cout << "    ";
    for (const auto & val : data)
        cout << val << " ";
    cout << "\n";

    // Sort
    doSort(begin(data), end(data));

    // Print final data
    cout << "  After:\n";
    cout << "    ";
    for (const auto & val : data)
        cout << val << " ";
    cout << endl;
}


// trySort_nearlySorted1
// Call doSort on nearly sorted data of type 1: all items close to their
// proper spots. Size is BIGSIZE (global). Values range from 0 to MAXVAL
// (global).
// Pre:
//    Preconditions, if any, for sorting call made by doSort.
void trySort_nearlySorted1()
{
    // Initial message
    cout << "Sorting trial: Nearly sorted type 1"
         << " (all items close to proper spots)\n";
    cout << "Size = " << intWithSep(BIGSIZE) << "\n";
    cout << "\n";

    // Make dataset
    vector<int> data(BIGSIZE);
    for (size_t i = 0; i < BIGSIZE; ++i)
    {
        size_t residue = i % 4;
        size_t ii = i + 3 - 2*residue;
        data[i] = int(double(ii) / BIGSIZE * MAXVAL);
    }

    // Sort
    doSort(begin(data), end(data));
}


// trySort_nearlySorted2
// Call doSort on nearly sorted data of type 2: few items out of order.
// Size is BIGSIZE (global). Values range from 0 to MAXVAL (global).
// Pre:
//    Preconditions, if any, for sorting call made by doSort.
void trySort_nearlySorted2()
{
    // Initial message
    cout << "Sorting trial: Nearly sorted type 2"
         << " (few items out of order)\n";
    cout << "Size = " << intWithSep(BIGSIZE) << "\n";
    cout << "\n";

    // Make dataset
    vector<int> data(BIGSIZE);
    for (size_t i = 0; i < BIGSIZE; ++i)
    {
        data[i] = int(double(i) / BIGSIZE * MAXVAL);
    }
    if (BIGSIZE >= 2)
    {
        swap(data[0], data[BIGSIZE-1]);
    }

    // Sort
    doSort(begin(data), end(data));
}


// trySort_messy
// Call doSort on "messy" data. Size is BIGISIZE (global). Values range
// from 0 to MAXVAL (global).
// This should give typical performance.
// Pre:
//    Preconditions, if any, for sorting call made by doSort.
void trySort_messy()
{
    // Initial message
    cout << "Sorting trial: random-ish data\n";
    cout << "Size = " << intWithSep(BIGSIZE) << "\n";
    cout << "\n";

    // Make dataset
    vector<int> data(BIGSIZE);
    const double phi = 1.6180339887498948482;
    for (size_t i = 0; i < BIGSIZE; ++i)
    {
        double x = double(i+1)*phi;
        double fracpart = x - int(x);
        data[i] = int(fracpart * (1+MAXVAL));
    }

    // Sort
    doSort(begin(data), end(data));
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Sorts a number of datasets, printing results.
int main()
{
    // ********** Dataset spec's **********

    cout << "Size of large datasets: ";
    cout << intWithSep(BIGSIZE) << ".\n";
    cout << "To change this, set BIGSIZE in the source code.\n";
    cout << "Values in datasets range from 0 to ";
    cout << intWithSep(MAXVAL) << ".\n";

    // ********** Sorting **********

    cout << "\n";
    trySort_small();

    cout << "\n";
    trySort_nearlySorted1();

    cout << "\n";
    trySort_nearlySorted2();

    cout << "\n";
    trySort_messy();

    // ********** Done **********

    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

