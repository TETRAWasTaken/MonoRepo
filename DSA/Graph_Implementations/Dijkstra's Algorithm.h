//
// Created by Anshumaan soni on 10/29/25.
//

#ifndef MONOREPO_DIJKSTRA_S_ALGORITHM_H
#define MONOREPO_DIJKSTRA_S_ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "MinHeap.h"

typedef struct adjListNode {
    int dest;
    int weight;
    struct adjListNode *next;
} AdjListNode;

typedef struct adjList {
    AdjListNode *head;
} AdjList;

typedef struct graph {
    int V;
    AdjList *array;
} Graph;

// Function prototypes
AdjListNode *newAdjListNode(int dest, int weight);

Graph *createGraph(int V);

void addEdge(Graph *graph, int src, int dest, int weight);

void printSolution(int dist[], int n);

void dijkstra(Graph *graph, int src);

#endif //MONOREPO_DIJKSTRA_S_ALGORITHM_H