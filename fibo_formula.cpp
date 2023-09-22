// fibo_formula.cpp
// Glenn G. Chappell
// 2023-09-21
//
// For CS 311 Fall 2023
// Computing Fibonacci Numbers
// Formula implementation

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstdint>
using std::uint_fast64_t;
#include <cmath>
using std::sqrt;
using std::pow;


// Type bignum
// Type of values used for large-ish integer computation.
// Should be an unsigned integer type.
using bignum = uint_fast64_t;  // fastest unsigned w/ >= 64 bits


// fibo
// Given nonnegative n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Pre:
//     n >= 0.
//     F(n) is a valid bignum value.
//     F(n) can be computed accurately using phi^n/sqrt(5)
//      with the (long double) type.
// For bignum 64-bit unsigned, 1st 2 preconditions hold if 0 <= n <= 93.
// If (long double) is 96-bit IEEE floating-point, then 3rd precondition
// holds if 0 <= n <= 84.
// Does not throw.
bignum fibo(int n)
{
    // Below "L" marks a long double floating-point literal
    const long double sqrt5 = sqrt(5.0L);
    const long double phi = (1.0L + sqrt5) / 2.0L;  // "Golden ratio"
    long double nearly = pow(phi, n) / sqrt5;       // phi^n/sqrt(5)

    // Our Fibonacci number is the nearest integer
    return bignum(nearly + 0.5L);
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
// number that our formula computes correctly, assuming 96-bit IEEE
// floating-point.
// Uses fibo.
int main()
{
    const int MAXINDEX = 84;  // Greatest i for which we compute F(i)
    // We only go to 84, instead of 93, due to the limitations of
    // floating-point on some machines.

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

