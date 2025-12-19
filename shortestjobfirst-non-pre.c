#include <stdio.h>

int main() {
    // Hardcoded process info: ID, Arrival Time, Burst Time
    int pid[] = {1, 2, 3, 4, 5};
    int at[]  = {0, 1, 2, 3, 4};
    int bt[]  = {7, 4, 1, 4, 2};
    int n = 5;

    int ft[10], tat[10], wt[10], done[10] = {0};
    int time = 0, completed = 0;

    // Arrays for Gantt chart
    int gc_pid[50];
    int gc_time[50];
    int gc_index = 0;

    printf("=== SHORTEST JOB FIRST (NON-PREEMPTIVE) ===\n\n");
    printf("Gantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int minBurst = 9999;

        // Find process with shortest burst among arrived ones
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && bt[i] < minBurst) {
                minBurst = bt[i];
                idx = i;
            }
        }

        // If no process is available, move forward in time
        if (idx == -1) {
            time++;
            continue;
        }

        // Record process and time for Gantt chart
        gc_pid[gc_index] = pid[idx];
        gc_time[gc_index] = time;
        gc_index++;

        printf("| P%d ", pid[idx]);

        time += bt[idx];
        ft[idx] = time;
        tat[idx] = ft[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        done[idx] = 1;
        completed++;
    }

    // Final time after last process
    gc_time[gc_index] = time;

    printf("|\n");

    // Print times under Gantt chart
    for (int i = 0; i <= gc_index; i++) {
        printf("%-5d", gc_time[i]);
    }
    printf("\n");

    // Print process table
    printf("\n-----------------------------------------------\n");
    printf("PID\tAT\tBT\tFT\tTAT\tWT\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ft[i], tat[i], wt[i]);
    }

    // Averages
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