# Matrix ADT

## Introduction

This program implements an Abstract Data Type (ADT) for matrices. The Matrix ADT provides various operations for creating, manipulating, and performing calculations on matrices. It uses a sparse representation to efficiently handle matrices with a large number of zero elements.


## Files
The program consists of the following files:

- `List.c`: This file contains the implementation of the doubly linked list ADT.
- `List.h`: This is the header file that declares the functions and structures used in `List.c`.
- `Matrix.c`: This file contains the implementation of the Matrix ADT.
- `Matrix.h`: This is the header file that declares the functions and structures used in `Matrix.c`.

## Data Structures:

- `EntryObj` is a struct representing an entry in the matrix. It contains a value (double) and a position (integer).
- `MatrixObj` is a struct representing the matrix. It contains an array of linked lists (rows), the size of the matrix, and the number of non-zero entries (non_zero).

## Constructors-Destructors:

- `newEntry(double val, int pos)` creates a new Entry object with the given value and position.
- `newMatrix(int n)` creates a new Matrix object with size n. It initializes the rows array, sets the size, and non-zero entries to 0.
- `freeEntry(Entry* pE)` frees the memory allocated for an Entry object.
- `freeMatrix(Matrix* pM)` frees the memory allocated for a Matrix object. It also frees the memory for each Entry object in the matrix.

## Access functions:

- `size(Matrix M)` returns the size of the matrix.
- `NNZ(Matrix M)` returns the number of non-zero entries in the matrix.
- `equals(Matrix A, Matrix B)` checks if two matrices A and B are equal.

## Manipulation procedures:

- `makeZero(Matrix M)` sets all entries of the matrix to zero.
- `shiftCursor(List L, int i)` moves the cursor in a list to a specified position i.
- `changeEntry(Matrix M, int i, int j, double x)` changes the value of the entry at row i and column j to x. If x is zero, the entry is removed.
- `copy(Matrix A)` creates a new matrix that is a copy of matrix A.
- `transpose(Matrix A)` creates a new matrix that is the transpose of matrix A.
- `scalarMult(double x, Matrix A)` multiplies each entry of matrix A by scalar x and returns a new matrix.
- `sum(Matrix A, Matrix B)` computes the sum of matrices A and B and returns a new matrix.
- `diff(Matrix A, Matrix B)` computes the difference between matrices A and B and returns a new matrix.
- `vectorDot(List P, List Q)` computes the dot product of two matrix rows represented by lists P and Q.
- `product(Matrix A, Matrix B)` computes the product of matrices A and B and returns a new matrix.
- `printMatrix(FILE* out, Matrix M)` prints the matrix M in a specified format to the specified file.