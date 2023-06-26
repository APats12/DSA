//-----------------------------------------------------------------------------
//  FindComponents.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"

int main(int argc, char *argv[]) {
    // Check input argument and open input/output file
    if(argc != 3) {
        printf("Invalid number of inputs\n");
        exit(1);
    }
    FILE* input = fopen(argv[1], "r");
    if(input == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    FILE* output = fopen(argv[2], "w");
    if( output==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Read the number of vertices from input file
    int n = 0;
    fscanf(input, "%d", &n);
    Graph G = newGraph(n);
    Graph T = NULL;
    List S = newList();
    for(int i=1; i<=n; i++) append(S, i);

    // Read edges from input file
    int vertexU,vertexV;
    fscanf(input, "%d %d\n", &vertexU, &vertexV);
    while(vertexU != 0 || vertexV != 0){
        addArc(G, vertexU, vertexV);
        fscanf(input, "%d %d\n", &vertexU, &vertexV);
    }

    // Sort the adjacency list of the graph
    sortGraph(G);

    // Print the adjacency list representation of the graph to output file
    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, G);

    // Find the strongly connected components of the graph
    T = transpose(G);
    DFS(G, S);
    DFS(T, S);
    List R = newList();
    int count = 0;
    moveFront(S);
    while(index(S) >= 0){
        if(getParent(T, get(S)) == NIL){
            count++;
            prepend(R, get(S));
        }
        moveNext(S);
    }
    fprintf(output, "\nG contains %d strongly connected components:\n", count);

    // Print the components to output file
    int k = 1;
    moveFront(R);
    while(index(R) >= 0){
        fprintf(output, "Component %d: ", k++);
        List components = newList();

        if(index(S) < 0) moveBack(S);
        while(index(S) >= 0){
            if(getParent(T,get(S)) == NIL){
                prepend(components, get(S));
                movePrev(S);
                break;
            }
            prepend(components, get(S));
            movePrev(S);
        }
        printList(output, components);
        fprintf(output, "\n");
        freeList(&components);
        moveNext(R);
    }
    // Free memory and close files
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    freeList(&R);
    fclose(input);
    fclose(output);
    return 0;
    }
