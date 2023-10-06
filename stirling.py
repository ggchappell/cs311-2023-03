#!/usr/bin/env python3
# stirling.py
# Glenn G. Chappell
# 2023-10-06
#
# For CS 311 Fall 2023
"""Compare factorial & Stirling's approximation."""


# Lines beginning ">>>" are doctests. If a command-line interface is
# available, then these can be executed by doing the following:
#
#     python3 -m doctest stirling.py
#
# When doing the above, only the results of failing tests are printed.
# Thus, no output is GOOD. To get the results of ALL tests, add "-v"
# (for "verbose"):
#
#     python3 -m doctest stirling.py -v


import math  # For .exp, .sqrt, .pi
import sys   # for .exit


def factorial(n):
    """nonneg int n -> n!

    >>> factorial(0)
    1
    >>> factorial(3)
    6
    >>> factorial(12)
    479001600

    Pre:
        n is integer.
        n >= 0.

    """
    assert isinstance(n, int)
    assert n >= 0

    result = 1
    for i in range(1, 1+n):
        result *= i
    return result


def stirling(n):
    """nonneg number n -> Stirling's approximation of n!

    >>> f"{stirling(6):.3f}"
    '710.078'
    >>> f"{stirling(20):.3f}"
    '2422786846761133568.000'

    Pre:
        n is integer or real number.
        n >= 0.

    """
    assert isinstance(n, (int, float))
    assert n >= 0

    return n**n / math.exp(n) * math.sqrt(2 * math.pi * n)


def print_results(n):
    """Compute n! & Stirling's approximation; print in pretty form."""

    print(f"n = {n}")
    print("")
    try:
        f = factorial(n)
        s = stirling(n)
    except:
        print("*** Factorial/Stirling's computation failed ***")
        print("")
        print("(Exactly when this happens is system-dependent. On my")
        print("machine, the computation exceeds the limits of Python's")
        print("floating-point math when n >= 144. -GGC-)")
    else:
        print(f"Factorial:  {f}")
        print(f"Stirling's: {s:.2f}")


# main
def main():
    while True:
        print()
        print("Given a nonnegative integer n, ", sep="")
        print("I compute its factorial and Stirling's approximation.")
        print()
        try:
            line = input("Type n [blank line to exit]: ")
            if line == "": break
            n = int(line)
            if n < 0: raise Exception()
        except:
            print()
            print("Please type a nonnegative integer")
        else:
            print()
            print_results(n)
        print()
        print("-" * 60)
    print()

    return 0  # Success


# Main program
# If this module is executed as a program (instead of being imported):
# input n, print F(n) in nice format, repeat until blank line input.
if __name__ == "__main__":
    sys.exit(main())

