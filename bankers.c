#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to display a matrix
void displayMatrix(const char* name, int matrix[][R], int rows, int cols) {
    printf("\n%s Matrix:\n", name);
    for (int i = 0; i < rows; i++) {
        printf("P%d |", i);
        for (int j = 0; j < cols; j++) {
            printf(" %d", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to display an array
void displayArray(const char* name, int arr[], int size) {
    printf("\n%s:\n", name);
    printf("|");
    for (int i = 0; i < size; i++) {
        printf(" %d", arr[i]);
    }
    printf(" |\n");
}


// Function to find a safe sequence
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    bool finish[P];
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }

    int safeSeq[P];
    int count = 0;

    // Need matrix
    int need[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    // Display all matrices and arrays
    printf("--- Banker's Safety Algorithm ---");
    displayMatrix("Allocation", allot, P, R);
    displayMatrix("Max", max, P, R);
    displayArray("Available", avail, R);
    displayMatrix("Need", need, P, R);


    printf("\nExecuting Safety Algorithm Steps:\n");
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == false) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                if (j == R) {
                    printf("  -> Process P%d can execute. Resources (%d,%d,%d) are added to Work (%d,%d,%d).\n",
                           p, allot[p][0], allot[p][1], allot[p][2], work[0], work[1], work[2]);
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                    printf("     New Work: (%d,%d,%d)\n", work[0], work[1], work[2]);
                }
            }
        }

        if (found == false) {
            printf("\nSystem is not in a safe state. No process can be found to satisfy its need with current available resources.\n");
            return false;
        }
    }

    printf("\nSystem is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d", safeSeq[i]);
        if (i < P - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {3, 3, 2};

    // Maximum R instances that can be requested by a process
    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources allocated to processes
    int allot[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    isSafe(processes, avail, max, allot);

    return 0;
}