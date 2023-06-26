# Graph ADT and BFS

The program implements a Graph abstract data type (ADT) using the adjacency list representation. It provides functions to create and manipulate a graph, perform breadth-first search (BFS), and print the graph.

## Important Files
The program consists of the following files:

- `List.c`: This file contains the implementation of the doubly linked list ADT.
- `List.h`: This is the header file that declares the functions and structures used in `List.c`.
- `Graph.c`: This file contains the implementation of the Graph ADT.
- `Graph.h`: This is the header file that declares the functions and structures used in `Graph.c`.
- `FindPath.c`: This is a C program that finds the shortest path between two vertices in a graph using BFS.


## Abstract Data Type (ADT) - Graph

The Graph ADT provides the following functions:

- `Graph newGraph(int n)`: Creates a new empty graph with `n` vertices and returns a reference to it.
- `void freeGraph(Graph* pG)`: Frees the memory associated with the graph and sets the reference to NULL.
- `int getOrder(Graph G)`: Returns the number of vertices in the graph.
- `int getSize(Graph G)`: Returns the number of edges in the graph.
- `int getSource(Graph G)`: Returns the most recently used source vertex for BFS.
- `int getParent(Graph G, int u)`: Returns the parent vertex of vertex `u` in the BFS tree.
- `int getDist(Graph G, int u)`: Returns the distance from the most recently used source vertex to vertex `u` in the BFS tree.
- `void getPath(List L, Graph G, int u)`: Stores the shortest path from the most recently used source vertex to vertex `u` in List `L`.
- `void makeNull(Graph G)`: Clears all edges from the graph, making it empty.
- `void addEdge(Graph G, int u, int v)`: Adds an undirected edge between vertices `u` and `v`.
- `void addArc(Graph G, int u, int v)`: Adds a directed edge from vertex `u` to vertex `v`.
- `void BFS(Graph G, int s)`: Performs breadth-first search starting from vertex `s`.
- `void printGraph(FILE* file, Graph graph)`: Prints the graph representation to the specified file.


