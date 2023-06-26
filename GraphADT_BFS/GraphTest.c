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
    int n=50;
    List C = newList();  
    Graph G = NULL;

    
    G = newGraph(n);
    for(int i=1; i<n; i++){
        if( i%7!=0 ) addEdge(G, i, i+1);
        if( i<=28  ) addEdge(G, i, i+7);
    }
    addEdge(G, 10, 27);
    addEdge(G, 4, 32);
    addEdge(G, 7, 20);

    printGraph(stdout, G);


}