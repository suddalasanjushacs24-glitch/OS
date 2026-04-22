#include <stdio.h>

#define MAX 10
#define TIME_QUANTUM 10

int main() {
    int n, i, completed = 0;

    int burst[MAX], weight[MAX];
    int remaining[MAX];

    float total_weight = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Burst Time: ");
        scanf("%d", &burst[i]);

        printf("Weight: ");
        scanf("%d", &weight[i]);

        remaining[i] = burst[i];
        total_weight += weight[i];
    }

    printf("\nExecution:\n");

    // Scheduling loop
    while (completed < n) {

        for (i = 0; i < n; i++) {

            if (remaining[i] > 0) {

                // time slice calculation
                int slice = (weight[i] * TIME_QUANTUM) / total_weight;

                if (slice == 0) slice = 1; // minimum 1 unit

                printf("P%d runs for %d units\n", i + 1, slice);

                remaining[i] -= slice;

                if (remaining[i] <= 0) {
                    printf("P%d completed\n", i + 1);
                    completed++;
                    total_weight -= weight[i];
                }
            }
        }
    }

    return 0;
} 