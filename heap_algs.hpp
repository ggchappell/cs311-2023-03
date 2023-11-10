// heap_algs.hpp  UNFINISHED
// Glenn G. Chappell
// 2023-11-09
//
// For CS 311 Fall 2023
// Header for Heap Algorithms
// There is no associated source file.

#ifndef FILE_HEAP_ALGS_HPP_INCLUDED
#define FILE_HEAP_ALGS_HPP_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::swap
#include <cassert>
// For assert


// heapTest
// Determines whether given random-access range is a Heap.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have <.
// Pre:
//     [first, last) is a valid range.
// Exception neutral. Throws what & when a value-type operation throws.
// Strong guarantee.
// If operator< does not throw, then No-Throw Guarantee.
template<typename RAIter>
bool heapTest(RAIter first, RAIter last)
{
    return true;  // DUMMY
    // TODO: WRITE THIS!!!
}


// heapInsert
// Heap insert operation on a random-access range.
// Inserts *(last-1) into Heap [first, last-1).
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have <, copy ctor, copy =.
// Pre:
//     [first, last) is a valid nonempty range.
//     [first, last-1) forms a Heap.
// Exception neutral. Throws what & when a value-type operation throws.
// Basic guarantee.
// If operator< and swap do not throw, then No-Throw Guarantee.
template<typename RAIter>
void heapInsert(RAIter first, RAIter last)
{
    // TODO: WRITE THIS!!!
}


// siftDown
// Internal-use function for heapDelete, heapMake.
// Does sift down of item at given location into existing partial Heap.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have <, copy ctor, copy =.
// Pre:
//     [first, last) is a valid nonempty range.
//     location lies in [first, last).
//     (location, last) is a partial Heap.
//      That is, !(first[(k-1)/2] < first[k]), whenever both
//      first+(k-1)/2 and first+k lie in (location, last).
// Exception neutral. Throws what & when a value-type operation throws.
// Basic guarantee.
// If operator< and swap do not throw, then No-Throw Guarantee.
template<typename RAIter>
void siftDown(RAIter first, RAIter last, RAIter location)
{
    std::size_t size = last-first;
    std::size_t curr = location-first;  // Index of item to sift down
    assert (curr < size);
    while (true)
    {
        std::size_t lchild = 2*curr+1;   // Index of left child, if any
        if (lchild >= size)              // Are there any children?
            break;                       // If not, done

        std::size_t bigchild = lchild;   // Index of bigger child
        if (lchild+1 < size && first[lchild] < first[lchild+1])
            bigchild = lchild+1;

        if (!(first[curr] < first[bigchild]))
            break;  // No more sifting; done

        // Sift down one level
        std::swap(first[curr], first[bigchild]);
        curr = bigchild;
    }
}


// heapDelete
// Heap delete operation on a random-access range.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have <, copy ctor, copy =.
// Pre:
//     [first, last) is a valid nonempty range.
//     [first, last) forms a Heap.
// Exception neutral. Throws what & when a value-type operation throws.
// Basic guarantee.
// If operator< and swap do not throw, then No-Throw Guarantee.
template<typename RAIter>
void heapDelete(RAIter first, RAIter last)
{
    // TODO: WRITE THIS!!!
}


// heapMake
// Turns the given random-access range into a Heap using a linear number
// of compare & swap operations.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have <, copy ctor, copy =.
// Pre:
//     [first, last) is a valid range.
// Exception neutral. Throws what & when a value-type operation throws.
// Basic guarantee.
// If operator< and swap do not throw, then No-Throw Guarantee.
template<typename RAIter>
void heapMake(RAIter first, RAIter last)
{
    // TODO: WRITE THIS!!!
}


// heapToSorted
// Given a Heap, sorts it by "<", ascending. Not stable.
// Sorts the given Heap.
// Requirements on Types:
//     RAIter is a random-access iterator type.
//     The value type of RAIter must have <, copy ctor, copy =.
// Pre:
//     [first, last) is a valid range.
//     [first, last) is a Heap.
// Exception neutral. Throws what & when a value-type operation throws.
// Basic guarantee.
// If operator< and swap do not throw, then No-Throw Guarantee.
template<typename RAIter>
void heapToSorted(RAIter first, RAIter last)
{
    // TODO: WRITE THIS!!!
}


#endif //#ifndef FILE_HEAP_ALGS_HPP_INCLUDED

