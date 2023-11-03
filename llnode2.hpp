// llnode2.hpp
// Glenn G. Chappell
// Started: 2023-10-26
// Updated: 2023-10-30
//
// For CS 311 Fall 2023
// Header for struct LLNode2
// Singly Linked List node using smart pointers
//  + associated functionality
// Based on llnode.hpp. Function size from use_list.cpp.
// There is no associated source file.

#ifndef FILE_LLNODE2_HPP_INCLUDED
#define FILE_LLNODE2_HPP_INCLUDED

#include <cstddef>
// For std::size_t
#include <memory>
// For std::unique_ptr
// For std::make_unique
#include <utility>
// For std::move


// *********************************************************************
// Forward declarations
// *********************************************************************


template <typename ValType>
struct LLNode2;

template <typename ValType>
void pop_front(std::unique_ptr<LLNode2<ValType>> & head) noexcept;


// *********************************************************************
// struct LLNode2 - Struct definition
// *********************************************************************


// struct LLNode2
// Singly Linked List node, with client-specified value type
// Invariants:
//     Either _next is null or _next points to an LLNode2 (and thus
//      _next points to a null-ptr-terminated Linked List of LLNode2).
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
template <typename ValType>
struct LLNode2 {
    ValType                  _data;  // Data for this node
    std::unique_ptr<LLNode2> _next;  // Ptr to next node, null if none

    // The following simplify creation & destruction

    // 1- & 2-param ctor
    // _data is set to data (given). _next is set to next, if given, or
    // nullptr if not.
    // No-Throw Guarantee
    explicit LLNode2(const ValType & data,
                     std::unique_ptr<LLNode2> & next = nullptr)
        :_data(data),
         _next(std::move(next))
    {}

    // dctor
    // Iterative: avoid recursive destruction.
    // No-Throw Guarantee
    ~LLNode2()
    {
        while (_next)
            pop_front(_next);
    }

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
// Given unique_ptr to Linked List, return its size (number of nodes).
// Pre:
//     head is ptr to null-terminated Linked List, or is null.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode2<ValType>; no member
// functions of ValType are actually used here.
// No-Throw Guarantee
template <typename ValType>
std::size_t size(const std::unique_ptr<LLNode2<ValType>> & head) noexcept
{
    auto p = head.get();      // Iterates through list
    std::size_t counter = 0;  // Number of nodes so far
    while (p != nullptr)
    {
        p = p->_next.get();
        ++counter;
    }
    return counter;
}


// push_front
// Given unique_ptr to Linked List, and a ValType item, push the item
// onto the front of the list. head becomes a pointer to the new list.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode2<ValType>; no member
// functions of ValType are actually used here.
// Strong Guarantee
// Exception Neutral
template <typename ValType>
void push_front(std::unique_ptr<LLNode2<ValType>> & head,
                const ValType & item)
{
    head = std::make_unique<LLNode2<ValType>>(item, head);
}


// pop_front
// Given unique_ptr to Linked List, removes first item from list, if
// list is nonempty. If list is empty, does nothing.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode2<ValType>; no member
// functions of ValType are actually used here.
// No-Throw Guarantee
template <typename ValType>
void pop_front(std::unique_ptr<LLNode2<ValType>> & head) noexcept
{
    if (head)
    {
        auto savenext = std::move(head->_next);
        head = std::move(savenext);
    }
}


#endif  //#ifndef FILE_LLNODE2_HPP_INCLUDED

