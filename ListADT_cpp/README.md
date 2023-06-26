# List ADT - C++

## Introduction

The List ADT is an abstract data type implemented in C++ that represents a linear collection of elements. It provides various operations to manipulate and access the elements in the list. This program consists of the implementation of the List ADT in the List.cpp file, along with the corresponding header file List.h. Additionally, there is a program called Shuffle.cpp that performs shuffling operations on a list and counts the number of shuffles required to bring the list back to its original order.

## Files

The program consists of the following files:

- `List.cpp`: This file contains the implementation of the list ADT.
- `List.h`: This is the header file that declares the functions and structures used in `List.cpp`.
- `Shuffle.cpp`: a program that reads a single command line argument, which will be a positive integer specifying the maximum number of cards in a deck. For each n in the range 1 up to this maximum, the program performs shuffles until the list (0, 1, 2, … , n − 1) is brought back to its original order, counting the number of shuffles as it goes. It prints a table to standard output giving this count, for each value of n.

## Abstract Data Type (ADT) - List

The List ADT provides the following functions:

- `List()`: Constructor that creates a new List in an empty state.
- `List(const List& L)`: Copy constructor that creates a new List by copying an existing List.
- `~List()`: Destructor that clears the List and frees any dynamically allocated memory.
- `length() const`: Returns the length of the List.
- `front() const`: Returns the front element in the List.
- `back() const`: Returns the back element in the List.
- `position() const`: Returns the position of the cursor in the List.
- `peekNext() const`: Returns the element after the cursor.
- `peekPrev() const`: Returns the element before the cursor.
- `clear()`: Deletes all elements in the List, setting it to the empty state.
- `moveFront()`: Moves the cursor to the front of the List.
- `moveBack()`: Moves the cursor to the back of the List.
- `moveNext()`: Advances the cursor to the next higher position and returns the List element passed over.
- `movePrev()`: Advances the cursor to the next lower position and returns the List element passed over.
- `insertAfter(ListElement x)`: Inserts an element after the cursor.
- `insertBefore(ListElement x)`: Inserts an element before the cursor.
- `setAfter(ListElement x)`: Overwrites the element after the cursor with a new value.
- `setBefore(ListElement x)`: Overwrites the element before the cursor with a new value.
- `eraseAfter()`: Deletes the element after the cursor.
- `eraseBefore()`: Deletes the element before the cursor.
- `findNext(ListElement x)`: Performs a linear search from the cursor position to find the first occurrence of an element x, updating the cursor accordingly.
- `findPrev(ListElement x)`: Performs a linear search from the cursor position to find the first occurrence of an element x in reverse order, updating the cursor accordingly.
- `cleanup()`: Removes any repeated elements in the List, leaving only unique elements.
- `concat(const List& L) const`: Returns a new List that concatenates the elements of the current List and another List.
- `to_string() const`: Returns a string representation of the List.
- `equals(const List& other) const`: Compares the List with another List to check if they contain the same elements in the same

### Operator overloads

- `operator<<(std::ostream& stream, const List& L)`: Inserts the string representation of the List L into the output stream stream.
- `operator==(const List& A, const List& B)`: Compares two Lists A and B for equality. Returns true if they have the same elements in the