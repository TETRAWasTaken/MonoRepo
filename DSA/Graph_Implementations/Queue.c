#include "Queue.h"

// Function to create a new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed for queue.\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// Function to check if the queue is empty
bool isempty(Queue* q) {
    if (q->front == NULL) {
        return true;
    }
    return false;
}

// Function to add an element to the rear of the queue
void enqueue(Queue* q, int value) {
    if (q == NULL) {
        printf("Queue is not initialized.\n");
        return;
    }
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed for new node.\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;


    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Function to remove and return the front element of the queue
int dequeue(Queue* q) {
    if (isempty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Indicating that the queue is empty
    }
    QueueNode* temp = q->front;
    int dequeuedValue = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return dequeuedValue;
}

// Function to get the front element of the queue without removing it
int front(Queue* q) {
    if (isempty(q)) {
        printf("Queue is empty, No front element. \n");
        return -1; // Indicating that the queue is empty
    }
    return q->front->data;
}

// Function to display the queue
void display(Queue* q) {
    if (isempty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    QueueNode* temp = q->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf(" <- %d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the queue
void freeQueue(Queue* q) {
    if (q == NULL) return;
    QueueNode* current = q->front;
    while (current != NULL) {
        QueueNode* next = current->next;
        free(current);
        current = next;
    }
    free(q);
}