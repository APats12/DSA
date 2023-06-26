// -----------------------------------------------------------------------------
//  Dictionary.cpp
//  Aryan Patel
// -----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include "Dictionary.h"

// Node Consturctor - added color: red = 0 black = 1
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 0;
}

// Creates Dictionary in the empty state
Dictionary::Dictionary() {
    nil = new Node("nil", 0);
    num_pairs = 0;
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = 1;
    root = nil;
    current = nil;
}


// Copy constructor
Dictionary::Dictionary(const Dictionary &D) {
    nil = new Node("nil", 0);
    num_pairs = 0;
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = 1;
    root = nil;
    current = nil;
    preOrderCopy(D.root, root);
    num_pairs = D.num_pairs;
}

// Destructor
Dictionary::~Dictionary() {
  postOrderDelete(root);
  delete nil;
}

// Helper Functions --------------------------------------------------------

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    // Check if R is not null and is not the sentinel node
    if (R != nullptr && R->key != "nil") {
        // Copy the key and value from R to the current Dictionary node
        setValue(R->key, R->val);
        // Recursively copy the left and right subtrees
        preOrderCopy(R->left, N->left);
        preOrderCopy(R->right, N->right);
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
    if(R == nil || k == R->key){
        return R;
    } 
    else if(k < R->key){
        return search(R->left, k);
    } 
    else{ 
        return search(R->right, k);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left); // delete left subtree
        postOrderDelete(R->right); // delete right subtree
        delete R; // delete this node
    }
}

// insert()
// Inserts the (k, v) pair into this Dictionary.
void Dictionary::insert(keyType k, valType v) {
    Node *newNode = new Node(k, v);
    Node *current = root;
    Node *parent = nil;
    // Traverse the Dictionary to find the proper place to insert the new Node
    while (current != nil) {
        parent = current;
        if (k < current->key) {
            current = current->left;
        } 
        else {
            current = current->right;
        }
    }
    // Link the new Node to its parent and update the root if necessary
    newNode->parent = parent;
    if (parent == nil) {
        root = newNode;
    } 
    else if (k < parent->key) {
        parent->left = newNode;
    } 
    else {
        parent->right = newNode;
    }
    // Set the new Node's children to nil
    newNode->left = nil;
    newNode->right = nil;
    // Increment the number of pairs in the Dictionary
    num_pairs++;
    newNode->color = 0;
    RB_InsertFixUp(newNode);

}

// transplant()
// Replaces one subtree as a child of its parent with another subtree.
// Used to delete a node from the tree.
void Dictionary::transplant(Node* u, Node* v) {
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// treeMinimum()
// Returns the Node containing the minimum key in the subtree rooted at R.
Dictionary::Node* Dictionary::treeMinimum(Node* R) const {
    while(R->left != nil){
        R = R->left;
    }
    return R;
}

// treeMaximum()
// Returns the Node containing the maximum key in the subtree rooted at R.
Dictionary::Node* Dictionary::treeMaximum(Node* R) const {
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}

// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        std::string entry = (R->key + " : " + std::to_string(R->val) + "\n");
        s += entry;
        inOrderString(s, R->right);
    }
}


// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const {
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// RBT Helper Functions ----------------------------------------------------

// LeftRotate() USING PSEUDO FROM EXAMPLES
void Dictionary::LeftRotate(Node *N) {
    Node *A = N->right;
    N->right = A->left;
    if (A->left != nil){
        A->left->parent = N;
    }
    A->parent = N->parent;
    if (N->parent == nil){
        root = A;
    }
    else if (N == N->parent->left){
        N->parent->left = A;
    }
    else{
        N->parent->right = A;
    }
    A->left = N;
    N->parent = A;
}

//RightRotate() USING PSEUDO FROM EXAMPLES
void Dictionary::RightRotate(Node* N){
    Node *A = N->left;
    N->left = A->right;
    if (A->right != nil){
        A->right->parent = N;
    }
    A->parent = N->parent;
    if (N->parent == nil){
        root = A;
    } 
    else if (N == N->parent->right){
        N->parent->right = A;
    } 
    else{
        N->parent->left = A;
    }
    A->right = N;
    N->parent = A;
}

