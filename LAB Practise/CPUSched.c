#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_burst_time; // Add remaining_burst_time
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int is_in_queue;
    bool is_completed;
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
            if(current_process->is_completed == false) {
                printf("\nProcessing PID: %d\n", current_process->pid);
                current_process->waiting_time = current_time - current_process->arrival_time;
                current_process->completion_time = current_time + current_process->burst_time;
                current_process->turnaround_time = current_process->waiting_time + current_process->burst_time;
                current_time += current_process->burst_time;
                completed++;
                current_process->is_completed = true;
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
            if(current_process->is_completed == false) {
                printf("\nProcessing PID: %d\n", current_process->pid);
                current_process->waiting_time = current_time - current_process->arrival_time;
                current_process->completion_time = current_time + current_process->burst_time;
                current_process->turnaround_time = current_process->waiting_time + current_process->burst_time;
                current_time += current_process->burst_time;
                current_process->is_completed = true;
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

void RoundRobin(Process processes[], int n, int time_quantum, Queue* q) {
    int current_time = 0;
    int completed = 0;
    int total_idle_time = 0;

    // Initially enqueue all processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && !processes[i].is_in_queue) {
            enqueue(q, &processes[i]);
            processes[i].is_in_queue = 1;
        }
    }

    while (completed < n) {
        if (isEmpty(q)) {
            current_time++;
            total_idle_time++;
            // Check for new arrivals during idle time
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && !processes[i].is_in_queue) {
                    enqueue(q, &processes[i]);
                    processes[i].is_in_queue = 1;
                }
            }
            continue;
        }

        Process* current_process = dequeue(q);
        printf("\nProcessing PID: %d at time %d\n", current_process->pid, current_time);

        int exec_time = (current_process->remaining_burst_time > time_quantum) ? time_quantum : current_process->remaining_burst_time;

        current_process->remaining_burst_time -= exec_time;
        current_time += exec_time;

        // Check for new arrivals during the execution of the current process
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time > (current_time - exec_time) && processes[i].arrival_time <= current_time && !processes[i].is_in_queue) {
                enqueue(q, &processes[i]);
                processes[i].is_in_queue = 1;
            }
        }

        if (current_process->remaining_burst_time == 0) {
            completed++;
            current_process->completion_time = current_time;
            current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
            current_process->is_completed = true;
            printf("Completed PID: %d at time %d\n", current_process->pid, current_time);
        } else {
            // Re-enqueue the process if it's not finished
            enqueue(q, current_process);
        }
    }

    printf("\n----- Round Robin Report (Time Quantum: %d) -----\n", time_quantum);
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].completion_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}


void resetProcesses(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completion_time = 0;
        processes[i].is_in_queue = 0;
        processes[i].is_completed = false;
        processes[i].remaining_burst_time = processes[i].burst_time;
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
        processes[i].remaining_burst_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completion_time = 0;
        processes[i].is_in_queue = 0;
        processes[i].is_completed = false;
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

    // Reset processes for Round Robin
    printf("\n--- Resetting processes for Round Robin ---\n");
    resetProcesses(processes, n);
    freeQueue(q);
    q = createQueue();

    // Call Round Robin Scheduling
    int time_quantum = 4;
    printf("\n--- Running Round Robin (Time Quantum: %d) ---\n", time_quantum);
    RoundRobin(processes, n, time_quantum, q);

    free(processes);
    freeQueue(q);
    return 0;
}