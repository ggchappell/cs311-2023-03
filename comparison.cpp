// comparison.cpp
// Glenn G. Chappell
// 2023-10-10
//
// For CS 311 Fall 2023
// Passing comparisons to STL sorts
// Also demonstrates use of lambdas

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <algorithm>
using std::sort;
#include <iterator>
using std::begin;
using std::end;
#include <functional>
using std::greater;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// struct Thing
// Holds an int nn and a string ss.
// operator< and operator> are defined; these compare nn.
struct Thing {
    int    nn;
    string ss;
};


// op<(Thing, Thing)
// Compares the nn fields of the given Thing objects.
bool operator<(const Thing & a, const Thing & b)
{
    return a.nn < b.nn;
}


// op>(Thing, Thing)
// Reversed operator<.
bool operator>(const Thing & a, const Thing & b)
{
    return b.nn < a.nn;
}


// printThingContainer
// Given a container that allows begin() and end() calls, holding values
// of type Thing, print all container items to cout, as "NN,SS",
// preceded by 2 blanks, separated by 2 blanks, followed by a newline.
// Requirements on Types:
//     For cont of type Container, begin(cont) and end(cont) must be
//      valid expressions returning forward iterators.
//     The value type of Container must be Thing.
// Pre:
//     [begin(c), end(c)) must be a valid range.
template<typename Container>
void printThingContainer(const Container & cc)
{
    cout << "  ";
    bool first = true;  // First item we're printing?
    for (const Thing & t : cc)
    {
        if (first)
            first = false;
        else
            cout << "  ";
        cout << t.nn << "," << t.ss;
    }
    cout << "\n";
}


// Main program
// Use STL sorting algorithms to sort a std::vector and a std::list in
// various ways, passing comparisons to some sorting calls. Print the
// results.
int main()
{
    // Create master dataset
    auto master = {
        Thing { 45, "Cat" },
        Thing { 72, "Dog" },
        Thing { 72, "Ape" },
        Thing { 25, "Bat" },
        Thing { 19, "Yak" },
        Thing { 67, "Owl" },
        Thing { 84, "Dog" },
        Thing { 31, "Emu" },
        Thing { 50, "Fox" },
    };
    // The above has type std::initializer_list<Thing>. If you need the
    // declaration of this template, include header <initializer_list>.

    // ***************************
    // * Dataset #1: std::vector *
    // ***************************

    // Set up dataset #1
    vector<Thing> data1(master);
    cout << "***** Sorting a std::vector with std::sort *****\n";
    cout << "\n";

    // Print unsorted data
    cout << "Initial data:\n";
    printThingContainer(data1);
    cout << "\n";

    // Sort in standard order
    sort(begin(data1), end(data1));
    cout << "Normal sort:\n";
    printThingContainer(data1);
    cout << "\n";

    // Sort in reverse order
    sort(begin(data1), end(data1), greater<Thing>());
    cout << "Descending sort (use std::greater):\n";
    printThingContainer(data1);
    cout << "\n";

    // Sort in custom order (by string field)
    auto compSS =   // Compare ss fields of 2 Thing objects
        [](const Thing & x, const Thing & y)
        {
            return x.ss < y.ss;
        };
    sort(begin(data1), end(data1), compSS);
    cout << "Custom order (by string; use lambda stored in var):\n";
    printThingContainer(data1);
    cout << "\n";

    cout << endl;

    // *************************
    // * Dataset #2: std::list *
    // *************************

    // Set up dataset #2
    list<Thing> data2(begin(master), end(master));
    cout << "***** Sorting a std::list "
         << "with member function sort *****\n";
    cout << "\n";

    // Print unsorted data
    cout << "Initial data:\n";
    printThingContainer(data2);
    cout << "\n";

    // Sort in standard order
    data2.sort();
    cout << "Normal sort:\n";
    printThingContainer(data2);
    cout << "\n";

    // Sort in reverse order
    data2.sort(greater<Thing>());
    cout << "Descending sort (use std::greater):\n";
    printThingContainer(data2);
    cout << "\n";

    // Sort in custom order (by string field, descending)
    data2.sort(  // Reverse compare ss fields of 2 Thing objects
        [](const Thing & x, const Thing & y)
        {
            return y.ss < x.ss;
        }
    );
    cout << "Custom order (descending by string; "
         << "use lambda created in func call):\n";
    printThingContainer(data2);
    cout << "\n";

    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

