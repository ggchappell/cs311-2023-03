// quicksort2.cpp  UNFINISHED
// Glenn G. Chappell
// 2023-10-06
//
// For CS 311 Fall 2023
// Quicksort
// Implementation #2: Optimized

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
using std::move;
#include <iterator>
using std::begin;
using std::end;
#include <algorithm>
using std::iter_swap;
#include <chrono>
// Everything from <chrono> is preceded by std::
#include <cassert>
// For assert


// Size of large datasets
const size_t BIGSIZE = 100'000'000;

// Values in datasets range from 0 to MAXVAL
const int MAXVAL = 999'999'999;


// Function insertionSort copied from file insertion_sort.cpp

// insertionSort
// Sort a range using Insertion Sort.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have a copy ctor, copy assignment,
//      and operator<.
//     operator< is a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid range.
template <typename RAIter>
void insertionSort(RAIter first, RAIter last)
{
    // NOTE. We *could* rewrite the following code using iterators
    //  instead of indices. Then we this function would be able to take
    //  parameters that are bidirectional iterators, instead of only
    //  random-access iterators.

    // Compute size of range
    size_t size = last - first;

    // Iterate through items, inserting each into earlier items
    for (size_t i = 1; i != size; ++i)
    {
        // We need to insert item i into sorted list of items 0 .. i-1

        auto save_item_i = std::move(first[i]);

        // Find the spot for item i, moving up other items as we go
        size_t k;  // We use k after the loop, so declare it outside
        for (k = i; k != 0; --k)
            // Be careful! Backwards loop with unsigned counter
        {
            if (!(save_item_i < first[k-1]))
                break;
            first[k] = std::move(first[k-1]);
        }

        // Item i should be in spot k; put it there
        first[k] = std::move(save_item_i);
        // NOTE. I had "if (k != i)" above, but that would leave
        //  first[i] in a moved-from state when k == i.
    }
}


// hPartition
// Partitions a sequence about a given pivot. Uses Hoare Algorithm.
// Returns the new pivot position via a reference parameter.
//
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have copy=, operator<.
//     operator< must be a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid nonempty range.
//     pivotiter is an iterator in the range [first, last).
// NOTE. We could make Hoare Partition work with bidirectional
// iterators, but it would be messier.
template <typename RAIter>
void hPartition(RAIter first, RAIter last,  // Range to partition
                RAIter & pivotiter)         // Iterator to pivot
{
    // Put the pivot at the start of the list
    if (first != pivotiter)
        iter_swap(first, pivotiter);

    // first points to the pivot

    // Iterator left: all items before it have !(PIVOT < ITEM)
    auto left = first+1;
    // Iterator right: all items after it have !(ITEM < PIVOT)
    auto right = last-1;

    // In the loop below, we stop when items before left + items
    //  after right are the entire list.
    while (left <= right)
    {
        // Move left & right in as far as we can
        while (left <= right && !(*first < *left))
            ++left;
        while (left <= right && !(*right < *first))
            --right;

        // If left & right have not collided, swap their items
        if (left < right)
        {
            iter_swap(left, right);
            ++left;
            --right;
        }
    }
    assert (right >= first);
    assert (right+1 == left);

    // Note new pivot position for caller, and put pivot there
    pivotiter = right;
    if (first != pivotiter)
        iter_swap(first, pivotiter);
}


// medianOf3
// Given 3 iterators, finds the median of the values they reference and
// returns an iterator to it. Values are not altered; return value is
// always equal to one of the parameters. Has properties necessary for
// stable sort.
//
// Does the same comparisons as an Insertion Sort of a 3-item list, but
// does not modify the list.
// Requirements on Types:
//     Iter is an iterator type.
// Pre:
//     ai, bi, ci are valid iterators.
template <typename Iter>
Iter medianOf3(Iter ai, Iter bi, Iter ci)
{
    if (*bi < *ai)
    {
        if (*ci < *ai)
            return (*ci < *bi) ? bi : ci;
        else
            return ai;
    }
    else
    {
        if (*ci < *bi)
            return (*ci < *ai) ? ai : ci;
        else
            return bi;
    }
}


// quicksort
// Sort a range, using Quicksort optimized with median-of-three
// pivot selection, tail-recursion elimination on the larger
// recursive call, and an Insertion Sort finish.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     operator< is a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid range.
template <typename RAIter>
void quicksort(RAIter first, RAIter last)
{
    // TODO: WRITE THIS!!!
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
    quicksort(first, last);

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

    // MESSY-DATA TRIAL MOVED BEFORE NEARLY-SORTED DATA TRIALS
    cout << "\n";
    trySort_messy();

    cout << "\n";
    trySort_nearlySorted1();

    cout << "\n";
    trySort_nearlySorted2();

    // ********** Done **********

    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

