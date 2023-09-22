#!/usr/bin/env python3
# fibo_fast.py
# Glenn G. Chappell
# 2023-09-21
#
# For CS 311 Fall 2023
"""Computing Fibonacci Numbers
Fast method"""


# Note: Lines beginning ">>>" are doctests. If a command-line interface
# is available, then these can be executed by doing the following:
#
#     python3 -m doctest fibo_fast.py
#
# When doing the above, only the results of failing tests are printed.
# Thus, no output is GOOD. To get the results of ALL tests, add "-v"
# (for "verbose"):
#
#     python3 -m doctest fibo_fast.py -v


import sys  # for .exit


def fibopair(n):
    """nonneg int n -> (F(n-1), F(n)); F(k) is kth Fibo #

    F(0) = 0. F(1) = 1. For k >= 2, F(k) = F(k-2) + F(k-1).

    Recursive. Values computed using fast method, involving a
    logarithmic number of multiplications.

    Pre:
        n >= 0.
    Post:
        Return is (F(n-1), F(n)).

    >>> fibopair(0)
    (1, 0)
    >>> fibopair(5)
    (3, 5)
    >>> fibopair(100)
    (218922995834555169026, 354224848179261915075)

    """
    assert isinstance(n, int)
    assert n >= 0

    # BASE CASE

    # For n = 0: (F(-1), F(0))
    if n == 0:
        return (1, 0)

    # RECURSIVE CASE

    # Get a = F(n//2-1), b = F(n//2).
    # NOTE: "//" is integer division.
    a, b = fibopair(n // 2)

    # We use the following two facts:
    #   1. F(2k-1) = F(k-1)F(k-1) + F(k)F(k).
    #   2. F(2k) = 2F(k-1)F(k) + F(k)F(k).
    # Set k = n//2. Note that a is F(n//2-1); b is F(n//2).
    s = a*a
    t = a*b*2
    u = b*b
    x = s+u
    y = t+u
    # Now x is F((n//2)*2-1); y is F((n//2)*2).

    if n % 2 == 0:
        return (x, y)    # x & y are what we want
    else:
        return (y, x+y)  # Advance the pair (x, y) by one


def fibo(n):
    """nonnegative int n -> F(n), the nth Fibonacci no.

    F(0) = 0. F(1) = 1. For k >= 2, F(k) = F(k-2) + F(k-1).

    Uses fibopair.

    Pre:
        n >= 0.
    Post:
        Return is F(n).

    >>> fibo(0)
    0
    >>> fibo(5)
    5
    >>> fibo(300)
    222232244629420445529739893461909967206666939096499764990979600

    """
    assert isinstance(n, int)
    assert n >= 0
    a, b = fibopair(n)
    return b


def print_results(n):
    """Compute Fibonacci number F(n); print in pretty form."""

    print(f"F({n}) = {fibo(n)}")


# main
# input n, print F(n) in nice format, repeat until blank line input.
def main():
    while True:
        print()
        print("Given integer n, I will compute Fibonacci number F(n).")
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


# If this module is executed as a program (instead of being imported):
# Call function main and exit with its return value.
if __name__ == "__main__":
    sys.exit(main())

