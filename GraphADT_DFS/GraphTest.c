//-----------------------------------------------------------------------------
//  GraphTest.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
    printf("Hello");
    Graph A = newGraph(0);
    addArc(A, 54, 1);
    addArc(A, 54, 2);
    addArc(A, 54, 2);
    addArc(A, 54, 3);
    addArc(A, 1, 54);
    addArc(A, 1, 54);
    addArc(A, 1, 55);
    addArc(A, 1, 55);
    int x = getSize(A);
    printf(x);


}