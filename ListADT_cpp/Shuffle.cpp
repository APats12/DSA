//-----------------------------------------------------------------------------
//  Shuffle.cpp
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

#include"List.h"

void shuffle(List& D);

void shuffle(List& D){
    List temp;
    int half_size = D.length() / 2;
    D.moveFront();
    // Move the first half of the list to a temporary list
    for(int i = 0; i < half_size; i++){
        int data = D.moveNext();
        temp.insertBefore(data);
        D.eraseBefore();
    } 
    // Insert the elements from the temporary list into the original list
    // alternating with the elements in the second half of the original list
    D.moveFront();
    temp.moveFront();
    while (temp.position() < temp.length()) {
        D.moveNext();
        D.insertAfter(temp.moveNext());
        D.moveNext();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return(EXIT_FAILURE);
    }
    int max_deck_size = stoi(argv[1]);
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    for (int i = 1; i <= max_deck_size; i++) {
        List L;
        for (int j = 0; j < i; j++) {
            L.insertBefore(j);
        }
        List D(L);
        int shuffle_count = 0;
        do {
            shuffle(D);
            shuffle_count++;
        } while (!D.equals(L));
        cout << i << "\t\t" << shuffle_count << endl;
    }
    return(EXIT_SUCCESS);
}