#include <stdio.h>

int main() {
    // Hardcoded process info: PID, Arrival Time, Burst Time, Priority
    int pid[] = {1, 2, 3, 4};
    int at[]  = {0, 1, 2, 3};
    int bt[]  = {5, 3, 8, 6};
    int prio[] = {2, 1, 4, 3}; // Lower number = higher priority
    int n = 4;

    int ft[10], tat[10], wt[10], done[10] = {0};
    int time = 0, completed = 0;

    // Gantt chart arrays
    int gc_pid[50];
    int gc_time[50];
    int gc_index = 0;

    printf("=== PRIORITY SCHEDULING (NON-PREEMPTIVE) ===\n\n");
    printf("Gantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int minPrio = 9999;

        // Find the process with highest priority among arrived
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && prio[i] < minPrio) {
                minPrio = prio[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        // Record Gantt chart info
        gc_pid[gc_index] = pid[idx];
        gc_time[gc_index] = time;
        gc_index++;
        printf("| P%d ", pid[idx]);

        // Execute process
        time += bt[idx];
        ft[idx] = time;
        tat[idx] = ft[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        done[idx] = 1;
        completed++;
    }

    // Final time for Gantt chart
    gc_time[gc_index] = time;
    printf("|\n");

    // Print times below Gantt chart
    for (int i = 0; i <= gc_index; i++)
        printf("%-5d", gc_time[i]);
    printf("\n");

    // Print process table
    printf("\n---------------------------------------------------\n");
    printf("PID\tAT\tBT\tPRIO\tFT\tTAT\tWT\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], prio[i], ft[i], tat[i], wt[i]);
    }

    // Calculate averages
    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += tat[i];
        avgWT += wt[i];
    }
    avgTAT /= n;
    avgWT /= n;

    printf("---------------------------------------------------\n");
    printf("Average Turnaround Time = %.2f\n", avgTAT);
    printf("Average Waiting Time    = %.2f\n", avgWT);
    printf("---------------------------------------------------\n");

    return 0;
}