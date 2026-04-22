#include <stdio.h>
#include <math.h>

#define MAX 10

int main() {
    int n, i, j, t, time_limit;

    int Ci[MAX], Ti[MAX];
    int remaining[MAX], next_arrival[MAX];
    int priority[MAX], id[MAX];

    // Input
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        id[i] = i + 1;

        printf("\nTask %d:\n", i + 1);
        printf("Execution Time (Ci): ");
        scanf("%d", &Ci[i]);
        printf("Period (Ti): ");
        scanf("%d", &Ti[i]);

        remaining[i] = 0;
        next_arrival[i] = 0;
    }

    // Step 1: CPU Utilization
    float U = 0;
    for (i = 0; i < n; i++) {
        U += (float)Ci[i] / Ti[i];
    }
    printf("\nCPU Utilization (U) = %.3f\n", U);

    // Step 2: RMS Bound
    float bound = n * (pow(2, (1.0 / n)) - 1);
    printf("RMS Bound = %.3f\n", bound);

    // Step 3: Check schedulability
    if (U <= bound)
        printf("Schedulable using RMS\n");
    else
        printf("Not guaranteed schedulable\n");

    // Step 4: Sort by period (ascending)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (Ti[i] > Ti[j]) {
                // swap Ti
                int temp = Ti[i];
                Ti[i] = Ti[j];
                Ti[j] = temp;

                // swap Ci
                temp = Ci[i];
                Ci[i] = Ci[j];
                Ci[j] = temp;

                // swap id
                temp = id[i];
                id[i] = id[j];
                id[j] = temp;

                // swap remaining
                temp = remaining[i];
                remaining[i] = remaining[j];
                remaining[j] = temp;

                // swap next arrival
                temp = next_arrival[i];
                next_arrival[i] = next_arrival[j];
                next_arrival[j] = temp;
            }
        }
    }

    // Assign priorities
    printf("\nPriorities (Smaller Ti = Higher Priority):\n");
    for (i = 0; i < n; i++) {
        priority[i] = i + 1;
        printf("Task %d -> Priority %d\n", id[i], priority[i]);
    }

    // Simulation time
    printf("\nEnter simulation time: ");
    scanf("%d", &time_limit);

    printf("\nScheduling Timeline:\n");

    // Step 5: Scheduling Loop
    for (t = 0; t < time_limit; t++) {

        // Task arrivals
        for (i = 0; i < n; i++) {
            if (t == next_arrival[i]) {
                remaining[i] = Ci[i];
                next_arrival[i] += Ti[i];
            }
        }

        int selected = -1;

        // Select highest priority READY task
        for (i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                selected = i;
                break; // already sorted by priority
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d running\n", t, id[selected]);
            remaining[selected]--;
        } else {
            printf("Time %d: CPU Idle\n", t);
        }
    }

    return 0;
}