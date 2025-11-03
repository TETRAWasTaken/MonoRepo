#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int is_in_queue;
} Process;

typedef struct queueNode{
    Process* process;
    struct queueNode* next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL){
        printf("Memory allocation failed for queue.\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, Process* process) {
    if(q == NULL){
        printf("Queue is not initialized.\n");
        return;
    }
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if(newNode == NULL){
        printf("Memory allocation failed for new node.\n");
        return;
    }
    newNode->process = process;
    newNode->next = NULL;

    if(q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Process* dequeue(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }
    QueueNode* temp = q->front;
    Process* process = temp->process;
    q->front = q->front->next;

    if(q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return process;
}

Process *mindequeue(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }

    QueueNode *current = q->front;
    QueueNode *minNode = current;
    QueueNode *prev = NULL;
    QueueNode *minPrev = NULL;

    while(current != NULL) {
        if(current->process->burst_time < minNode->process->burst_time) {
            minNode = current;
            minPrev = prev;
        }
        prev = current;
        current = current->next;
    }

    // Remove minNode from the queue
    if(minPrev == NULL) { // minNode is the front node
        q->front = minNode->next;
        if(q->front == NULL) {
            q->rear = NULL; // Queue is now empty
        }
    } else {
        minPrev->next = minNode->next;
        if(minNode == q->rear) {
            q->rear = minPrev; // Update rear if needed
        }
    }

    Process* process = minNode->process;
    free(minNode);
    return process;
}

void freeQueue(Queue* q) {
    if(q == NULL) return;
    QueueNode* current = q->front;
    QueueNode* nextNode;
    while(current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(q);
}

void FCFS(Process processes[], int n, Queue* q){
    int current_time = 0;
    int completed = 0;

    while(completed < n) {
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && processes[i].completion_time == 0 && !processes[i].is_in_queue) {
                printf("Enqueuing PID: %d at time %d\n", processes[i].pid, current_time);
                enqueue(q, &processes[i]);
                processes[i].is_in_queue = 1; // Mark as in queue
            }
        }

        if(!isEmpty(q)) {
            Process* current_process = dequeue(q);
            if(current_process->completion_time == 0) {
                printf("\nProcessing PID: %d\n", current_process->pid);
                current_process->waiting_time = current_time - current_process->arrival_time;
                current_process->completion_time = current_time + current_process->burst_time;
                current_process->turnaround_time = current_process->waiting_time + current_process->burst_time;
                current_time += current_process->burst_time;
                completed++;
                printf("Completed PID: %d at time %d\n", current_process->pid, current_time);
            }
        } else {
            current_time++;
        }
    }

    printf("----- FCFS REPORT -----\n");
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].completion_time);
    }
}

void SJF(Process processes[], int n, Queue* q) {
    int current_time = 0;
    int completed = 0;

    while(completed < n) {
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && processes[i].completion_time == 0 && !processes[i].is_in_queue) {
                printf("Enqueuing PID: %d at time %d\n", processes[i].pid, current_time);
                enqueue(q, &processes[i]);
                processes[i].is_in_queue = 1; // Mark as in queue
            }
        }

        if(!isEmpty(q)) {
            Process* current_process = mindequeue(q);
            if(current_process->completion_time == 0) {
                printf("\nProcessing PID: %d\n", current_process->pid);
                current_process->waiting_time = current_time - current_process->arrival_time;
                current_process->completion_time = current_time + current_process->burst_time;
                current_process->turnaround_time = current_process->waiting_time + current_process->burst_time;
                current_time += current_process->burst_time;
                completed++;
                printf("Completed PID: %d at time %d\n", current_process->pid, current_time);
            }
        } else {
            current_time++;
        }
    }

    printf("----- SJF REPORT -----\n");
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].completion_time);
    }
}

void resetProcesses(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completion_time = 0;
        processes[i].is_in_queue = 0;
    }
}

int main() {
    Queue *q = createQueue();
    if(q == NULL) {
        return -1;
    }
    int n = 5;
    Process *processes = (Process*)malloc(n * sizeof(Process));

    // Generate 5 random processes
    srand(time(NULL));
    printf("Generated Processes:\n");
    printf("PID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].arrival_time = rand() % 10;
        processes[i].burst_time = (rand() % 10) + 1;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completion_time = 0;
        processes[i].is_in_queue = 0;
        printf("%d\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time);
    }
    
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Call FCFS Scheduling
    printf("\n--- Running FCFS ---\n");
    FCFS(processes, n, q);

    // Reset processes for SJF
    printf("\n--- Resetting processes for SJF ---\n");
    resetProcesses(processes, n);
    freeQueue(q);
    q = createQueue();


    // Call SJF Scheduling
    printf("\n--- Running SJF ---\n");
    SJF(processes, n, q);

    free(processes);
    freeQueue(q);
    return 0;
}