//RB_InsertFixUp USING PSEUDO FROM EXAMPLES
void Dictionary::RB_InsertFixUp(Node* N){
    while(N->parent->color == 0){
        if(N->parent == N->parent->parent->left){
            Node *A = N->parent->parent->right;
            if(A->color == 0){
                N->parent->color = 1;
                A->color = 1;
                N->parent->parent->color = 0;
                N = N->parent->parent;
            }
            else{
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 1;
                N->parent->parent->color = 0;
                RightRotate(N->parent->parent);
            }
        }
        else{
            Node *A = N->parent->parent->left;
            if(A->color == 0){
                N->parent->color = 1;
                A->color = 1;
                N->parent->parent->color = 0;
                N = N->parent->parent;
            }
            else {
                if(N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 1;
                N->parent->parent->color = 0;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 1;
}

//RB_Transplant USING PSEUDO FROM EXAMPLES
void Dictionary::RB_Transplant(Node *u, Node *v) {
    if (u->parent == nil){
        root = v;
    } 
    else if (u == u->parent->left){
        u->parent->left = v;
    } 
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

//RB_DeleteFixUp USING PSEUDO FROM EXAMPLES
void Dictionary::RB_DeleteFixUp(Node *N) {
    while(N != root && N->color == 1){
        if(N == N->parent->left){
            Node *A = N->parent->right;
            if(A->color == 0){
                A->color = 1;
                N->parent->color = 0;
                LeftRotate(N->parent);
                A = N->parent->right;
            }
            if(A->left->color == 1 && N->right->color == 1){
                A->color = 0;
                N = N->parent;
            }
            else{
                if(A->right->color == 1){
                    A->left->color = 1;
                    A->color = 0;
                    RightRotate(A);
                    A = N->parent->right;
                }
                A->color = N->parent->color;
                N->parent->color = 1;
                A->right->color = 1;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else{
            Node *A = N->parent->left;
            if(A->color == 0){
                A->color = 1;
                N->parent->color = 0;
                RightRotate(N->parent);
                A = N->parent->left;
            }
            if(A->right->color == 1 && N->left->color == 1){
                A->color = 0;
                N = N->parent;
            }
            else{
                if(A->left->color == 1){
                    A->right->color = 1;
                    A->color = 0;
                    LeftRotate(A);
                    A = N->parent->left;
                }
                A->color = N->parent->color;
                N->parent->color = 1;
                A->left->color = 1;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 1;
}

//RB_Delete USING PSEUDO FROM EXAMPLES
void Dictionary::RB_Delete(Node* N){
    Node *A = N;
    Node *B = nil;
    int a_origin_col = A->color;
    if(A->left == nil){
        B = N->right;
        RB_Transplant(N, N->right);
    }
    else if(N->right == nil){
        B = N->left;
        RB_Transplant(N, N->left);
    }
    else{
        A = treeMinimum(N->right);
        a_origin_col = A->color;
        B = A->right;
        if(A->parent == N){
            B->parent = A;
        }
        else{
            RB_Transplant(A, A->right);
            A->right = N->right;
            A->right->parent = A;
        }
        RB_Transplant(N, A);
        A->left = N->left;
        A->left->parent = A;
        A->color = N->color;
    }
    if(a_origin_col == 1){
        RB_DeleteFixUp(B);
    }
}

// Access functions --------------------------------------------------------

// size() 
// returns size of this Dictionary
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false otherwise.
bool Dictionary::contains(keyType k) const {
    Node *result = search(root, k);
    if(result == nil){
        return false;
    } 
    else{
        return true;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    Node* result = search(root, k);
    if(result == nil) {
        // if the key is not found, throw an exception
        throw std::runtime_error("Key not found in Dictionary");
    }
    // return a reference to the value associated with the key
    return result->val;
}


// hasCurrent()
// Returns true if the current iterator is defined, and returns false otherwise.
bool Dictionary::hasCurrent() const {
    return (current != nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::length_error("Current iterator is not defined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Current iterator is not defined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root); // delete all nodes in the tree
    num_pairs = 0; // reset the number of pairs
    root = nil; // set root to nil
    current = nil; // set current to nil
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    Node *result = search(root, k); // search for the key k
    if (result == nil) {
        // key not found, insert new node
        insert(k, v);
    } 
    else {
        // key found, update value
        result->val = v;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    // Check if the key exists in the dictionary
    if (!contains(k)) {
        throw std::length_error("Dictionary ADT, remove(): key k not found in dictionary!");
    }
    // Find the node to be removed
    Node* r = search(root, k);
    // If the node to be removed is current, then current becomes undefined
    if (r == current) {
        current = nil;
    }
    RB_Delete(r);
    delete r;
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair 
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if (root != nil) {
        current = treeMinimum(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair 
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
    if (root != nil) {
        current = treeMaximum(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        return;
    }
    // Case 1: Current has a right subtree
    if (current->right != nil) {
        current = treeMinimum(current->right);
    }
    // Case 2: Current does not have a right subtree
    else {
        Node* temp = current->parent;
        while (temp != nil && current == temp->right) {
            current = temp;
            temp = temp->parent;
        }
        current = temp;
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        return;
    }
    if (current->left != nil) {
        current = treeMaximum(current->left);
    } else {
        Node* y = current->parent;
        while (y != nil && current == y->left) {
            current = y;
            y = y->parent;
        }
        current = y;
    }
}

// Other Functions ---------------------------------------------------------

// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string str = "";
    inOrderString(str, root);
    return str;
}

// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string str = "";
    preOrderString(str, root);
    return str;
}

// equals() returns true if and only if this dictionary contains the same key
// value pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    return to_string() == D.to_string();
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// to_string
std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
    return stream << D.to_string();
}

// operator ==() returns true if and only if Dict A == Dict B, as defined by
// equals().
bool operator==(const Dictionary &A, const Dictionary &B) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if( this != &D ){ // not self assignment
        // make a copy of D
        Dictionary temp = D;    // copy constructor.
        // then swap the copy's fields with fields of this
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    // return this with the new data installed
    return *this;
}