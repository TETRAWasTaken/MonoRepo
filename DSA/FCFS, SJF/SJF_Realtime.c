#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    int arrival;
    int burst;
    int remaining;
    int start;       // -1 if not started yet
    int completion;
    int turnaround;
    int waiting;
    int response;
} Process;

typedef struct {
    int pid;
    int start;
    int end;
} Segment;

int main(void) {
    int n;
    printf("Number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    Process *p = calloc(n, sizeof(Process));
    if (!p) return 1;

    for (int i = 0; i < n; ++i) {
        int at, bt;
        printf("Process %d - arrival burst: ", i+1);
        if (scanf("%d %d", &at, &bt) != 2) { free(p); return 0; }
        if (at < 0) at = 0;
        if (bt <= 0) bt = 1;
        p[i].id = i + 1;
        p[i].arrival = at;
        p[i].burst = bt;
        p[i].remaining = bt;
        p[i].start = -1;
        p[i].completion = 0;
    }

    int completed = 0;
    int time = 0;
    // find earliest arrival to start at
    int earliest = INT_MAX;
    for (int i = 0; i < n; ++i) if (p[i].arrival < earliest) earliest = p[i].arrival;
    if (earliest > 0) time = earliest;

    Segment *gantt = calloc(2 * n + 10, sizeof(Segment)); // upper bound segments
    int seg_count = 0;
    int last_pid = -1;

    while (completed < n) {
        int idx = -1;
        int min_rem = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (p[i].remaining > 0 && p[i].arrival <= time) {
                if (p[i].remaining < min_rem || (p[i].remaining == min_rem && p[i].arrival < p[idx].arrival)) {
                    min_rem = p[i].remaining;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // idle until next arrival
            int next_arr = INT_MAX;
            for (int i = 0; i < n; ++i) if (p[i].remaining > 0 && p[i].arrival > time && p[i].arrival < next_arr) next_arr = p[i].arrival;
            if (next_arr == INT_MAX) break;
            // record idle segment
            if (last_pid != 0) {
                gantt[seg_count].pid = 0;
                gantt[seg_count].start = time;
                gantt[seg_count].end = next_arr;
                seg_count++;
                last_pid = 0;
            } else {
                gantt[seg_count-1].end = next_arr;
            }
            time = next_arr;
            continue;
        }

        // start if first time
        if (p[idx].start == -1) p[idx].start = time;

        // record gantt
        if (last_pid != p[idx].id) {
            gantt[seg_count].pid = p[idx].id;
            gantt[seg_count].start = time;
            gantt[seg_count].end = time + 1;
            seg_count++;
            last_pid = p[idx].id;
        } else {
            gantt[seg_count-1].end = time + 1;
        }

        // execute for 1 time unit (preemptive simulation)
        p[idx].remaining -= 1;
        time += 1;

        if (p[idx].remaining == 0) {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].response = p[idx].start - p[idx].arrival;
            completed++;
        }
    }

    // output Gantt chart
    printf("\nGantt chart:\n");
    for (int i = 0; i < seg_count; ++i) {
        if (gantt[i].pid == 0)
            printf("| Idle (%d-%d) ", gantt[i].start, gantt[i].end);
        else
            printf("| P%d (%d-%d) ", gantt[i].pid, gantt[i].start, gantt[i].end);
    }
    printf("|\n");

    // results table
    double total_wt = 0, total_tat = 0, total_rt = 0;
    printf("\nPID\tArrival\tBurst\tStart\tCompletion\tTurnaround\tWaiting\tResponse\n");
    for (int i = 0; i < n; ++i) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               p[i].id, p[i].arrival, p[i].burst, p[i].start,
               p[i].completion, p[i].turnaround, p[i].waiting, p[i].response);
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
        total_rt += p[i].response;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Response Time: %.2f\n", total_rt / n);

    free(p);
    free(gantt);
    return 0;
}