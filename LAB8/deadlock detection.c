#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m];
    int request[n][m];
    int available[m];

    printf("\nEnter Allocation Matrix:\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for(j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("\nEnter Request Matrix:\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);
    }

    printf("\nEnter Available Resources: ");

    for(i = 0; i < m; i++)
        scanf("%d", &available[i]);

    int work[m], finish[n], sequence[n];

    for(i = 0; i < m; i++)
        work[i] = available[i];

    for(i = 0; i < n; i++)
    {
        int flag = 0;

        for(j = 0; j < m; j++)
        {
            if(allocation[i][j] != 0)
            {
                flag = 1;
                break;
            }
        }

        if(flag)
            finish[i] = 0;
        else
            finish[i] = 1;
    }

    int count = 0;

    while(1)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    for(k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    sequence[count++] = i;
                    found = 1;

                    printf("\nP%d is executed (", i);

                    for(k = 0; k < m; k++)
                    {
                        printf("%d", work[k]);

                        if(k != m - 1)
                            printf(" ");
                    }

                    printf(")");
                }
            }
        }

        if(found == 0)
            break;
    }

    int deadlock = 0;

    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            deadlock = 1;
            break;
        }
    }

    if(deadlock)
    {
        printf("\n\nSystem is in deadlock state\n");
        printf("Deadlocked processes are: ");

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
                printf("P%d ", i);
        }
    }
    else
    {
        printf("\n\nSystem is not in deadlock state\n");
        printf("Safe sequence is: ");

        for(i = 0; i < count; i++)
            printf("P%d ", sequence[i]);
    }

    return 0;
}
