// iterative_merge_sort.cpp
// Glenn G. Chappell
// 2023-10-04
//
// For CS 311 Fall 2023
// Iterative Merge Sort

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
using std::distance;
using std::iterator_traits;
#include <algorithm>
using std::move;
#include <chrono>
// Everything from <chrono> is preceded by std::
#include <cassert>
// For assert


// Size of large datasets
const size_t BIGSIZE = 100'000'000;

// Values in datasets range from 0 to MAXVAL
const int MAXVAL = 999'999'999;


// Function stableMerge copied from file merge_sort.cpp

// stableMerge
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
template <typename FDIter>
void stableMerge(FDIter first, FDIter middle, FDIter last)
{
    // Get type of what iterators point to
    using Value = typename iterator_traits<FDIter>::value_type;

    vector<Value> buffer(distance(first, last));
                               // Buffer for temporary copy of data
    auto in1 = first;          // Read location in 1st half
    auto in2 = middle;         // Read location in 2nd half
    auto out = begin(buffer);  // Write location in buffer

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1)  // Must do comparison this way, to be stable.
            *out++ = std::move(*in2++);
        else
            *out++ = std::move(*in1++);
    }

    // Move remainder of original sequence to buffer.
    // Only one of the following two calls will do anything, since the
    //  other is given an empty source range.
    // NOTE. This is the 3-parameter version of std::move (the "move"
    //  version of std::copy, declared in <algorithm>), not the
    //  1-parameter version (casts to an Rvalue, declared in <utility>).
    move(in1, middle, out);
    move(in2, last, out);

    // Move buffer contents back to original sequence location.
    move(begin(buffer), end(buffer), first);
}


// iterativeMergeSort
// Sort a range using iterative variant of Merge Sort.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid range.
// NOTE. We could make this iterative version of Merge Sort work with
// forward iterators, but it would be messy.
template <typename RAIter>
void iterativeMergeSort(RAIter first, RAIter last)
{
    // Compute size of entire range
    size_t size = last - first;

    // We merge ranges of size 1 into ranges of size 2. Then we merge
    // ranges of size 2 into ranges of size 4. This continues until
    // the entire range is sorted.
    //
    // The outer loop goes through sizes: 1, 2, 4, 8, etc. The inner
    // loop goes through pairs of ranges of the current size. Each pair
    // is merged into a single sorted range of twice that size. The last
    // subrange to be merged may need to be shorter.

    size_t partsize = 1;  // Size of two subranges to be merged
    while (partsize < size)
    {
        auto lo = first;  // Start of 1st subrange to be merged
        while (lo + partsize < last)
        {
            auto hi = lo + partsize * 2;
                          // Past end of 2nd subrange to be merged
            if (last < hi)
                hi = last;
            stableMerge(lo, lo + partsize, hi);

            lo = hi;      // Onward to the next pair of subranges
        }
        partsize *= 2;    // All ranges of current size have been
                          //  merged. Proceed to the next size
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
    iterativeMergeSort(first, last);

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

