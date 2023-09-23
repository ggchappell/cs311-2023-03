// fibo_recurse.cpp
// Glenn G. Chappell
// 2023-09-22
//
// For CS 311 Fall 2023
// Computing Fibonacci Numbers
// Fast recursive implementation

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstdint>
using std::uint_fast64_t;
#include <utility>
using std::pair;


// Type bignum
// Type of values used for large-ish integer computation.
// Should be an unsigned integer type.
using bignum = uint_fast64_t;  // fastest unsigned w/ >= 64 bits


// fibo_recurse
// Given nonnegative n, returns F(n-1), F(n) (the (n-1)th and nth
// Fibonacci numbers] as a pair.
// F(-1) = 1. F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Recursive helper function for fibo.
// Pre:
//     n >= 0.
//     F(n) is a valid bignum value.
// For bignum 64-bit unsigned, preconditions hold if 0 <= n <= 93.
// Does not throw.
pair<bignum, bignum> fibo_recurse(int n)
{
    // BASE CASE

    if (n == 0)
        return { 1, 0 };

    // RECURSIVE CASE

    auto [prev, curr] = fibo_recurse(n-1);
    return { curr, prev+curr };
}


// fibo
// Given nonnegative n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Uses recursive helper function fibo_recurse.
// Pre:
//     n >= 0.
//     F(n) is a valid bignum value.
// For bignum 64-bit unsigned, preconditions hold if 0 <= n <= 93.
// Does not throw.
bignum fibo(int n)
{
    auto [prev, curr] = fibo_recurse(n);
    return curr;
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

