// da3.hpp  SKELETON
// Glenn G. Chappell
// 2023-09-21
//
// For CS 311 Fall 2023
// Header for Assignment 3 functions

#ifndef FILE_DA3_HPP_INCLUDED
#define FILE_DA3_HPP_INCLUDED

#include "llnode.hpp"  // For LLNode
#include <cstddef>     // For std::size_t
#include <functional>  // For std::function


template <typename ValueType>
ValueType lookup(const LLNode<ValueType> * head,
                 std::size_t index)
{
    return ValueType();  // DUMMY
    // TODO: WRITE THIS!!!
}


// Implementation in source file
void didItThrow(const std::function<void()> & ff,
                bool & threw);


template <typename FDIter>
bool checkSorted(FDIter first,
                 FDIter last)
{
    return false;  // DUMMY
    // TODO: WRITE THIS!!!
}


// Implementation in source file
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DA3_HPP_INCLUDED

