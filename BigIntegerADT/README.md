# BigInteger ADT

## Introduction

The BigInteger ADT (Abstract Data Type) provides a way to represent and manipulate arbitrarily large integers in computer programs. It is designed to handle numbers that are too large to be stored in standard integer data types.

## Files
The program consists of the following files:

- `List.cpp`: This file contains the implementation of the list ADT.
- `List.h`: This is the header file that declares the functions and structures used in `List.cpp`.
- `BigInteger.h`: Header file containing the declaration of the BigInteger class and its member functions.
- `BigInteger.cpp`: Implementation file containing the definitions of the BigInteger class member functions.


## Data Structures:

The BigInteger ADT utilizes the following data structures:

- Dynamic array: It is used to store the individual digits of the large integer. Each element of the array represents a digit of the number.

## Constructors-Destructors:

- `BigInteger()`: Default constructor that creates an empty BigInteger object.
- `~BigInteger()`: Destructor that deallocates the memory used by the BigInteger object.
- `BigInteger(std::string s)`: Creates a new BigInteger object from the string s. The string should be a non-empty string consisting of base 10 digits {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.

## Access functions:

- `int sign() const`: Returns -1, 1, or 0 according to whether the BigInteger is negative, positive, or zero, respectively.
- `int compare(const BigInteger& other) const`: Returns -1, 1, or 0 according to whether the BigInteger is less than, greater than, or equal to the other BigInteger, respectively.

## Manipulation procedures:

- `void makeZero()`: Resets the BigInteger to the zero state.
- `void negate()`: Reverses the sign of the BigInteger. If the BigInteger is zero, it does nothing.

## BigInteger Arithmetic operations

- `BigInteger add(const BigInteger& N) const`: Returns a new BigInteger object representing the sum of the current BigInteger and the N BigInteger.
- `BigInteger sub(const BigInteger& N) const`: Returns a new BigInteger object representing the difference between the current BigInteger and the N BigInteger.
- `BigInteger mult(const BigInteger& N) const`: Returns a new BigInteger object representing the product of the current BigInteger and the N BigInteger

## Other Functions

- `std::string to_string()`: Returns a string representation of the BigInteger consisting of its base 10 digits. If the BigInteger is negative, the returned string will begin with a negative sign '-'. If the BigInteger is zero, the returned string will consist of the character '0' only.
