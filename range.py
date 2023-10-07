#!/usr/bin/env python3
# range.py
# Glenn G. Chappell
# Started: 2023-09-17
# Updated: 2023-10-07
#
# For CS 311 Fall 2023
"""Example of a range specification in Python."""


import sys  # for .exit


# main
def main():
    """Demonstrate Python's range functionality.

    """
    print("Printing values given by \"range(2, 7)\":")
    for i in range(2, 7):
        print(" ", i)
    print()

    print("Python follows the same first/just-past-last convention for")
    print("specifying ranges as the C++ STL.")
    print()

    return 0  # Success


# If this module is executed as a program (instead of being imported):
# Call function main and exit with its return value.
if __name__ == "__main__":
    sys.exit(main())

