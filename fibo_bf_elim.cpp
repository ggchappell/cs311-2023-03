// fibo_bf_elim.cpp
// Glenn G. Chappell
// 2023-11-01
//
// For CS 311 Fall 2023
// Computing Fibonacci Numbers
// Recursion eliminated, brute-force method
//
// This program is based on fibo_first.cpp.
// Recursion has been eliminated using the brute-force technique covered
// in class, applying as little intelligence as possible.

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstdint>
using std::uint_fast64_t;
#include <stack>
using std::stack;


// Type bignum
// Type of values used for large-ish integer computation.
// Should be an unsigned integer type.
using bignum = uint_fast64_t;  // fastest unsigned w/ >= 64 bits


// Original function fibo, from fibo_first.cpp:
//
// bignum fibo(int n)
// {
//     // BASE CASE
//
//     if (n <= 1)
//         return bignum(n);
//
//     // RECURSIVE CASE
//
//     // Invariant: n >= 2
//     return fibo(n-2) + fibo(n-1);
// }
//
// Modified version used as the basis of this code:
//
// bignum fibo(int n)
// {
//     bignum r1, r2;
//
//     // BASE CASE
//     if (n <= 1)
//         return bignum(n);
//
//     // RECURSIVE CASE
//     r1 = fibo(n-2);  // Recursive call #1
//     r2 = fibo(n-1);  // Recursive call #2
//     return r1 + r2;  // Return the result
// }


// struct FiboStackFrame
// "Stack frame" - holds local values for function fibo.
// In a structure so that they can be saved on a stack.
struct FiboStackFrame {
    int    n;            // Parameter
    bignum r1;           // Result of recursive call #1
    bignum r2;           // Result of recursive call #2
    bignum returnValue;  // Value to return
    int    returnAddr;   // Return address:
                         //   0: outside world (return from function)
                         //   1: recursive call #1 (goto return_here_1)
                         //   2: recursive call #2 (goto return_here_2)
};


// fibo
// Given nonnegative n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Pre:
//     n >= 0.
//     F(n) is a valid bignum value.
// For bignum 64-bit unsigned, preconditions hold if 0 <= n <= 93.
// May throw std:bad_alloc on out-of-memory.
// Strong Guarantee
bignum fibo(int n)
{
    // ***************************************
    // ORIGINAL CODE:
    // bignum fibo(int n)
    // {
    //     bignum r1, r2;
    // ***************************************

    // Local variables
    stack<FiboStackFrame> cs;   // Call stack for recursion elimination
                                // Top of stack holds current local vars
                                // + spot for return value, return addr
    int tmpi;                   // Temp - holds int during stack ops
    bignum tmpb;                // Temp - holds bignum during stack ops

    // Set up stack frame
    cs.push(FiboStackFrame());  // Make new stack frame
    cs.top().n = n;             // Out parameter
    cs.top().returnAddr = 0;    // Our return addr: outside world

    // ***************************************
    // BEGIN LOOP
    // while (true) loop used for recursion
    // elimination
    // ***************************************
    while (true)
    {

        // ***************************************
        // ORIGINAL CODE:
        // // BASE CASE
        // if (n <= 1)
        //     return bignum(n);
        // ***************************************
        if (cs.top().n <= 1)
        {
            // Do "return bignum(n);"
            cs.top().returnValue = bignum(cs.top().n);

            if (cs.top().returnAddr == 1)       // Back to call #1
                goto return_here_1;
            else if (cs.top().returnAddr == 2)  // Back to call #2
                goto return_here_2;
            else                                // Back to outside world
            {
                tmpb = cs.top().returnValue;
                cs.pop();
                return tmpb;
            }
        }

        // ***************************************
        // ORIGINAL CODE:
        // // RECURSIVE CASE
        // r1 = fibo(n-2);  // Recursive call #1
        // ***************************************
        tmpi = cs.top().n - 2;
        cs.push(FiboStackFrame());  // Make new stack frame
        cs.top().n = tmpi;          // Set parameter
        cs.top().returnAddr = 1;    // Return addr: recursive call #1
        continue;                   // Do "recursive call"
return_here_1:                      // Place to return to
        tmpb = cs.top().returnValue;
        cs.pop();
        cs.top().r1 = tmpb;         // Returned value -> r1

        // ***************************************
        // ORIGINAL CODE:
        // r2 = fibo(n-1);  // Recursive call #2
        // ***************************************
        tmpi = cs.top().n - 1;
        cs.push(FiboStackFrame());  // Make new stack frame
        cs.top().n = tmpi;          // Set parameter
        cs.top().returnAddr = 2;    // Return addr: recursive call #2
        continue;                   // Do "recursive call"
return_here_2:                      // Place to return to
        tmpb = cs.top().returnValue;
        cs.pop();
        cs.top().r2 = tmpb;         // Returned value -> r2

        // ***************************************
        // ORIGINAL CODE:
        // return r1 + r2;  // Return the result
        // ***************************************
        cs.top().returnValue = cs.top().r1 + cs.top().r2;

        if (cs.top().returnAddr == 1)       // Back to call #1
            goto return_here_1;
        else if (cs.top().returnAddr == 2)  // Back to call #2
            goto return_here_2;
        else                                // Back to outside world
        {
            tmpb = cs.top().returnValue;
            cs.pop();
            return tmpb;
        }

    // ***************************************
    // END LOOP
    // while (true) loop used for recursion
    // elimination
    // ***************************************
    }
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Prints F(i) for i = 0, 1, 2, ... through the greatest Fibonacci
// number that a 64-bit unsigned integer can represent.
// Uses fibo.
int main()
{
    const int MAXINDEX = 93;  // Greatest i for which we compute F(i)

    // Print Fibonacci numbers
    cout << "Fibonacci Numbers" << "\n";
    cout << "\n";
    for (int i = 0; i <= MAXINDEX; ++i)
    {
        // Compute Fibonacci number
        auto ff = fibo(i);

        // Print it nicely
        cout << "F(" << i << ")";
        if (i < 10)
            cout << " ";  // For aligned output
        cout << " = " << ff << "\n";
    }
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

