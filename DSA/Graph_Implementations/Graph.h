#ifndef GRAPH_H
#define GRAPH_H

#include "stdio.h"
#include "stdlib.h"

// Define the structure for Adjacency List
typedef struct AdjList {
    int dest;
    struct AdjList* next;
} AdjList;

// Define the structure for a Graph
// Each Graph contains an array of adjacency lists
typedef struct Graph {
    int vertex;
    AdjList** array;
} Graph;

// Function prototypes
AdjList* newAdjListNode(int dest);
Graph* createGraph(int V);
void addVertex(Graph* graph);
void AddEdge(Graph* graph, int src, int dest);
void deleteEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void deleteVertex(Graph* graph, int v);
AdjList* returnList(int node, Graph* graph);
void freeGraph(Graph* graph);

#endif //GRAPH_H
