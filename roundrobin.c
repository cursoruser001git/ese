#include <stdio.h>

int main() {
    // Hardcoded process data (Process ID, Arrival Time, Burst Time)
    int pid[] = {1, 2, 3, 4};
    int at[]  = {0, 1, 2, 3};
    int bt[]  = {5, 4, 2, 1};
    int n = 4;
    int tq = 2;  // Time Quantum

    int ft[10], tat[10], wt[10], rem[10];
    int done[10] = {0};

    for (int i = 0; i < n; i++)
        rem[i] = bt[i];

    // Gantt chart arrays
    int gc_pid[100];
    int gc_time[100];
    int gc_index = 0;

    int time = 0, completed = 0;

    printf("=== ROUND ROBIN SCHEDULING ===\n\n");
    printf("Time Quantum = %d\n", tq);
    printf("\nGantt Chart:\n");

    while (completed < n) {
        int progress = 0;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0) {
                progress = 1;
                gc_pid[gc_index] = pid[i];
                gc_time[gc_index] = time;
                gc_index++;
                printf("| P%d ", pid[i]);

                if (rem[i] > tq) {
                    rem[i] -= tq;
                    time += tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    ft[i] = time;
                    tat[i] = ft[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    done[i] = 1;
                    completed++;
                }
            }
        }
        if (!progress)
            time++;
    }

    // Final time for Gantt chart
    gc_time[gc_index] = time;
    printf("|\n");

    // Print time values below chart
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