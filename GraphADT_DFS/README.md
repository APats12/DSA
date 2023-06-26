# Graph ADT and DFS

The program implements a Graph abstract data type (ADT) using the adjacency list representation. It provides functions to create and manipulate a graph, perform depth-first search (DFS), and print the graph.

## Important Files
The program consists of the following files:

- `List.c`: This file contains the implementation of the doubly linked list ADT.
- `List.h`: This is the header file that declares the functions and structures used in `List.c`.
- `Graph.c`: This file contains the implementation of the Graph ADT.
- `Graph.h`: This is the header file that declares the functions and structures used in `Graph.c`.
- `FindComponents.c`: This is a C program that finds the strongest components of a graph using an adjacency list and DFS.

## Abstract Data Type (ADT) - Graph

The Graph ADT provides the following functions:
- `Graph newGraph(int n)`: Creates a new graph with `n` vertices.
- `void freeGraph(Graph* pG)`: Frees the memory allocated for the graph.
- `int getOrder(Graph G)`: Returns the number of vertices in the graph.
- `int getSize(Graph G)`: Returns the number of edges in the graph.
- `int getParent(Graph G, int u)`: Returns the parent of vertex `u` in the DFS forest.
- `int getDiscover(Graph G, int u)`: Returns the discovery time of vertex `u` in the DFS.
- `int getFinish(Graph G, int u)`: Returns the finish time of vertex `u` in the DFS.
- `void addArc(Graph G, int u, int v)`: Adds a directed edge from vertex `u` to vertex `v`.
- `void addEdge(Graph G, int u, int v)`: Adds an undirected edge between vertex `u` and vertex `v`.
- `void DFS(Graph G, List S)`: Performs a depth-first search on the graph starting from the vertices in list `S`.
- `Graph transpose(Graph G)`: Computes the transpose of the given graph.
- `Graph copyGraph(Graph G)`: Creates a copy of the given graph.
- `void printGraph(FILE* file, Graph graph)`: Prints the graph to a specified file.

## Depth-First Search (DFS)

The program implements the depth-first search algorithm using the Graph ADT. The `DFS` function takes a graph `G` and a list `S` of starting vertices and performs DFS on the graph. During the DFS, the algorithm assigns colors (white, gray, black) to vertices, discovers vertices, and assigns finish times. The DFS function also returns the list `S` in an order that represents the decreasing finish times.