// rpneval_main.cpp
// Glenn G. Chappell
// 2023-10-31
//
// For CS 311 Fall 2023
// Entering & evaluating Reverse Polish Notation
// Requires rpneval.hpp

#include "rpneval.hpp"     // For rpnEval
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
using std::getline;
#include <stack>
using std::stack;
#include <cctype>
using std::isspace;
#include <utility>
using std::pair;
#include <stdexcept>
using std::domain_error;
using std::out_of_range;
using std::overflow_error;
using std::invalid_argument;


// readNonEmptyLine
// Print prompt and attempt to read a line from cin. If the line is
// empty, or it consists entirely of space characters, then try again.
// Returns { false, "" } on input error EOF; otherwise returns
// { true, line }.
// May throw std::bad_alloc on out of memory.
// Basic Guarantee
pair<bool, string> readNonemptyLine(const string & prompt)
{
    string line;  // Holds input line
    while (true)
    {
        // Input a line
        cout << prompt;
        cout.flush();
        getline(cin, line);

        // Check result
        if (!cin)
            return { false, "" };
        for (char c : line)
        {
            if (!isspace(c))
                return { true, line };
        }

        // Here, we have no error on cin, and our line consists entirely
        // of zero or more space characters. We try again.
    }
}


// printStack
// Given a stack<int>, prints its top item with an explanatory message,
// or prints a message indicating the Stack is empty. Output ends with
// a newline.
// No-Throw Guarantee
void printStack(const stack<int> & s)
{
    if (s.empty())
        cout << "<Empty Stack>\n";
    else
        cout << "Top of Stack: " << s.top() << "\n";
}


// Main program
// Repeatedly inputs space-separated token from standard input,
// operates on Stack (RPN operations) and prints top of Stack.
// May throw std::bad_alloc on out of memory.
int main()
{
    const string prompt = "Commands (q to quit): ";
    const string quitmsg = "*** Quitting";
    stack<int> s;  // Stack used for RPN evaluation

    // Print introductory message
    cout << "Reverse Polish Notation Expression Evaluation\n\n";

    // Print top of Stack (should be message indicating empty Stack)
    printStack(s);

    while (true)
    {
        cout << endl;

        // Get line from stdin
        auto [valid, line] = readNonemptyLine(prompt);
        cout << "\n";

        // Quit on input error
        if (!valid)
        {
            cout << "\n" << quitmsg << "\n\n";
            return 0;
        }

        // Get space-deliminted commands from line
        istringstream lineStream(line);
        string token;
        while (lineStream >> token)  // Get space-deliminated command
                                     //  ("token") from line
        {
            // Quit?
            if (token == "q" || token == "Q")
            {
                cout << quitmsg << "\n" << endl;
                return 0;
            }

            // Do RPN processing
            try
            {
                rpnEval(s, token);
            }
            catch (domain_error & e)
            {
                cout << "*** ERROR - " << e.what() << "\n";
            }
            catch (out_of_range & e)
            {
                cout << "*** ERROR - " << e.what() << "\n";
            }
            catch (overflow_error & e)
            {
                cout << "*** ERROR - " << e.what() << "\n";
            }
            catch (invalid_argument & e)
            {
                cout << "*** ERROR - " << e.what() << "\n";
            }
            // std::bad_alloc exceptions will escape this function

            // Print top of Stack
            printStack(s);
        }
    }
}

