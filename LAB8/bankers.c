#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for P%d\n", i);

        printf("Enter allocation: ");
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter max: ");
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nEnter Available Resources: ");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    int request[n];

    printf("\nEnter New Request Details\n");
    printf("Enter PID: ");
    int pid;
    scanf("%d", &pid);

    printf("Enter Request for Resources: ");
    for(i = 0; i < m; i++)
        scanf("%d", &request[i]);

    int possible = 1;

    for(i = 0; i < m; i++)
    {
        if(request[i] > need[pid][i] ||
           request[i] > avail[i])
        {
            possible = 0;
            break;
        }
    }

    if(possible)
    {
        for(i = 0; i < m; i++)
        {
            avail[i] -= request[i];
            alloc[pid][i] += request[i];
            need[pid][i] -= request[i];
        }
    }
    else
    {
        printf("\nResources not available, process must wait\n");
        return 0;
    }

    int work[m], finish[n], safeSeq[n];

    for(i = 0; i < m; i++)
        work[i] = avail[i];

    for(i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    printf("\nP%d is visited (", i);

                    for(k = 0; k < m; k++)
                    {
                        work[k] += alloc[i][k];
                        printf("%d", work[k]);

                        if(k != m - 1)
                            printf(" ");
                    }

                    printf(")");

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n)
    {
        printf("\n\nSystem is in safe state\n");
        printf("The safe sequence is: ");

        for(i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if(i != n - 1)
                printf(" -> ");
        }
    }
    else
    {
        printf("\nSystem is not in safe state\n");
    }

    printf("\n\nProcess\tAllocation\tMax\tNeed\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t", i);

        for(j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);

        printf("\t");

        for(j = 0; j < m; j++)
            printf("%d ", max[i][j]);

        printf("\t");

        for(j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    return 0;
}
