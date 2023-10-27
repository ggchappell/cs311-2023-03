// use_list2.cpp
// Glenn G. Chappell
// 2023-10-26
//
// For CS 311 Fall 2023
// Singly Linked List example using smart pointers: create & find size
// Based on use_list.cpp

#include "llnode2.hpp"  // For struct LLNode2
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstddef>
using std::size_t;
#include <memory>
using std::unique_ptr;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Creates a Linked List and finds its size.
int main()
{
    const size_t THESIZE = 507;  // Size of list to create

    // Create empty list
    cout << "Creating empty Linked List" << "\n";
    unique_ptr<LLNode2<int>> head;

    // Add nodes to list
    cout << "Adding " << THESIZE << " nodes to Linked List" << "\n";
    for (size_t i = 0; i < THESIZE ; ++i)
    {
        push_front(head, int(THESIZE-i));
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
    // *** NOTHING TO DO HERE! ***

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

