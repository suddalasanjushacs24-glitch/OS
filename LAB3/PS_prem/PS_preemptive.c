#include <stdio.h>

int main(){
    int n, bt[20], wt[20], tat[20], at[20], ct[20], pr[20];
    int rt[20], response[20], pid[20];
    int i, time=0, completed=0, index;
    float twt=0.0, ttat=0.0, trt=0.0, awt, att, art;

    printf("Enter no. of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        pid[i]=i+1;

        printf("Enter arrival time for process %d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter burst time for process %d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Enter priority for process %d: ",i+1);
        scanf("%d",&pr[i]);

        rt[i]=bt[i];
        response[i] = -1;   // mark not started
    }

    while(completed != n){

        index = -1;

        for(i=0;i<n;i++){
            if(at[i] <= time && rt[i] > 0){
                if(index == -1 || pr[i] < pr[index]){
                    index = i;
                }
            }
        }

        if(index == -1){
            time++;
            continue;
        }

        // first time execution
        if(response[index] == -1){
            response[index] = time - at[index];
        }

        rt[index]--;
        time++;

        if(rt[index] == 0){
            completed++;

            ct[index] = time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
        }
    }

    for(i=0;i<n;i++){
        twt += wt[i];
        ttat += tat[i];
        trt += response[i];
    }

    awt = twt/n;
    att = ttat/n;
    art = trt/n;

    printf("\nPROCESS\tAT\tBT\tPR\tCT\tTAT\tWT\tRT");

    for(i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
        pid[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i],response[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f",awt);
    printf("\nAverage Turnaround Time = %.2f",att);
    printf("\nAverage Response Time = %.2f\n",art);

    return 0;
}