//-----------------------------------------------------------------------------
//  List.cpp
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include <unordered_set>
#include"List.h"
using namespace std;

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    prev = nullptr;
    next = nullptr;
}

// Creates new List in the empty state.
List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

//Copy constructor.
List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    Node* curr = L.frontDummy->next;
    while (curr != L.backDummy) {
        insertBefore(curr->data);
        curr = curr->next;
    }
    moveFront();
    while(pos_cursor != L.pos_cursor){
        moveNext();
    }
}


// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (num_elements == 0) {
        throw std::runtime_error("List Error: List is empty.");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (num_elements == 0) {
        throw std::runtime_error("List Error: List is empty.");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor == num_elements) {
        throw std::runtime_error("List Error: Cursor is at back of list.");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor == 0) {
        throw std::runtime_error("List Error: Cursor is at front of list.");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveBack();
    while (length() > 0) {
        eraseBefore();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = afterCursor->prev;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (pos_cursor == num_elements) {
        throw std::runtime_error("List Error: Cursor is at back of list.");
    }
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (pos_cursor == 0) {
        throw std::runtime_error("List Error: Cursor is at front of list.");
    }
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    afterCursor = newNode;
    num_elements++;
}

//insertBefore()
//Inserts x before cursor.
void List::insertBefore(int x){
    Node* newNode = new Node(x);
    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    beforeCursor = newNode;
    num_elements++;
    pos_cursor++;
}


// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if (pos_cursor == num_elements) {
        throw std::runtime_error("List Error: Cursor is at back of list.");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if (pos_cursor == 0) {
        throw std::runtime_error("List Error: Cursor is at front of list.");
    }
    beforeCursor->data = x;
} 

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if (pos_cursor == num_elements) {
        throw std::runtime_error("List Error: Cursor is at back of list.");
    }
    Node* oldNode = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements--;
    delete oldNode;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (position() == 0) {
        throw std::runtime_error("List Error: Cursor is at front of list.");
    }
    Node* oldNode = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    pos_cursor --;
    num_elements --;
    delete oldNode;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    Node* curr = afterCursor;
    int indx = pos_cursor + 1; 
    while (curr != backDummy) {
        if (curr->data == x) {
            afterCursor = curr->next;
            beforeCursor = curr;
            pos_cursor = indx;
            return pos_cursor;
        }
        curr = curr->next;
        indx++;
    }
    // x was not found
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
    return -1;
}

// // findPrev()
// // Starting from the current cursor position, performs a linear search (in 
// // the direction back-to-front) for the first occurrence of element x. If x
// // is found, places the cursor immediately before the found element, then
// // returns the final cursor position. If x is not found, places the cursor 
// // at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    Node* curr = beforeCursor;
    int indx = pos_cursor - 1;
    while (curr != frontDummy) {
        if (curr->data == x) {
            beforeCursor = curr->prev;
            afterCursor = curr;
            pos_cursor = indx;
            return pos_cursor;
        }
        curr = curr->prev;
        indx--;
    }
    // x was not match found
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    Node* curr = frontDummy->next;
    int curr_pos = 0;
    while (curr != backDummy) {
        int curr_val = curr->data;
        Node* next_node = curr->next;
        int inner_pos = curr_pos + 1;
        while (next_node != backDummy) {
            int next_val = next_node->data;
            if (next_val == curr_val) {
                Node* to_delete = next_node;
                next_node = next_node->next;
                Node* before = to_delete->prev;
                before->next = to_delete->next;
                to_delete->next->prev = before;
                delete to_delete;
                num_elements--;
                if (inner_pos <= pos_cursor) {
                    pos_cursor--;
                }
            } else {
                next_node = next_node->next;
            }
            inner_pos++;
        }
        curr_pos++;
        curr = curr->next;
    }
    int pos = pos_cursor;
    moveFront();
    while (position() != pos) {
        moveNext();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List newList;
    Node* curr = frontDummy->next;
    
    // Copy elements from this list to newList
    while (curr != backDummy) {
        newList.insertBefore(curr->data);
        curr = curr->next;
    }
    
    // Copy elements from L to newList
    curr = L.frontDummy->next;
    while (curr != L.backDummy) {
        newList.insertBefore(curr->data);
        curr = curr->next;
    }
    
    // Reset cursor position in newList
    newList.moveFront();
    
    return newList;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string result = "(";
    Node* current = frontDummy->next;
    while (current != backDummy) {
        result += std::to_string(current->data);
        if (current->next != backDummy) {
            result += ", ";
        }
        current = current->next;
    }
    result += ")";
    return result;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& other) const {
    // Check if the two lists have the same length
    if (num_elements != other.num_elements) {
        return false;
    }

    // Traverse both lists in parallel and compare their elements
    Node* curr_this = frontDummy->next;
    Node* curr_other = other.frontDummy->next;
    while (curr_this != backDummy && curr_other != other.backDummy) {
        if (curr_this->data != curr_other->data) {
            return false;
        }
        curr_this = curr_this->next;
        curr_other = curr_other->next;
    }

    // If we reach the end of both lists without finding any differences, they are equal
    return true;
}

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List & L ){
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged
bool operator==(const List& A, const List& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the contents of this List with the contents of L.
List& List::operator=(const List& L) {
    if (this == &L) {
        return *this; // no action necessary for self-assignment
    }
    List temp(L); // create temporary list to copy elements from L
    std::swap(frontDummy, temp.frontDummy); // swap dummies
    std::swap(backDummy, temp.backDummy);
    std::swap(beforeCursor, temp.beforeCursor); // swap cursors
    std::swap(afterCursor, temp.afterCursor);
    std::swap(pos_cursor, temp.pos_cursor); // swap cursor positions
    std::swap(num_elements, temp.num_elements); // swap number of elements
    return *this;
}



