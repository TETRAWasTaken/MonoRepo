#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct circularQueue {
    int front;           // Index of front element
    int rear;            // Index of rear element
    int size;
    unsigned capacity;
    int* array;          // Array for circular queue
} CircularQueue;

typedef struct process {
    int pid; // Process ID
    int bt;  // Burst Time
    int rt;  // Remaining Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
} Process;

CircularQueue* createQueue(unsigned capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

void destroyQueue(CircularQueue* queue) {
    if (queue) {
        if (queue->array) {
            free(queue->array);
        }
        free(queue);
    }
}

void enqueue(CircularQueue* queue, int item) {
    if (queue->size == queue->capacity)
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

void dequeue(CircularQueue* queue) {
    if (queue->size == 0)
        return;
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
}

int front(CircularQueue* queue) {
    if (queue->size == 0)
        return -1;
    return queue->array[queue->front];
}

int isEmpty(CircularQueue* queue) {
    return (queue->size == 0);
}

void turnaroundTime(Process* p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i]->tat = p[i]->bt + p[i]->wt;
    }
}

void RoundRobin(Process **processes, int n, int timeQuantum) {
    int time = 0; // Current time
    CircularQueue* queue = createQueue(n);
    int completed = 0; // Number of completed processes

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i]->rt > 0) {
                enqueue(queue, i);
            }
        }

        while (!isEmpty(queue)) {
            int idx = front(queue);
            dequeue(queue);

            if (processes[idx]->rt > timeQuantum) {
                time += timeQuantum;
                processes[idx]->rt -= timeQuantum;
            } else {
                time += processes[idx]->rt;
                processes[idx]->wt = time - processes[idx]->bt;
                processes[idx]->rt = 0;
                completed++;
            }
        }
    }

    destroyQueue(queue);
}

int main(){
    Process **processes = (Process **)malloc(5 * sizeof(Process *));
    
    for (int i = 0; i < 5; i++) {
        processes[i] = (Process *)malloc(sizeof(Process));
        processes[i]->pid = i + 1;
        processes[i]->wt = 0;
        processes[i]->tat = 0;

        printf("Enter burst time for process %d: ", processes[i]->pid);
        scanf("%d", &processes[i]->bt);
        processes[i]->rt = processes[i]->bt;
    }

    int timeQuantum;
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    RoundRobin(processes, 5, timeQuantum);
    turnaroundTime(processes, 5);

    for (int i = 0; i < 5; i++) {
        printf("Process %d: WT = %d, TAT = %d\n", processes[i]->pid, processes[i]->wt, processes[i]->tat);
        free(processes[i]);
    }
    free(processes);
    return 0;
}