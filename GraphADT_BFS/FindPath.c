//-----------------------------------------------------------------------------
//  FindPath.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "Graph.h"

int main(int argc, char *argv[]) {
    // Check argument and open input/output file
    if(argc != 3) {
        printf("Invalid number of inputs");
        exit(1);
    }
    // open files for reading and writing
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
    // Read the first part of input file
    int n;
    fscanf(input, "%d", &n);
    Graph G = newGraph(n);
    int u, v;
    fscanf(input, "%d %d\n", &u, &v);
    while (u != 0 || v != 0) {
        addEdge(G, u, v);
        fscanf(input, "%d %d\n", &u, &v);
    }
    sortGraph(G);
    printGraph(output, G);
    // Read the second part of input file
    fscanf(input, "%d %d\n", &u, &v);
    while (u != 0 || v != 0) {
        if (u == v) {
            fprintf(output, "\nThe distance from %d to %d is 0\n", u, v);
            fprintf(output, "A shortest %d-%d path is: %d\n", u, v, u);
        } else {
            BFS(G, u);
            int dist = getDist(G, v);
            if (dist == INF) {
                fprintf(output, "\nThe distance from %d to %d is infinity\n", u, v);
            } else {
                fprintf(output, "\nThe distance from %d to %d is %d\n", u, v, dist);
            }
            List path = newList();
            getPath(path, G, v);
            if (front(path) == NIL) {
                fprintf(output, "No %d-%d path exists\n", u, v);
            } else {
                fprintf(output, "A shortest %d-%d path is: ", u, v);
                printList(output, path);
            }
            freeList(&path);
        }
        fscanf(input, "%d %d\n", &u, &v);
    }
    // Close files and free graph
    fclose(input);
    fclose(output);
    freeGraph(&G);
    return 0;
}
