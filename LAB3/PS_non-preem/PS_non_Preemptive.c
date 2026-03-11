#include <stdio.h>

int main(){
    int n, bt[20], wt[20], tat[20], at[20], ct[20], pr[20], pid[20];
    int i, j, temp;
    float twt=0.0, ttat=0.0, awt, att;

    printf("Enter no. of processes: ");
    scanf("%d",&n);

    // Input
    for(i=0;i<n;i++){
        pid[i]=i+1;

        printf("Enter arrival time for process %d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter burst time for process %d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Enter priority for process %d: ",i+1);
        scanf("%d",&pr[i]);
    }

    // Sort by arrival time
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(at[i] > at[j]){

                temp=at[i]; at[i]=at[j]; at[j]=temp;
                temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
                temp=pr[i]; pr[i]=pr[j]; pr[j]=temp;
                temp=pid[i]; pid[i]=pid[j]; pid[j]=temp;
            }
        }
    }

    int time=0, completed=0, highest, index;

    while(completed < n){

        highest = 9999;
        index = -1;

        for(i=0;i<n;i++){
            if(at[i] <= time && ct[i]==0){
                if(pr[i] < highest){
                    highest = pr[i];
                    index = i;
                }
            }
        }

        if(index != -1){
            ct[index] = time + bt[index];
            wt[index] = time - at[index];

            if(wt[index] < 0)
                wt[index] = 0;

            tat[index] = wt[index] + bt[index];

            time = ct[index];
            completed++;
        }
        else{
            time++;
        }
    }

    // Average
    for(i=0;i<n;i++){
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt/n;
    att = ttat/n;

    printf("\nPROCESS\tAT\tBT\tPR\tCT\tTAT\tWT");

    for(i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
        pid[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f",awt);
    printf("\nAverage Turnaround Time = %.2f\n",att);

    return 0;
}