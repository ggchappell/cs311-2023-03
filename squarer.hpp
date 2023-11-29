// squarer.hpp
// Glenn G. Chappell
// 2023-11-28
//
// For CS 311 Fall 2023
// Header for class Squarer
// There is no associated source file.
// For Assignment 8, Exercise B

#ifndef FILE_SQUARER_HPP_INCLUDED
#define FILE_SQUARER_HPP_INCLUDED


// class Squarer
// Class for function objects that return squares of numbers.
// Usage:
//     Squarer c;
//     cout << c(3);    // Prints "27"
//     cout << c(1.5);  // Prints "3.375"
// Class invariants: None.
class Squarer {
public:
    // operator()
    // Takes a value k and returns its square.
    // Requirements on types:
    //     Num must have binary operator* and copy ctor.
    // Pre:
    //     The square of k must be representable as a value of the same
    //      type as k.
    // Throws what & when Num operations throw.
    // Strong Guarantee
    // Exception Neutral
    template<typename Num>
    Num operator()(const Num & k) const
    {
        return k * k;
    }

    // We use automatically generated default ctor & Big 5.
    Squarer() = default;
    ~Squarer() = default;
    Squarer(const Squarer &) = default;
    Squarer(Squarer &&) = default;
    Squarer & operator=(const Squarer &) = default;
    Squarer & operator=(Squarer &&) = default;
};  // End class Squarer


#endif //#ifndef FILE_SQUARER_HPP_INCLUDED

