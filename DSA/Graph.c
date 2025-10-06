// Created by Anshumaan Soni on 29/09/25.

#include "stdio.h"
#include "stdlib.h"

// Define the structure for Adjacency List
typedef struct adjlist {
    int dest;
    struct adjlist* next;
} AdjList;

// Define the structure for a Graph
// Each Graph contains an array of adjacency lists
typedef struct graph {
    int vertex;
    struct AdjList** array;
} Graph;


// Function to create a new adjacency list node
AdjList* newAdjListNode(int dest) {
    AdjList* newNode = (AdjList*)malloc(sizeof(AdjList));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertex = V;

    // Create an array of adjacency lists
    graph->array = (AdjList**)malloc(V * sizeof(AdjList*));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; i++) {
        graph->array[i] = NULL;
    }

    return graph;
}

void AddEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    AdjList* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}

// Function to print the adjacency list representation of the graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->vertex; v++) {
        AdjList* pCrawl = graph->array[v];
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Deletes a vertex and all associated edges
void deleteVertex(Graph* graph, int v) {
    AdjList* pCrawl = graph->array[v];
    while (pCrawl){
        int adjVertex = pCrawl->dest;

        // Remove edge from adjVertex to v
        AdjList* curr = graph->array[adjVertex];
        AdjList* prev = NULL;
        
        while(curr) {
            if (curr->dest == v) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    graph->array[adjVertex] = curr->next;
                }
                free(curr);
                break;
            }
        }
    }
}

int main() {
    int V = 5; // Number of vertices
    Graph* graph = createGraph(V);
    AddEdge(graph, 0, 1);
    AddEdge(graph, 0, 4);
    AddEdge(graph, 1, 2);
    AddEdge(graph, 1, 3);
    AddEdge(graph, 1, 4);
    AddEdge(graph, 2, 3);
    AddEdge(graph, 3, 4);

    // Print the adjacency list representation of the graph
    printGraph(graph);

    return 0;
}
