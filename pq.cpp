// pq.cpp
// Glenn G. Chappell
// 2023-11-12
//
// For CS 311 Fall 2023
// Priority Queues & custom comparisons

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <functional>
using std::greater;
#include <queue>
using std::priority_queue;


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


// printThingPQ
// Given a std::priority_queue holding values of type Thing, remove each
// item and print it to cout, as "NN,SS", preceded by 2 blanks,
// separated by 2 blanks, followed by a newline.
// The passed priority_queue is empty when the function returns.
// Requirements on Types:
//     PQ must be a std::priority_queue type.
//     The value type of PQ must be Thing.
template<typename PQ>
void printThingPQ(PQ & pq)
{
    cout << "  ";
    bool first = true;  // First item we're printing?
    while (!pq.empty())
    {
        if (first)
            first = false;
        else
            cout << "  ";
        auto t = pq.top();
        pq.pop();
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

    cout << "***** Demo of Priority Queues"
         << " with Various Comparisons *****\n\n";

    // Print initial data
    cout << "Item are inserted into each Priority Queue"
         << " in the following order:\n";
    cout << "  ";
    bool first = true;  // First item we're printing?
    for (const auto & t : master)
    {
        if (first)
            first = false;
        else
            cout << "  ";
        cout << t.nn << "," << t.ss;
    }
    cout << "\n\n";

    for (int i = 0; i < 72; ++i)
        cout << "-";
    cout << "\n\n";

    // *****************************
    // * Priority Queue #1: Normal *
    // *****************************

    priority_queue<Thing> pqnorm;
    for (const auto & t : master)
    {
        pqnorm.push(t);
    }
    cout << "Priority Queue #1: Normal\n";
    cout << "Items in order removed:\n";
    printThingPQ(pqnorm);
    cout << "\n";

    // **********************************************
    // * Priority Queue #2: Reversed (std::greater) *
    // **********************************************

    priority_queue<Thing, vector<Thing>, greater<Thing>> pqrev;
    for (const auto & t : master)
    {
        pqrev.push(t);
    }
    cout << "Priority Queue #2: Reversed (std::greater)\n";
    cout << "Items in order removed:\n";
    printThingPQ(pqrev);
    cout << "\n";

    // ***********************************************
    // * Priority Queue #3: Custom order (by string) *
    // ***********************************************

    // Lambda copied from comparison.cpp
    auto compSS =   // Compare ss fields of 2 Thing objects
        [](const Thing & x, const Thing & y)
        {
            return x.ss < y.ss;
        };

    priority_queue<Thing, vector<Thing>, decltype(compSS)>
        pqcust(compSS);
    for (const auto & t : master)
    {
        pqcust.push(t);
    }
    cout << "Priority Queue #3: Custom order (by string)\n";
    cout << "Items in order removed:\n";
    printThingPQ(pqcust);
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

