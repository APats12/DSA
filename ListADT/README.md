# Doubly Linked List ADT

## Introduction
This program implements a doubly linked list abstract data type (ADT) named "List". The list supports various operations such as insertion, deletion, traversal, and more. The implementation provides functions to manipulate and access the elements of the list.

## Important Files
The program consists of the following files:

- `List.c`: This file contains the implementation of the doubly linked list ADT.
- `List.h`: This is the header file that declares the functions and structures used in `List.c`.

## Abstract Data Type (ADT) - List
The List ADT provides the following functions:

- `List newList(void)`: Creates a new empty List and returns a reference to it.
- `void freeList(List* pL)`: Frees the memory associated with the List and sets the reference to NULL.
- `int length(List L)`: Returns the number of elements in the List.
- `int index(List L)`: Returns the index of the cursor element in the List.
- `int front(List L)`: Returns the value of the front element in the List.
- `int back(List L)`: Returns the value of the back element in the List.
- `int get(List L)`: Returns the value of the cursor element in the List.
- `bool equals(List A, List B)`: Checks if two Lists are equal by comparing their elements.
- `void clear(List L)`: Clears all elements from the List, making it empty.
- `void set(List L, int x)`: Overwrites the cursor element with the given value.
- `void moveFront(List L)`: Moves the cursor to the front of the List.
- `void moveBack(List L)`: Moves the cursor to the back of the List.
- `void movePrev(List L)`: Moves the cursor one step toward the front of the List.
- `void moveNext(List L)`: Moves the cursor one step toward the back of the List.
- `void prepend(List L, int x)`: Inserts a new element at the front of the List.
- `void append(List L, int x)`: Inserts a new element at the back of the List.
- `void insertBefore(List L, int x)`: Inserts a new element before the cursor element in the List.
- `void insertAfter(List L, int x)`: Inserts a new element after the cursor element in the List.
- `void deleteFront(List L)`: Deletes the front element of the List.
- `void deleteBack(List L)`: Deletes the back element of the List.
- `void delete(List L)`: Deletes the cursor element from the List.
- `void printList(FILE* out, List L)`: Prints the elements of the List to the specified file.
- `List copyList(List L)`: Creates a new List that is a deep copy of the given List.
