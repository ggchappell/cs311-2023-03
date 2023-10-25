// msarray.cpp  HAND-OFF
// VERSION 6
// Glenn G. Chappell
// Started: 2023-10-17
// Updated: 2023-10-25
//
// For CS 311 Fall 2023
// Source for class MSArray
// Marvelously smart array of int
// Preliminary to Assignment 5


#include "msarray.hpp"  // For class MSArray definition
#include <algorithm>
using std::copy;


// *********************************************************************
// class MSArray - Member function definitions
// *********************************************************************


// Copy ctor
// See header for info.
MSArray::MSArray(const MSArray & other)
    :_capacity(other._capacity),
     _size(other.size()),
     _data(other._capacity == 0 ? nullptr
                                : new value_type[other._capacity])
{
    copy(other.begin(), other.end(), begin());
    // The above call to std::copy does not throw, since it copies int
    // values. But if value_type is changed, then the call may throw, in
    // which case this copy ctor may need to be rewritten.
}


// Move ctor
// See header for info.
MSArray::MSArray(MSArray && other) noexcept
    :_capacity(other._capacity),
     _size(other._size),
     _data(other._data)
{
    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
}


// Copy assignment operator
// See header for info.
MSArray & MSArray::operator=(const MSArray & other)
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// Move assignment operator
// See header for info.
MSArray & MSArray::operator=(MSArray && other) noexcept
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// resize
// See header for info.
void MSArray::resize(MSArray::size_type newsize)
{
    // TODO: WRITE THIS!!!
}


// insert
// See header for info.
MSArray::iterator MSArray::insert(MSArray::iterator pos,
                                  MSArray::value_type item)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// erase
// See header for info.
MSArray::iterator MSArray::erase(MSArray::iterator pos)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// swap
// See header for info.
void MSArray::swap(MSArray & other) noexcept
{
    // TODO: WRITE THIS!!!
}

