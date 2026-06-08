#include <stdio.h>

#define MAX 10
#define TIME_QUANTUM 10

typedef struct
{
    int pid;
    int capacity;
    int period;
    int weight;
    int remaining;
    int next_arrival;
} Task;

int main()
{
    Task t[MAX];

    int n, i, time;
    int total_weight = 0;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        t[i].pid = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Capacity (Ci): ");
        scanf("%d", &t[i].capacity);

        printf("Period (Ti): ");
        scanf("%d", &t[i].period);

        printf("Weight (Wi): ");
        scanf("%d", &t[i].weight);

        t[i].remaining = 0;
        t[i].next_arrival = 0;

        total_weight += t[i].weight;
    }

    printf("\nExecution Timeline:\n");

    for(time = 0; time < 20; time++)
    {
        for(i = 0; i < n; i++)
        {
            if(time == t[i].next_arrival)
            {
                t[i].remaining = t[i].capacity;
                t[i].next_arrival += t[i].period;
            }
        }

        int idx = -1;
        int max_share = -1;

        for(i = 0; i < n; i++)
        {
            if(t[i].remaining > 0)
            {
                int share =
                    (t[i].weight * TIME_QUANTUM) / total_weight;

                if(share > max_share)
                {
                    max_share = share;
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
            int exec;

            if(t[idx].remaining < max_share)
                exec = t[idx].remaining;
            else
                exec = max_share;

            printf("Time %d -> Task %d (%d units)\n",
                   time,
                   t[idx].pid,
                   exec);

            t[idx].remaining -= exec;

            time += exec - 1;
        }
    }

    return 0;
}
