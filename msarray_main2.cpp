// msarray_main2.cpp
// Glenn G. Chappell
// 2023-10-22
//
// For CS 311 Fall 2023
// Simple program using class MSArray
// Requires msarray.hpp, msarray.cpp

#include "msarray.hpp"  // For class MSArray
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <iterator>
using std::begin;
using std::end;
#include <algorithm>
using std::sort;
#include <cassert>
// For assert


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Do some things with MSArray. Avoid moving, assigning, resizing,
// swapping of MSArray values.
int main()
{
    const MSArray::size_type ASIZE = 20;  // Size of our array

    // Print intro message
    cout << "Simple program using an MSArray object\n";
    cout << "Size of MSArray: " << ASIZE << "\n\n";

    // Create an MSArray and put some data in it.
    MSArray data(ASIZE);
    assert(data.size() == ASIZE);
    assert(!data.empty());
    for (MSArray::size_type i = 0; i < data.size(); ++i)
    {
        auto val = 2*i < ASIZE ? 20*((ASIZE-1)/2-i) : 20*(ASIZE-1-i)+10;
        data[i] = MSArray::value_type(val);
    }

    // Print initial data
    cout << "Initial data:\n";
    for (auto n : data)  // Range-based for-loop!
    {
        cout << n << " ";
    }
    cout << "\n\n";

    // Sort data
    sort(begin(data), end(data));  // STL algorithm!

    // Print sorted data
    cout << "Sorted data:\n";
    for (auto n : data)  // Another range-based for-loop!
    {
        cout << n << " ";
    }
    cout << "\n" << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

