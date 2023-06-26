# Dictionary ADT - Red/Black Tree

This program implements a dictionary data structure using a red-black tree. The Dictionary class allows you to store key-value pairs and perform various operations on them.

## Class Structure

Dictionary::Node: This nested class represents a node in the red-black tree. It contains fields for the key, value, parent, left child, right child, and color of the node.

Dictionary: This is the main class that implements the dictionary functionality. It has member functions for inserting, deleting, searching, and accessing key-value pairs. It also includes helper functions for various operations.

## Constructors and Destructors

Dictionary::Node::Node(keyType k, valType v): This constructor creates a new node with the given key and value.

Dictionary::Dictionary(): This constructor creates an empty dictionary. It initializes the sentinel node, sets the root and current nodes to the sentinel, and sets the number of pairs to zero.

Dictionary::Dictionary(const Dictionary &D): This is the copy constructor, which creates a deep copy of the given dictionary.

Dictionary::~Dictionary(): This destructor deallocates the memory used by the dictionary, including all nodes and the sentinel node.

## Helper Functions

The class includes several helper functions to support the main operations:

preOrderCopy(): Recursively copies the subtree rooted at R to the current dictionary.

search(): Searches for a node with the specified key in the subtree rooted at R.

postOrderDelete(): Deletes all nodes in the subtree rooted at R.

insert(): Inserts a new key-value pair into the dictionary.

transplant(): Replaces one subtree with another subtree, used for deleting a node from the tree.

treeMinimum(): Returns the node containing the minimum key in the subtree rooted at R.

treeMaximum(): Returns the node containing the maximum key in the subtree rooted at R.

inOrderString(): Appends a string representation of the tree rooted at R in an in-order traversal to the given string.

preOrderString(): Appends a string representation of the tree rooted at R in a pre-order traversal to the given string.

## Red-Black Tree Operations

The class also includes helper functions for maintaining the red-black tree properties:

LeftRotate(): Performs a left rotation on the given node.

RightRotate(): Performs a right rotation on the given node.

RB_InsertFixUp(): Fixes the red-black tree properties after an insertion.

RB_Transplant(): Replaces one subtree with another subtree, used in the delete operation.

RB_DeleteFixUp(): Fixes the red-black tree properties after a deletion.

RB_Delete(): Deletes the given node from the tree.

## Access Functions
The following functions provide access to the dictionary and its contents:

size(): Returns the number of key-value pairs in the dictionary.

contains(): Checks if a pair with the specified key exists in the dictionary.

getValue(): Returns a reference to the value associated with the specified key.

hasCurrent(): Checks if the current iterator is defined.

currentKey(): Returns the key of the current iterator.

currentVal(): Returns a reference to the value of the current iterator.

## Manipulation Procedures

The following functions allow you to modify the contents of the dictionary:

clear(): Resets the dictionary to an empty