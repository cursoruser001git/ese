#include <stdio.h>

int main() {
    // Hardcoded Process Data (PID, Arrival Time, Burst Time)
    int pid[] = {1, 2, 3, 4};
    int at[]  = {0, 2, 4, 5};
    int bt[]  = {7, 4, 1, 4};
    int n = 4;

    int remaining[10];
    int ft[10], tat[10], wt[10];
    int done[10] = {0};

    for (int i = 0; i < n; i++)
        remaining[i] = bt[i];

    int time = 0, completed = 0, prev = -1;

    // For Gantt Chart
    int gc_pid[100];
    int gc_time[100];
    int gc_index = 0;

    printf("=== SHORTEST JOB FIRST (PREEMPTIVE) ===\n\n");
    printf("Gantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int minRemaining = 9999;

        // Find the process with shortest remaining time among arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining[i] > 0 && remaining[i] < minRemaining) {
                minRemaining = remaining[i];
                idx = i;
            }
        }

        // If no process has arrived yet, move time forward
        if (idx == -1) {
            time++;
            continue;
        }

        // Record Gantt Chart segment if process changes
        if (idx != prev) {
            gc_pid[gc_index] = pid[idx];
            gc_time[gc_index] = time;
            gc_index++;
            printf("| P%d ", pid[idx]);
            prev = idx;
        }

        // Execute for one unit of time
        remaining[idx]--;
        time++;

        // If process completed
        if (remaining[idx] == 0) {
            ft[idx] = time;
            tat[idx] = ft[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            done[idx] = 1;
            completed++;
        }
    }

    // Record final time
    gc_time[gc_index] = time;
    printf("|\n");

    // Print time values under Gantt chart
    for (int i = 0; i <= gc_index; i++) {
        printf("%-5d", gc_time[i]);
    }
    printf("\n");

    // Print process summary table
    printf("\n-----------------------------------------------\n");
    printf("PID\tAT\tBT\tFT\tTAT\tWT\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ft[i], tat[i], wt[i]);
    }

    // Calculate averages
    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += tat[i];
        avgWT += wt[i];
    }
    avgTAT /= n;
    avgWT /= n;

    printf("-----------------------------------------------\n");
    printf("Average Turnaround Time = %.2f\n", avgTAT);
    printf("Average Waiting Time    = %.2f\n", avgWT);
    printf("-----------------------------------------------\n");

    return 0;
}