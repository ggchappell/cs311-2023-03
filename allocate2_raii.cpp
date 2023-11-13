// allocate2_raii.cpp
// Glenn G. Chappell
// 2023-09-14
//
// For CS 311 Fall 2023
// Out-of-memory handling using exceptions, with RAII classes

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <new>
using std::bad_alloc;
#include <memory>
using std::unique_ptr;
using std::make_unique;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// class Named
// Given name in ctor. construction. On both construction and
// destruction, prints this name along with a message.
// Invariants:
//     _name is the parameter passed to the ctor.
class Named {

// ***** Named: ctors, dctor, op= *****
public:

    // Ctor from string
    // Store given string as name. Print name with a message to cout.
    // May throw std::bad_alloc.
    Named(const string & name)
        :_name(name)
    {
        // UNCOMMENT ONE OR MORE LINES BELOW TO SEE WHAT WOULD HAPPEN IF
        // ALLOCATION FAILED AND "new" THREW AN EXCEPTION.

        if (false
            // || _name == "Object A"
            // || _name == "Object B"
            )
        {
            cout << _name << " CREATION FAILED; THROWING\n";
            throw bad_alloc();
        }

        // ******************************************************
        // * In practice, we NEVER do a throw like that above;  *
        // * "new" does it. We are signalling a fake error, to  *
        // * see what would happen if "new" did actually throw. *
        // ******************************************************

        cout << _name << " created\n";
    }

    // Dctor
    // Print name with a message to cout.
    ~Named()
    {
        cout << _name << " destroyed\n";
    }

    // No other Big Five functions
    Named(const Named & other) = delete;
    Named(Named && other) = delete;
    Named & operator=(const Named & rhs) = delete;
    Named & operator=(Named && rhs) = delete;

// ***** Named: data members *****
private:

    string _name;  // Object's name; print on destruction

};


// allocate2
// Attempt to allocate two Named objects, with names "Object A" and
// "Object B". Return unique_ptrs to these in nptra, nptrb. Throws
// exception thrown by "new" (derived class of std::bad_alloc) if either
// allocation is unsuccessful.
// Pre: None.
// Post:
//     nptra points to object with name "Object A".
//     nptrb points to object with name "Object B".
// May throw std::bad_alloc.
void allocate2(unique_ptr<Named> & nptra,
               unique_ptr<Named> & nptrb)
{
    nptra = make_unique<Named>("Object A");
    nptrb = make_unique<Named>("Object B");
}


// Main program
// Demonstrates calling allocate2 with proper catching.
int main()
{
    // Call allocate2
    unique_ptr<Named> npa;
    unique_ptr<Named> npb;
    try
    {
        allocate2(npa, npb);
        cout << "Call to \"allocate2\" successful\n";
    }
    catch (bad_alloc & e)
    {
        cout << "Call to \"allocate2\" NOT successful\n";
        cout << "  exception caught [what = '" << e.what() << "']\n";
    }

    // Deallocation is automatic; nothing more for us to do
    // (Isn't RAII great?)
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

