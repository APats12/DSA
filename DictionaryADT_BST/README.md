# Dictionary ADT

## Introduction

This is the implementation file for the Dictionary class. The Dictionary class represents a dictionary data structure that stores key-value pairs. It uses a binary search tree to efficiently store and retrieve the pairs.

## Node Structure

The Node structure represents a node in the binary search tree. It contains the key, value, parent, left child, and right child pointers.

## Constructor and Destructor

- `Dictionary()` creates a new empty dictionary.
- `Dictionary(const Dictionary &D)` is the copy constructor that creates a deep copy of the given dictionary.
- `~Dictionary()` is the destructor that cleans up the memory allocated for the dictionary.

## Helper Functions

These are internal helper functions used by the class:

- `preOrderCopy(Node* R, Node* N)` recursively copies the nodes from one tree to another.
- `search(Node* R, keyType k)` searches for a node with the given key in the subtree rooted at R.
- `postOrderDelete(Node* R)` recursively deletes all nodes in the subtree rooted at R.
- `insert(keyType k, valType v)` inserts a new node with the given key and value into the dictionary.
- `transplant(Node* u, Node* v)` replaces one subtree with another in the tree.
- `treeMinimum(Node* R)` returns the node with the minimum key in the subtree rooted at R.
- `treeMaximum(Node* R)` returns the node with the maximum key in the subtree rooted at R.
- `inOrderString(std::string &s, Node* R)` appends a string representation of the tree to s in in-order traversal.
- `preOrderString(std::string &s, Node* R)` appends a string representation of the tree to s in pre-order traversal.

## Access Functions

These functions provide access to the dictionary:

- `size()` returns the number of key-value pairs in the dictionary.
- `contains(keyType k)` checks if a pair with the given key exists in the dictionary.
- `getValue(keyType k)` returns a reference to the value associated with the given key.
- `hasCurrent()` checks if the current iterator is defined.
- `currentKey()` returns the key of the current pair.
- `currentVal()` returns a reference to the value of the current pair.

## Manipulation Procedures

These functions modify the dictionary:

- `clear()` resets the dictionary to the empty state.
- `setValue(keyType k, valType v) `sets the value for the pair with the given key. If the key doesn't exist, it inserts a new pair.
- `remove(keyType k)` removes the pair with the given key from the dictionary.
- `begin()` moves the current iterator to the first pair in the dictionary.
- `end()` moves the current iterator to the last pair in the dictionary.
- `next()` moves the current iterator to the next pair.
- `prev() `moves the current iterator to the previous pair.

## Other Functions

- `to_string()` returns a string representation of the dictionary.
- `pre_string()` returns a string representation of the dictionary with keys only.
- `equals(const Dictionary& D)` checks if two dictionaries are equal.
- `operator<<()` overloads the << operator to allow printing the dictionary directly to the output stream.
- `operator==()` overloads the == operator to compare two dictionaries for equality.
- `operator=()` overloads the assignment operator to copy the state of one dictionary to another.

## Order.cpp

Order.cpp is a program that reads input from a file, inserts the strings into a dictionary, and writes the dictionary to an output file. It is designed to be used through the command line with two arguments: the input file and the output file.