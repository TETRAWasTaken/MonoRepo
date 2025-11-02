//
// Created by Anshumaan soni on 10/29/25.
//

#include "MinHeap.h"

// Function to create a new node
HeapNode* createHeapNode(int vertex, int distance) {
    HeapNode *node = (HeapNode*)malloc(sizeof(HeapNode));
    node->vertex = vertex;
    node->distance = distance;
    return node;
}

// Function to create a Min Heap of a given capacity
MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->array = (HeapNode**)malloc(capacity * sizeof(HeapNode*));
    return heap;
}

// Function to swap to nodes of a min heap
void swap(HeapNode** a, HeapNode** b) {
    HeapNode *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify at the given index
void minHeapify(MinHeap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    if (left < heap->size && heap->array[left]->distance < heap->array[smallest]->distance) {
        smallest = left;
    }
    if (right < heap->size && heap->array[right]->distance < heap->array[smallest]->distance) {
        smallest = right;
    }
    if (smallest != index) {
        HeapNode *temp = heap->array[smallest];
        HeapNode *temp2 = heap->array[index];

        heap->pos[temp->vertex] = index;
        heap->pos[temp2->vertex] = smallest;

        swap(&heap->array[smallest], &heap->array[index]);
        minHeapify(heap, smallest);
    }
}

// Function to check if the given minHeap is empty
int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

// Function to extract the minimum distance node from the heap
HeapNode* extractMin(MinHeap* heap) {
    if (isEmpty(heap)) {
        printf("Heap is empty. Cannot extract.\n");
        return NULL;
    }
    HeapNode *min = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->pos[min->vertex] = heap->size - 1;
    heap->size--;
    minHeapify(heap, 0);
    return min;
}

// Function to decrease dist value of a given vertex v
void decreaseKey(MinHeap* heap, int v, int dist) {
    int index = heap->pos[v];
    heap->array[index]->distance = dist;
    while (index > 0 && heap->array[index]->distance < heap->array[(index - 1) / 2]->distance) {
        HeapNode *temp = heap->array[index];
        HeapNode *temp2 = heap->array[(index - 1) / 2];
        heap->pos[temp->vertex] = (index - 1) / 2;
        heap->pos[temp2->vertex] = index;
        swap(&heap->array[(index - 1) / 2], &heap->array[index]);
        index = (index - 1) / 2;
    }
}

