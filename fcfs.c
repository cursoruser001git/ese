#include <stdio.h>

int main() {
    // Hardcoded process data (ID, Arrival Time, Burst Time)
    int pid[] = {1, 2, 3, 4};
    int at[]  = {0, 2, 4, 6};
    int bt[]  = {5, 3, 8, 6};
    int n = 4;

    int ft[10], tat[10], wt[10];
    int currentTime = 0;

    printf("=== FIRST COME FIRST SERVE SCHEDULING ===\n\n");

    printf("Process Execution Order (Gantt Chart):\n");

    // Draw Gantt chart and calculate all times
    for (int i = 0; i < n; i++) {
        if (currentTime < at[i]) 
            currentTime = at[i];

        printf("| P%d ", pid[i]);

        currentTime += bt[i];
        ft[i] = currentTime;
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("|\n");

    // Print time labels below Gantt chart
    currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < at[i])
            currentTime = at[i];
        printf("%d    ", currentTime);
        currentTime += bt[i];
    }
    printf("%d\n", currentTime);

    // Detailed table output
    printf("\n---------------------------------------------\n");
    printf("PID\tAT\tBT\tFT\tTAT\tWT\n");
    printf("---------------------------------------------\n");

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

    printf("---------------------------------------------\n");
    printf("Average Turnaround Time = %.2f\n", avgTAT);
    printf("Average Waiting Time    = %.2f\n", avgWT);
    printf("---------------------------------------------\n");

    return 0;
}