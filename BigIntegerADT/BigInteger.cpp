// -----------------------------------------------------------------------------
//  BigInteger.cpp
//  Aryan Patel
// -----------------------------------------------------------------------------

#include "BigInteger.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

const long BASE = 1000000000;
const int POWER = 9;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}


// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    // Check if the input string is empty, and throw an exception if it is.
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    // Initialize the start index and the sign variable based on the first character of the string.
    // If the first character is '-', set the sign variable to -1 and start the index at 1.
    // If the first character is '+', start the index at 1.
    int startIndex = 0;
    int sign = 1;
    if (s[0] == '-') {
        sign = -1;
        startIndex = 1;
    } else if (s[0] == '+') {
        startIndex = 1;
    }
    // Check if all the characters in the string are digits.
    bool allDigits = true;
    for (std::string::size_type i = startIndex; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            allDigits = false;
            break;
        }
    }
    // If any character in the string is not a digit, throw an exception.
    if (!allDigits) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    // If the string is equal to "0", set the signum to 0 and return.
    if (s == "0") {
        return;
    }
    // Set the signum based on the sign variable.
    signum = sign;
    // Initialize the end index to the length of the string.
    int endIndex = s.length();
    // Divide the string into substrings of length POWER (defined elsewhere).
    // Convert each substring to a long long and insert it into the linked list of digits.
    while (endIndex > startIndex) {
        int numDigits = std::min(endIndex - startIndex, POWER);
        std::string numStr = s.substr(endIndex - numDigits, numDigits);
        long long num = std::stoll(numStr);
        digits.insertAfter(num);
        endIndex -= numDigits;
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = List(N.digits);
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& other) const {
    List thisDigits = this->digits;
    List otherDigits = other.digits;
    // Sign comparisons
    if (signum > other.signum) {
        return 1;
    } else if (signum < other.signum) {
        return -1;
    } else if (signum == 0 && other.signum == 0) {
        return 0;
    }
    int signCheck = signum;
    // Check if same number of digits; bigger number of digits
    if ((thisDigits.length() < otherDigits.length() && signCheck == -1) || (thisDigits.length() > otherDigits.length() && signCheck == 1)) {
        return 1 * signCheck;
    } 
    else if ((thisDigits.length() > otherDigits.length() && signCheck == -1) || (thisDigits.length() < otherDigits.length() && signCheck == 1)) {
        return -1 * signCheck;
    } 
    else {
        thisDigits.moveFront();
        otherDigits.moveFront();
        // Compare digits until there is a difference
        while (thisDigits.position() != thisDigits.length() && otherDigits.position() != otherDigits.length()) {
            ListElement digitVal = thisDigits.moveNext();
            ListElement nDigitVal = otherDigits.moveNext();
            if (digitVal > nDigitVal) {
                return (1 * signCheck);
            } 
            else if (digitVal < nDigitVal) {
                return (-1 * signCheck);
            }
        }
        // Check for remaining digits 
        if (thisDigits.position() != thisDigits.length()) {
            return (1 * signCheck);
        } 
        else if (otherDigits.position() != otherDigits.length()) {
            return (-1 * signCheck);
        } 
        else {
            return 0;
        }
    }
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
    List digitsTemp;
    digits = digitsTemp;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (signum != 0){
        signum *= -1;
    }
} 

