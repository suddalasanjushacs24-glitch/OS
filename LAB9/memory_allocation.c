#include<stdio.h>


int main(){


    int b[10], p[10], temp[10];
    int nb, np, i, j, best, worst;


    printf("Enter number of memory blocks: ")
    scanf("%d",&nb);


    printf("Enter sizes of %d memory blocks:\n", nb);
    for(i=0;i<nb;i++)
        scanf("%d",&b[i]);


    printf("\nEnter number of processes: ");
    scanf("%d",&np);


    printf("Enter sizes of %d processes:\n", np);
    for(i=0;i<np;i++)
        scanf("%d",&p[i]);


    // ---------- First Fit ----------
    for(i=0;i<nb;i++)
        temp[i]=b[i];


    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");


    for(i=0;i<np;i++){
        for(j=0;j<nb;j++){
            if(temp[j] >= p[i]){
                printf("%d\t\t%d\t\t%d\n", i+1, p[i], j+1);
                temp[j] -= p[i];
                break;
            }
        }


        if(j == nb)
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, p[i]);
    }


    // ---------- Best Fit ----------
    for(i=0;i<nb;i++)
        temp[i]=b[i];


    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(i=0;i<np;i++){
        best = -1;
        for(j=0;j<nb;j++){
            if(temp[j] >= p[i]){
                if(best == -1 || temp[j] < temp[best])
                    best = j;
            }
        }


        if(best != -1){
            printf("%d\t\t%d\t\t%d\n", i+1, p[i], best+1);
            temp[best] -= p[i];
        }
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, p[i]);
    }


    // ---------- Worst Fit ----------
    for(i=0;i<nb;i++)
        temp[i]=b[i];


    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");


    for(i=0;i<np;i++){
        worst = -1;
        for(j=0;j<nb;j++){
            if(temp[j] >= p[i]){
                if(worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }
        }


        if(worst != -1){
            printf("%d\t\t%d\t\t%d\n", i+1, p[i], worst+1);
            temp[worst] -= p[i];
        }
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, p[i]);
    }
    return 0;
}
