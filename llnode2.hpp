// llnode2.hpp  UNFINISHED
// Glenn G. Chappell
// 2023-10-26
//
// For CS 311 Fall 2023
// Header for struct LLNode2
// Singly Linked List node
// Based on llnode.hpp. Function size from use_list.cpp.
// There is no associated source file.

#ifndef FILE_LLNODE2_HPP_INCLUDED
#define FILE_LLNODE2_HPP_INCLUDED

#include <cstddef>
// For std::size_t


// *********************************************************************
// struct LLNode2 - Struct definition
// *********************************************************************


// struct LLNode2
// Singly Linked List node, with client-specified value type
// Invariants:
//     Either _next is nullptr, or _next points to an LLNode2, allocated
//      with new, owned by *this.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
template <typename ValType>
struct LLNode2 {
    ValType    _data;  // Data for this node
    LLNode2 *  _next;  // Ptr to next node, or nullptr if none

    // The following simplify creation & destruction

    // 1- & 2-param ctor
    // _data is set to data (given). _next is set to next, if given, or
    // nullptr if not.
    // Pre:
    //     theNext, if passed, is either nullptr, or else it points to
    //      an LLNode2 allocated with new, with ownership transferred to
    //      *this.
    explicit LLNode2(const ValType & data,
                     LLNode2 * next = nullptr)
        :_data(data),
         _next(next)
    {}

    // dctor
    // Does delete on _next.
    ~LLNode2()
    { delete _next; }

    // No default ctor, no copy/move operations.
    LLNode2() = delete;
    LLNode2(const LLNode2 & other) = delete;
    LLNode2 & operator=(const LLNode2 & other) = delete;
    LLNode2(LLNode2 && other) = delete;
    LLNode2 & operator=(LLNode2 && other) = delete;

};  // End struct LLNode2


// *********************************************************************
// struct LLNode2 - Associated global functions
// *********************************************************************


// size
// Given ptr to Linked List, return its size (number of nodes).
// Pre:
//     head is ptr to nullptr-terminated Linked List, or nullptr for
//      empty Linked List.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode2<ValType>; no member
// functions of ValType are actually used here.
template <typename ValType>
std::size_t size(const LLNode2<ValType> * head)
{
    auto p = head;            // Iterates through list
    std::size_t counter = 0;  // Number of nodes so far
    while (p != nullptr)
    {
        p = p->_next;
        ++counter;
    }
    return counter;
}


#endif  //#ifndef FILE_LLNODE2_HPP_INCLUDED