// Helper Functions --------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        int temp = L.peekNext() * -1;
        L.setAfter(temp);
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// // Used by both sum() and sub().
void sumList(List &S, List A, List B, int sgn) {
    S.moveFront();
    A.moveBack();
    B.moveBack();
    for(;A.position() > 0 || B.position() > 0; ) { 
        if(A.position() == 0) {
            S.insertAfter(sgn * B.peekPrev()); //If A is empty insert B into S multiplied by the sgn of B
            B.movePrev();
        }
        else if(A.position() > 0 && B.position() > 0) {
            S.insertAfter(A.peekPrev() + sgn * B.peekPrev()); //If both A and B have elements insert the sum of the corresponding elements multiplied by sgn
            A.movePrev();
            B.movePrev();
        } 
        else if(B.position() == 0) {
            S.insertAfter(A.peekPrev()); //If B is empty insert A
            A.movePrev();
        }
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits, then returns the sign of the resulting integer. Used by add(), sub() and mult().
int normalizeList(List &L) {
    if (L.length() == 0) {
        return 0;
    }
    int sign = 1;
    long l;
    L.moveBack(); //move cursor to the end of the list
    L.movePrev();  //move cursor to the second-to-last element
    for (int i = L.position(); i > 0; i--) { //Normalize digits from right to left
        if (L.peekNext() < 0) {
            l = (abs(L.peekNext()) + BASE - 1) / BASE * BASE;
            L.setAfter(L.peekNext() + l);
            L.setBefore(L.peekPrev() - l / BASE);
        }
        else if (L.peekNext() >= BASE) {
            l = L.peekNext() / BASE * BASE;
            L.setAfter(L.peekNext() - l);
            L.setBefore(L.peekPrev() + l / BASE);
        }
        L.movePrev();
    }

    if (L.front() < 0) { //check if the result is negative
        sign = -1;
        negateList(L); //negate the list
        sign *= normalizeList(L); //recursively normalize the list
    }
    for (; L.front() >= BASE; ) { //carry from left to right
        l = L.peekNext() / BASE * BASE;
        L.setAfter(L.peekNext() - l);
        L.insertBefore(l / BASE);
    }
    for (; L.peekNext() == 0; ) { //remove leading zeroes
        if (L.position() == L.length() - 1) {
            return 0;
        }
        L.moveNext();
    }
    return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p.
void shiftList(List &L, int p) {
    L.moveBack();
    while (p > 0) {
        L.insertBefore(0);
        p--;
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m.
void scalarMultList(List &L, ListElement m) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(L.peekNext() * m);
        L.moveNext();
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger &N) const {
    List X = List(digits);
    List Y = List(N.digits);
    BigInteger sum = BigInteger();
    if (sign() == -1) { //If the sign of this BigInteger object is negative, negate the List X.
        negateList(X);
    }
    sumList(sum.digits, X, Y, N.sign());//Add the two Lists and store the result in the List of the BigInteger object sum.
    for (; sum.digits.length() > 0 && sum.digits.front() == 0; ) {//Remove leading zeros
        sum.digits.eraseAfter();
    }
    sum.signum = normalizeList(sum.digits); //Set signum of sum based on the sign of its digits List
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger &N) const {
    List X = List(digits);
    List Y = List(N.digits);
    BigInteger diff = BigInteger();
    if (sign() == -1) {//If the sign of this BigInteger object is negative, negate the List X.
        negateList(X);
    }
    sumList(diff.digits, X, Y, N.sign() * -1);//subtract the two Lists and store the result in the List of the BigInteger object diff. 
    for (; diff.digits.length() > 0 && diff.digits.front() == 0; ) {//Remove leading zeros
        diff.digits.eraseAfter();
    }
    diff.signum = normalizeList((diff).digits);//Set signum of sum based on the sign of its digits List
    return diff;
}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger &N) const {
    List A = List(N.digits);
    BigInteger B = BigInteger();
    if (sign() == 0) { //If either operand is 0 ret 0
        if (N.sign() == 0){
            return B;
        }
        return B;
    }
    A.moveBack();
    int count = 0;
    while (A.position() > 0) { //Iterate over the digits in the input list
        BigInteger C = BigInteger(*this); // Create a copy of this BigInteger
        C.signum = 1; //Set the sign of the copy to positive
        scalarMultList(C.digits, A.peekPrev()); //Multiply the copy by the current digit in the input list
        shiftList(C.digits, count); //Shift the copy to the left by count positions
        normalizeList(C.digits); //Normalize the copy
        B = B.add(C); //Add the copy to the result
        A.movePrev();
        count += 1;
    }
    B.signum = sign() * N.sign(); //Set the sign of the result to the product of the signs of the operands
    return B;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    if (signum == 0 || digits.length() == 0) {
        return "0";
    }
    std::string s = "";
    digits.moveFront();
    while (digits.position() < digits.length()) {
        std::string num = std::to_string(digits.peekNext());
        int count = 0;
        while (count < POWER - num.length()) {
            s += "0";
            count++;
        }
        s += num;
        digits.moveNext();
    }
    while (s.length() > 1 && s.at(0) == '0') {
        s.erase(0, 1);
    }
    if (signum == -1) {
        s.insert(0, 1, '-');
    }
    return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, BigInteger N) {
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==(const BigInteger &A, const BigInteger &B) {
    return A.compare(B) == 0;
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<(const BigInteger &A, const BigInteger &B) {
    return A.compare(B) == -1;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B) {
    return A.compare(B) != 1;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B) {
    return A.compare(B) == 1;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B) {
    return A.compare(B) != -1;
}

// operator+()
// Returns the sum A+B.
BigInteger operator+(const BigInteger &A, const BigInteger &B) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=(BigInteger &A, const BigInteger &B) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-(const BigInteger &A, const BigInteger &B) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B.
BigInteger operator*(const BigInteger &A, const BigInteger &B) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=(BigInteger &A, const BigInteger &B) {
    A = A.mult(B);
    return A.mult(B);
}

