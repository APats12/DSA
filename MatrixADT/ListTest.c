//-----------------------------------------------------------------------------
//  ListTest.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
    List A = newList();
    List B = newList();

    prepend(A, 1);
    //printList(stdout, A);
    prepend(B, 1);
    //printList(stdout, B);
    prepend(A, 2);
    //printList(stdout, A);
    moveFront(B);
    //printList(stdout, B);
    insertBefore(B, 2);
    //printList(stdout, B);

    append(A, 1);
    //printList(stdout, A);
    printf("\n");

    deleteBack(A);
    //printList(stdout, A);
    printf("\n");

    append(A, 2);
    append(A, 3);
    append(A, 5);
    //printList(stdout, A);
    printf("\n");
    moveFront(A);
    printf("Cursorindex, %d", index(A));
    printf("\n");
    insertAfter(A, 12);
    //printList(stdout, A);
    printf("\n");
    deleteBack(A);
    printf("\n");
    //printList(stdout, A);
    printf("\n");
    printf("Length, %d", length(A));


    prepend(A, 76);
    //printList(stdout, A);
    printf("\n");
    prepend(A, 4);
    //printList(stdout, A);
    printf("\n");
    deleteFront(A);
    //printList(stdout, A);
    printf("\n");
    prepend(A, 3);
    //printList(stdout, A);
    printf("\n");
    prepend(A, 1);
    //printList(stdout, A);
    printf("\n");
    moveFront(A);
    insertBefore(A, 115);
    //printList(stdout, A);
    printf("\n");
    deleteFront(A);
    //printList(stdout, A);
    printf("\n");


    //list A -  2 1
    //list B -  1 

    //printList(stdout, A);
    printf("\n");
    //printList(stdout, B);
    printf("\n");

    printf("Cursorindex, %d", index(A));
    printf("\n");
    printf("Cursorindex, %d", index(B));
    printf("\n");
    

}