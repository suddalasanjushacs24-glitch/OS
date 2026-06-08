#include <stdio.h>

#define MAX 10

typedef struct
{
    int pid;
    int arrival;
    int c;              // Capacity
    int d;              // Deadline
    int t;              // Period
    int remaining;
    int completed;
    int next_arrival;
    int abs_deadline;
} Task;

int main()
{
    Task task[MAX];
    int n, i, time;
    float u = 0;

    printf("Enter no of tasks: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        task[i].pid = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Capacity (Ci): ");
        scanf("%d", &task[i].c);

        printf("Period (Ti): ");
        scanf("%d", &task[i].t);

        printf("Deadline (Di): ");
        scanf("%d", &task[i].d);

        task[i].remaining = 0;
        task[i].completed = 0;
        task[i].next_arrival = 0;

        u += (float)task[i].c / task[i].t;
    }

    printf("\nCPU Utilisation = %.2f\n", u);

    if(u > 1)
        printf("Not feasible (deadline may be missed)\n");
    else
        printf("Feasible Schedule\n");

    printf("\nExecution Timeline:\n");

    for(time = 0; time < 20; time++)
    {
        for(i = 0; i < n; i++)
        {
            if(time == task[i].next_arrival)
            {
                task[i].remaining = task[i].c;
                task[i].abs_deadline = time + task[i].d;
                task[i].next_arrival += task[i].t;
            }
        }

        int idx = -1;
        int earliest_deadline = 9999;

        for(i = 0; i < n; i++)
        {
            if(task[i].remaining > 0)
            {
                if(task[i].abs_deadline < earliest_deadline)
                {
                    earliest_deadline = task[i].abs_deadline;
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            printf("Time %d -> Idle\n", time);
        }
        else
        {
            printf("Time %d -> Task %d (Deadline = %d)\n",
                   time,
                   task[idx].pid,
                   task[idx].abs_deadline);

            task[idx].remaining--;
        }
    }

    return 0;
}
