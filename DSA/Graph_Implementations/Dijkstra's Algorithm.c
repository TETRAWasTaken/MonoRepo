//
// Created by Anshumaan soni on 10/29/25.
//

#include "Dijkstra's Algorithm.h"

// Creates a new adjacency list node
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode =
        (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Creates a graph of V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Adds an edge to an undirected graph (u -> v and v -> u)
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the solution path
void printSolution(int dist[], int n) {
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Main Dijkstra's Logic
void dijkstra(Graph *graph, int src) {
    int V = graph->V;
    int *dist = (int *)malloc(V * sizeof(int));

    MinHeap *minHeap = createMinHeap(V);

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        minHeap->array[i] = createHeapNode(i, dist[i]);
        minHeap->pos[i] = i;
    }

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        HeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        AdjListNode *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (minHeap->pos[v] < minHeap->size && dist[u] != INT_MAX && dist[u] + pCrawl->weight < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
        free(minHeapNode);
    }
    printSolution(dist, V);
    free(dist);
}


int main() {
    // Example graph (from the adjacency matrix example)
    // V = 9
    int V = 9;
    Graph* graph = createGraph(V);

    // Edges (src, dest, weight) - Duplicates handled by addEdge for undirected
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    int source_vertex = 0;
    printf("Dijkstra's Algorithm (Adjacency List with Min-Heap) starting from Source %d:\n", source_vertex);
    dijkstra(graph, source_vertex);

    return 0;
}
