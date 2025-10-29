#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Structure of a process
typedef struct {
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to sort processes by arrival time
int compareArrivalTime(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrival_time - p2->arrival_time;
}

// Function to Simulate the FCFS scheduling algorithm
void simulateFCFS(Process processes[], int n) {
    int current_time = 0;
    int process_index = 0;

    // Creating a Copy of all the processes
    Process* temp_processes = (Process *)malloc(n * sizeof(Process));
    if (!temp_processes) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(temp_processes, processes, n * sizeof(Process));


    printf("Starting FCFS Simulation...\n");
    while(completed_processes < n){
        printf("Current Time: %d\n", current_time);

        int is_cpu_idle = 1;
        for(int i = 0; i < n; i++) {
            if(temp_processes[i].remaining_time > 0 && temp_processes[i].arrival_time <= current_time){
                if(is_cpu_idle){
                    is_cpu_idle = 0;

                    if(temp_processes[i].remaining_time == temp_processes[i].burst_time){
                        printf("Process %d is starting execution.\n", temp_processes[i].id);
                    }
                    temp_processes[i].remaining_time--;
                    printf("Process %d is executing. Remaining time: %d\n", temp_processes[i].id, temp_processes[i].remaining_time);
                    if(temp_processes[i].remaining_time == 0){
                        completed_processes++;
                        temp_processes[i].turnaround_time = current_time + 1 - temp_processes[i].arrival_time;
                        temp_processes[i].waiting_time = temp_processes[i].turnaround_time - temp_processes[i].burst_time;
                        printf("Process %d has completed execution.\n", temp_processes[i].id);
                    }
                }
            }
        }
        if(is_cpu_idle){
            printf("CPU is idle.\n");
        }
        current_time++;
        sleep(1); // Simulate real-time passage
    }
    printf("FCFS Simulation Completed.\n");

    // Copy completion times back to original array
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(processes[i].id == temp_processes[j].id) {
                processes[i].waiting_time = temp_processes[j].waiting_time;
                processes[i].turnaround_time = temp_processes[j].turnaround_time;
                break;
            }
        }
    }
    free(temp_processes);
}


// Function to calculate and print average waiting and turnaround times
void calculateAndPrintAverages(Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;  

    for (size_t i = 0; i < count; i++){
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time

        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int
