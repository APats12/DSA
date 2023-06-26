//-----------------------------------------------------------------------------
//  Graph.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"Graph.h"
#include"List.h"


typedef struct GraphObj{

    // An array of Lists whose i'th element contains the neighbors of vertex i 
    List* adj;

    //A list of ints whose ith element is the color (white, gray, black) of vertex i.
    List color;

    //A list of ints whose ith element is the parent of vertex i.
    List parent;

    //number of vertices
    int order;

    //the number of edges
    int size;

    List discover;

    List finish;
} GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n){
    Graph g = (GraphObj *)malloc(1 * sizeof(GraphObj));
    g->adj = (List*)calloc(n + 1, sizeof(List));
    for(int i = 0; i <= n; i++){ 
        g->adj[i] = newList();
    }
    g->color = newList();
    g->parent = newList();
    g->discover = newList();
    g->finish = newList();
    for(int i = 0; i <= n; i++){
        append(g->color, WHITE);
        append(g->discover, UNDEF);
        append(g->finish, UNDEF);
        append(g->parent, NIL);
    }
    g->order = n;
    g->size = 0;
    return g;
}

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL){
        for (int i = 0; i <= getOrder(*pG); i++) {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->adj);
        freeList(&(*pG)->color);
        freeList(&(*pG)->discover);
        freeList(&(*pG)->finish);
        freeList(&(*pG)->parent);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

int getOrder(Graph G){
    if (G == NULL){
        printf("Graph error: calling getOrder() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G){
    if (G == NULL){
        printf("Graph error: calling getSize() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getParent(Graph G, int u){
    if (G == NULL){
        printf("Graph error: calling getParent() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    shiftCursor(G->parent, u);
    return get(G->parent);
}

int getDiscover(Graph G, int u){
    if (G == NULL){
        printf("Graph error: calling getDiscover() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    shiftCursor(G->discover, u);
    return get(G->discover);
}

int getFinish(Graph G, int u){
    if (G == NULL){
        printf("Graph error: calling getFinish() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    shiftCursor(G->finish, u);
    return get(G->finish);
}

/*** Manipulation procedures ***/

void addArc(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph error: calling addArc() with invalid vertices\n");
        exit(EXIT_FAILURE);
    }
    append(G->adj[u], v);
    G->size += 1;
    sortGraph(G);
}

void addEdge(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph error: calling addEdge() with invalid vertices\n");
        exit(EXIT_FAILURE);
    }
    append(G->adj[u], v);
    append(G->adj[v], u);
    G->size += 1;
    sortGraph(G);
}

void DFS(Graph G, List S){
    moveFront(S);
    while(index(S) >= 0){
        int x = get(S);
        shiftCursor(G->color, x);
        set(G->color, WHITE);
        shiftCursor(G->parent, x);
        set(G->parent, NIL);
        moveNext(S);
    }
    int time = 0;
    moveFront(S);
    while (index(S) >= 0){
        int x = get(S);
        shiftCursor(G->color, x);
        int color = get(G->color);
        if(color == WHITE){
            visit(G, x, &time);
        }
        moveNext(S);
    }
    //Making S in order of decreasing finish
    List L = newList();
    append(L, 1);
    moveFront(L);
    for(int i = 2; i <= length(S); i++){ 
        moveFront(L);
        while(index(L) >= 0){
            if(getFinish(G, i) < getFinish(G, get(L))){
                break;
            }
            moveNext(L);
        }
        if(index(L) < 0){
            append(L, i);
        }else{
            insertBefore(L,i);
        }
    }

    moveFront(S);
    moveBack(L);
    while (index(S) >= 0){
        set(S, get(L));
        moveNext(S);
        movePrev(L);
    }
    freeList(&L);
}

void visit(Graph G, int x, int *tPtr){
    shiftCursor(G->discover, x);
    *tPtr += 1;
    set(G->discover, *tPtr);
    shiftCursor(G->color, x);
    set(G->color, GRAY);
    moveFront(G->adj[x]);
    while(index(G->adj[x]) >= 0){
        int z = get(G->adj[x]);
        shiftCursor(G->color, z);
        int color = get(G->color);
        if (color == WHITE){
            shiftCursor(G->parent, z);
            set(G->parent, x);   
            visit(G, z, tPtr);
        }
        moveNext(G->adj[x]);
    }
    shiftCursor(G->color, x);
    set(G->color, BLACK);
    shiftCursor(G->finish, x);
    *tPtr += 1;
    set(G->finish, *tPtr);
}

/*** Other operations ***/

Graph transpose(Graph G){
    Graph transGraph = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++){
        List adjacents = G->adj[i];
        moveFront(adjacents);
        while(index(adjacents) >= 0){
            int adj_vert = get(adjacents);
            addArc(transGraph, adj_vert, i);
            moveNext(adjacents);
        }
    }
    return transGraph;
}

Graph copyGraph(Graph G) {
    int n = getOrder(G);
    Graph copy = newGraph(n);

    for (int i = 1; i <= n; i++) {
        moveFront(G->adj[i]);
        while (index(G->adj[i]) >= 0) {
            int neighbor = get(G->adj[i]);
            addArc(copy, i, neighbor);
            moveNext(G->adj[i]);
        }
    }

    copy->color = copyList(G->color);
    copy->parent = copyList(G->parent);
    copy->discover = copyList(G->discover);
    copy->finish = copyList(G->finish);

    return copy;
}


void printGraph(FILE* file, Graph graph) {
    if (graph == NULL) {
        printf("Error: cannot print a NULL graph\n");
        exit(EXIT_FAILURE);
    }
    int numVertices = getOrder(graph);
    for (int i = 1; i <= numVertices; i++) {
        fprintf(file, "%d:", i);
        moveFront(graph->adj[i]);
        while (index(graph->adj[i]) >= 0) {
            int neighbor = get(graph->adj[i]);
            fprintf(file, " %d", neighbor);
            moveNext(graph->adj[i]);
        }
        fprintf(file, "\n");
    }

}

void sortGraph(Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        if(length(G->adj[i]) == 0){
            continue;
        }
        List L = newList();
        moveFront(G->adj[i]);
        while(index(G->adj[i]) >= 0){
            moveFront(L);
            while(index(L) >= 0){
                if(get(L) > get(G->adj[i])){
                    break;
                }
                moveNext(L);
            }
            if(index(L) < 0){
                append(L, get(G->adj[i]));
            }
            else{
                insertBefore(L, get(G->adj[i]));
            }
            moveNext(G->adj[i]);
        }
        freeList(&(G->adj[i]));
        G->adj[i] = L;
    }
}

//shift the cursor index ith position
void shiftCursor(List L, int i){
    moveFront(L);
    while(index(L) != i){
        moveNext(L);
    }
}

