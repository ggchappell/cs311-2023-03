// msarray.hpp  HAND-OFF
// VERSION 6
// Glenn G. Chappell
// Started: 2023-10-17
// Updated: 2023-10-25
//
// For CS 311 Fall 2023
// Header for class MSArray
// Marvelously smart array of int
// Preliminary to Assignment 5

// History:
// - v1:
//   - Bare-bones only, does not compile. Header & source files,
//     #ifndef, #include, empty class definition.
// - v2:
//   - Add member types value_type, size_type, iterator, const_iterator.
//   - Add dummy versions (at least) of all member functions, including
//     dummy return statements for non-void functions. Package compiles.
//   - Add data members.
//   - Add class invariants.
//   - Write (untested versions of) the following member functions:
//     default ctor, ctor from size (these two are single func), dctor,
//     op[], size, empty, begin, end, push_back, pop_back.
// - v3:
//   - Document exception-safety guarantees for most functions.
//   - Write copy ctor.
// - v4:
//   - Revise class invariants to allow for _data being nullptr if _size
//     is zero.
//   - Revise ctor from size, copy ctor accordingly.
//   - Write move ctor.
//   - Mark various functions as noexcept.
// - v5:
//   - Move func defs to source file: copy & move ops, resize, insert,
//     erase, swap.
// - v6:
//   - Add _capacity data member.
//   - Revise class invariants & ctors accordingly.
//   - Add constant DEFAULT_CAP and use it in setting the capacity in
//     default ctor/ctor from size.

#ifndef FILE_MSARRAY_HPP_INCLUDED
#define FILE_MSARRAY_HPP_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max


// *********************************************************************
// class MSArray - Class definition
// *********************************************************************


// class MSArray
// Marvelously Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of value_type, allocated with new [],
//      owned by *this, holding _capacity value_type values -- UNLESS
//      _capacity == 0, in which case _data may be nullptr.
class MSArray {

// ***** MSArray: types *****
public:

    // value_type: type of data items
    using value_type = int;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** MSArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 42 };

// ***** MSArray: ctors, op=, dctor *****
public:

    // Default ctor & ctor from size
    // Strong Guarantee
    explicit MSArray(size_type thesize=0)
        :_capacity(std::max(thesize, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(thesize),
         _data(_capacity == 0 ? nullptr
                              : new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    MSArray(const MSArray & other);

    // Move ctor
    // No-Throw Guarantee
    MSArray(MSArray && other) noexcept;

    // Copy assignment operator
    // ??? Guarantee
    MSArray & operator=(const MSArray & other);

    // Move assignment operator
    // No-Throw Guarantee
    MSArray & operator=(MSArray && other) noexcept;

    // Dctor
    // No-Throw Guarantee
    ~MSArray()
    {
        delete [] _data;
    }

// ***** MSArray: general public operators *****
public:

    // operator[] - non-const & const
    // Pre:
    //     ???
    // No-Throw Guarantee
    value_type & operator[](size_type index)
    {
        return _data[index];
    }
    const value_type & operator[](size_type index) const
    {
        return _data[index];
    }

// ***** MSArray: general public functions *****
public:

    // size
    // No-Throw Guarantee
    size_type size() const noexcept
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    iterator begin() noexcept
    {
        return _data;
    }
    const_iterator begin() const noexcept
    {
        return _data;
    }

    // end - non-const & const
    // No-Throw Guarantee
    iterator end() noexcept
    {
        return begin() + size();
    }
    const_iterator end() const noexcept
    {
        return begin() + size();
    }

    // resize
    // ??? Guarantee
    void resize(size_type newsize);

    // insert
    // Pre:
    //     ???
    // ??? Guarantee
    iterator insert(iterator pos,
                    value_type item);
        // Above, passing by value is appropriate, since our value type
        // is int. However, if the value type is changed, then a
        // different parameter-passing method may need to be used.

    // erase
    // Pre:
    //     ???
    // ??? Guarantee
    iterator erase(iterator pos);

    // push_back
    // ??? Guarantee
    void push_back(value_type item)
        // Above, passing by value is appropriate, since our value type
        // is int. However, if the value type is changed, then a
        // different parameter-passing method may need to be used.
    {
        insert(end(), item);
    }

    // pop_back
    // Pre:
    //     ???
    // ??? Guarantee
    void pop_back()
    {
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    void swap(MSArray & other) noexcept;

// ***** MSArray: data members *****
private:

    // Below, _capacity must be declared before _data
    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

};  // End class MSArray


#endif  //#ifndef FILE_MSARRAY_HPP_INCLUDED

