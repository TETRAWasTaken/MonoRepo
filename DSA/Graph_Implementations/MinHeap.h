//
// Created by Anshumaan soni on 10/29/25.
//

#ifndef MONOREPO_MINHEAP_H
#define MONOREPO_MINHEAP_H

#include <stdio.h>
#include <stdlib.h>

// Node of the heap
typedef struct heapNode {
    int vertex;
    int distance;
} HeapNode;

// Structure of the Heap
typedef struct minHeap {
    int size;
    int capacity;
    int *pos;
    struct heapNode **array;
} MinHeap;

// Function prototypes
HeapNode *createHeapNode(int vertex, int distance);

MinHeap *createMinHeap(int capacity);

void swap(HeapNode **a, HeapNode **b);

void minHeapify(MinHeap *heap, int index);

int isEmpty(MinHeap *heap);

HeapNode *extractMin(MinHeap *heap);

void decreaseKey(MinHeap *heap, int v, int dist);

#endif //MONOREPO_MINHEAP_H