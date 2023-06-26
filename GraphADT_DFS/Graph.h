//-----------------------------------------------------------------------------
//  Graph.h
//  Aryan Patel
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

#define UNDEF -1
#define NIL 0
#define WHITE 1     //undiscovered
#define GRAY 2     //discovered but not all neighbors have been discovered
#define BLACK 3     //finished

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List s);
void visit(Graph G, int x, int *tPtr);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
void sortGraph(Graph G);
void shiftCursor(List L, int i);