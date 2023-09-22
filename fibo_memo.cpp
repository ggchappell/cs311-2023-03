// fibo_memo.cpp
// Glenn G. Chappell
// 2023-09-21
//
// For CS 311 Fall 2023
// Computing Fibonacci Numbers
// Recursive top-down dynamic programming implementation
// A.k.a. memoizing

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstdint>
using std::uint_fast64_t;
#include <vector>
using std::vector;


// Type bignum
// Type of values used for large-ish integer computation.
// Should be an unsigned integer type.
using bignum = uint_fast64_t;  // fastest unsigned w/ >= 64 bits


// Marker for unknown values in table. Must not be a Fibonacci number.
const bignum UNKNOWN = 9999999999999999999ULL;


// fibo_recurse
// Given nonnegative n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Recursive helper function for fibo.
// Pre:
//     n >= 0.
//     F(n) is a valid bignum value.
// For bignum 64-bit unsigned, above preconditions hold if 0 <= n <= 93.
//     n < fibotable.size().
//     For each i, fibotable[i] is either UNKNOWN or F(i).
// May throw std::bad_alloc.
bignum fibo_recurse(vector<bignum> & fibotable,
                    int n)
{
    // Check if we have already computed F(n); if so, do not recompute
    if (vector<bignum>::size_type(n) < fibotable.size()
          && fibotable[n] != UNKNOWN)
        return fibotable[n];

    // Resize table large enough to hold F(n); new values are UNKNOWN
    if (fibotable.size() <= vector<bignum>::size_type(n))
        fibotable.resize(n+1, UNKNOWN);

    bignum result;  // For our final result

    if (n <= 1)  // BASE CASE
    {
        result = bignum(n);
    }
    else         // RECURSIVE CASE
    {
        result =
            fibo_recurse(fibotable, n-2) + fibo_recurse(fibotable, n-1);
    }

    // Save result in table and return it
    fibotable[n] = result;
    return result;
}


// fibo
// Given nonnegative n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Uses recursive helper function fibo_recurse.
// Pre:
//     n >= 0.
//     F(n) is a valid bignum value.
// For bignum 64-bit unsigned, preconditions hold if 0 <= n <= 93.
// May throw std::bad_alloc.
bignum fibo(int n)
{
    vector<bignum> fibotable;  // For saving values (memoizing)
    return fibo_recurse(fibotable, n);
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

