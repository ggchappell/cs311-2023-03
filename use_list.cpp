// use_list.cpp
// Glenn G. Chappell
// Started: 2023-09-17
// Updated: 2023-09-18
//
// For CS 311 Fall 2023
// Singly Linked List example: create & find size

#include "llnode.hpp"  // For struct LLNode
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstddef>
using std::size_t;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// size
// Given ptr to Linked List, return its size (number of nodes).
// Pre:
//     head is ptr to nullptr-terminated Linked List, or nullptr for
//      empty Linked List.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode<ValType>; no member
// functions of ValType are actually used here.
template <typename ValType>
size_t size(const LLNode<ValType> * head)
{
    auto p = head;       // Iterates through list
    size_t counter = 0;  // Number of nodes so far
    while (p != nullptr)
    {
        p = p->_next;
        ++counter;
    }
    return counter;
}


// Main program
// Creates a Linked List and finds its size.
int main()
{
    const size_t THESIZE = 507;  // Size of list to create

    // Create empty list
    cout << "Creating empty Linked List" << "\n";
    LLNode<int> * head = nullptr;

    // Add nodes to list
    cout << "Adding " << THESIZE << " nodes to Linked List" << "\n";
    for (size_t i = 0; i < THESIZE ; ++i)
    {
        head = new LLNode<int>(int(THESIZE-i), head);
    }
    cout << endl;

    // Find & print size of Linked List
    auto s = size(head);
    cout << "Computed size of Linked List: " << s << " - ";
    cout << (s == THESIZE
               ? "right!"
               : "WRONG **********************************************")
         << "\n";
    cout << endl;

    // Deallocate list
    cout << "Deallocating list" << "\n";
    delete head;
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

