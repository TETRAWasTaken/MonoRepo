// Created by Anshumaan Soni on 29/09/25.
#include "Graph.h"

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

// Function to add a vertex to the graph
void addVertex(Graph* graph) {
    int V = graph->vertex;
    AdjList** newArray = (AdjList**)realloc(graph->array, (V + 1) * sizeof(AdjList*));
    if (newArray == NULL) {
        printf("Failed to allocate memory for new vertex.\n");
        return;
    }
    graph->array = newArray;
    graph->vertex = V + 1;
    graph->array[V] = NULL;
    printf("Vertex added. New number of vertices: %d\n", graph->vertex);
}

// Function to add an edge to the graph
void AddEdge(Graph* graph, int src, int dest) {
    // Check if the edge already exists
    AdjList* pCrawl = graph->array[src];
    while (pCrawl != NULL) {
        if (pCrawl->dest == dest) {
            printf("Edge between %d and %d already exists.\n", src, dest);
            return;
        }
        pCrawl = pCrawl->next;
    }

    // Add an edge from src to dest
    AdjList* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}

// Function to delete an edge from the graph
void deleteEdge(Graph* graph, int src, int dest) {
    // Remove edge from src to dest
    AdjList *pCrawl = graph->array[src];
    AdjList *prev = NULL;

    while (pCrawl != NULL && pCrawl->dest != dest) {
        prev = pCrawl;
        pCrawl = pCrawl->next;
    }

    if (pCrawl != NULL) {
        if (prev != NULL) {
            prev->next = pCrawl->next;
        } else {
            graph->array[src] = pCrawl->next;
        }
        free(pCrawl);
    }

    // Since the graph is undirected, remove edge from dest to src
    pCrawl = graph->array[dest];
    prev = NULL;

    while (pCrawl != NULL && pCrawl->dest != src) {
        prev = pCrawl;
        pCrawl = pCrawl->next;
    }

    if (pCrawl != NULL) {
        if (prev != NULL) {
            prev->next = pCrawl->next;
        } else {
            graph->array[dest] = pCrawl->next;
        }
        free(pCrawl);
    }
    printf("Edge between %d and %d deleted.\n", src, dest);
}

// Function to print the adjacency list representation of the graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->vertex; v++) {
        AdjList* pCrawl = graph->array[v];
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf(" -> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Deletes a vertex and all associated edges
void deleteVertex(Graph* graph, int v) {
    if (v >= graph->vertex) {
        printf("Vertex %d does not exist.\n", v);
        return;
    }

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
            prev = curr;
            curr = curr->next;
        }
        pCrawl = pCrawl->next;
    }

    // Free the adjacency list of vertex v
    pCrawl = graph->array[v];
    while(pCrawl) {
        AdjList* temp = pCrawl;
        pCrawl = pCrawl->next;
        free(temp);
    }
    graph->array[v] = NULL;
    printf("Vertex %d deleted.\n", v);
}

AdjList* returnList(int node, Graph* graph) {
    return graph->array[node];
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->vertex; i++) {
        AdjList* pCrawl = graph->array[i];
        while (pCrawl) {
            AdjList* temp = pCrawl;
            pCrawl = pCrawl->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}
