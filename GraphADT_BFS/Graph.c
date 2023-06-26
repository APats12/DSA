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
    //An array of ints whose ith element is the color (white, gray, black) of vertex i.
    List color;
    //An array of ints whose ith element is the parent of vertex i.
    List parent;
    //An array of ints whose ith element is the distance from the (most recent) source to vertex i.
    List dist;
    //number of vertices
    int order;
    //the number of edges
    int size;
    //Label of the vertex that was most recently used as source for BFS
    int source_vertex;
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
    g->dist = newList();
    for(int i = 0; i <= n; i++){
        append(g->color, WHITE);
        append(g->dist, INF);
        append(g->parent, NIL);
    }
    g->order = n;
    g->size = 0;
    g->source_vertex = NIL;
    return g;
}

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL){
        for (int i = 0; i <= getOrder(*pG); i++) {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->adj);
        freeList(&(*pG)->color);
        freeList(&(*pG)->parent);
        freeList(&(*pG)->dist);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

int getOrder(Graph G){
    if (G == NULL)
    {
        printf("Graph error: calling getOrder() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G){
    if (G == NULL)
    {
        printf("Graph error: calling getSize() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G){
    if (G == NULL)
    {
        printf("Graph error: calling getSource() on NULL Graph \n");
        exit(EXIT_FAILURE);
    }
    return G->source_vertex;
}

int getParent(Graph G, int u){
    if(G->source_vertex == NIL){
        return NIL;
    }
    List parent = G->parent;
    moveFront(parent);
    while(index(parent) != u){
        moveNext(parent);
    }
    return get(parent);
}

int getDist(Graph G, int u){
    if(G->source_vertex == NIL){
        return INF;
    }
    List distance = G->dist;
    moveFront(distance);
    while(index(distance) != u){
        moveNext(distance);
    }
    return get(distance);
}

void getPath(List L, Graph G, int u) {
    if (u == getSource(G)) {
        append(L, u);
        return;
    }
    List temp = newList();
    int curr = u, parent = getParent(G, u);
    append(temp, curr);
    append(temp, parent);
    while (parent != getSource(G) && parent != NIL) {
        curr = parent;
        parent = getParent(G, parent);
        append(temp, parent);
    }
    if (parent == NIL) {
        append(L, NIL);
    }
    else {
        moveBack(temp);
        while (index(temp) >= 0) {
            append(L, get(temp));
            movePrev(temp);
        }
    }
    freeList(&temp);    
}

/*** Manipulation procedures ***/

void makeNull(Graph G){
    for (int i = 1; i <= G->order; i++) {
        clear(G->adj[i]);
    }
    clear(G->color);
    clear(G->parent);
    clear(G->dist);
    G->size = 0;
    G->source_vertex = NIL;
}

void addEdge(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph error: calling addEdge() with invalid vertices\n");
        exit(EXIT_FAILURE);
    }
    if(u == v){
        return;
    }
    append(G->adj[u], v);
    append(G->adj[v], u);
    G->size += 1;
}

void addArc(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph error: calling addArc() with invalid vertices\n");
        exit(EXIT_FAILURE);
    }
    if(u == v){
        return;
    }
    append(G->adj[u], v);
    G->size += 1;
}

//using pseudocode given in examples 
void BFS(Graph G, int s){
    sortGraph(G);
    G->source_vertex = s;
    moveFront(G->color);
    moveFront(G->dist);
    moveFront(G->parent);
    for(int i = 0; i <= G->order; i++){
        set(G->color, WHITE);
        set(G->dist, INF);
        set(G->parent, NIL);
        moveNext(G->color);
        moveNext(G->dist);
        moveNext(G->parent);
    }
    moveFront(G->color);
    moveFront(G->dist);
    moveFront(G->parent);
    while (index(G->color) != s)
    {
        moveNext(G->color);
        moveNext(G->dist);
        moveNext(G->parent);
    }
    set(G->color, GRAY);
    set(G->dist, 0);
    set(G->parent, NIL);
    List queue = newList();
    append(queue, s);
    while(length(queue) > 0){
        int x = front(queue);
        deleteFront(queue);
        moveFront(G->adj[x]);
        while (index(G->adj[x]) >= 0){
            int y = get(G->adj[x]);
            moveFront(G->dist);
            while(index(G->dist) != x){
                moveNext(G->dist);
            }
            int x_dist = get(G->dist);
            moveFront(G->color);
            moveFront(G->dist);
            moveFront(G->parent);
            while(index(G->color) != y){
                moveNext(G->color);
                moveNext(G->dist);
                moveNext(G->parent);
            }
            if(get(G->color) == WHITE){
                set(G->color, GRAY);
                set(G->dist, x_dist + 1);
                set(G->parent, x);
                append(queue, y);
            }
            moveNext(G->adj[x]);
        }
        moveFront(G->color);
        while (index(G->color) != x)
        {
            moveNext(G->color);
        }
        set(G->color, BLACK);
    }
    freeList(&queue);
}


/*** Other operations ***/
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