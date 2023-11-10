// heap_algs_main.cpp
// Glenn G. Chappell
// 2023-11-09
//
// For CS 311 Fall 2023
// Simple main program for Heap algorithms
// Requires heap_algs.hpp

#include "heap_algs.hpp"
// For Heap algorithms

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <algorithm>
using std::is_sorted;


// printInfo
// Given a range specified by two iterators and a bool indicating
// whether the range is expected to be a Heap. Prints values in given
// range, separated by blanks, ending with a blank and a newline.
// Determines whether range is a Heap, and prints message indicating
// result and whether this is what was expected.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     operator< is a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     Messages have been printed to cout.
// Exception neutral. Throws what & when a value-type operation throws.
// Strong guarantee.
// If operator< and cout << ... do not throw, then No-Throw Guarantee.
template<typename RAIter>
void printInfo(RAIter first, RAIter last,
               bool expectheap)
{
    for (auto it = first; it != last; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    bool isheap = heapTest(first, last);
    cout << "The above is";
    if (!isheap)
    {
        cout << " NOT";
    }
    cout << " a heap ("
         << (isheap == expectheap ? "good" : "BAD *******************")
         << ")" << endl;
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Demonstrates use of Heap algorithms.
int main()
{
    cout << "=================================================" << endl;
    cout << endl;

    // Initialize dataset #1
    vector<int> v1 { 20, 12, 8, 5, 10, 8, 4, 3, 1, 2 };
    cout << "Initialize dataset #1" << endl;
    cout << endl;

    printInfo(v1.begin(), v1.end(), true);
    cout << endl;

    // Do an insert
    v1.push_back(15);
    heapInsert(v1.begin(), v1.end());
    cout << "Heap insert 15" << endl;
    cout << endl;

    printInfo(v1.begin(), v1.end(), true);
    cout << endl;

    // Do another insert
    v1.push_back(11);
    heapInsert(v1.begin(), v1.end());
    cout << "Heap insert 11" << endl;
    cout << endl;

    printInfo(v1.begin(), v1.end(), true);
    cout << endl;

    cout << "=================================================" << endl;
    cout << endl;

    // Initialize dataset #2
    vector<int> v2 { 5, 3, 2, 9, 6, 7, 10, 4, 5, 1, -4 };
    cout << "Initialize dataset #2" << endl;
    cout << endl;

    printInfo(v2.begin(), v2.end(), false);
    cout << endl;

    // Make a heap
    heapMake(v2.begin(), v2.end());
    cout << "Heap make" << endl;
    cout << endl;

    printInfo(v2.begin(), v2.end(), true);
    cout << endl;

    // Do an insert
    v2.push_back(8);
    heapInsert(v2.begin(), v2.end());
    cout << "Heap insert 8" << endl;
    cout << endl;

    printInfo(v2.begin(), v2.end(), true);
    cout << endl;

    // Do a delete
    heapDelete(v2.begin(), v2.end());
    v2.pop_back();
    cout << "Heap delete" << endl;
    cout<< endl;

    printInfo(v2.begin(), v2.end(), true);
    cout << endl;

    // Sort it
    heapToSorted(v2.begin(), v2.end());
    cout << "Heap -> sorted" << endl;
    cout << endl;

    printInfo(v2.begin(), v2.end(), false);
    if (is_sorted(v2.begin(), v2.end()))
    {
        cout << "The above is sorted (good)" << endl;
    }
    else
    {
        cout << "The above is NOT sorted (BAD *******************)"
             << endl;
    }
    cout << endl;

    cout << "=================================================" << endl;
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

