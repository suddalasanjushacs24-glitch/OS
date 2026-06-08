#include<stdio.h>


int main(){
    int frames, n, i, j, k;
    int ref[50], temp[10];
    int pos, faults;


    printf("Enter the number of Frames: ");
    scanf("%d", &frames);


    printf("Enter the length of reference string: ");
    scanf("%d", &n);


    printf("Enter the reference string: ");
    for(i=0;i<n;i++)
        scanf("%d",&ref[i]);


    // ---------- FIFO ----------
    printf("\nFIFO Page Replacement Process:\n");
    for(i=0;i<frames;i++)
        temp[i] = -1;


    faults = 0;
    pos = 0;


    for(i=0;i<n;i++){
        int found = 0;
        for(j=0;j<frames;j++){
            if(temp[j] == ref[i]){
                found = 1;
                break;
            }
        }


        if(found == 0){
            temp[pos] = ref[i];
            pos = (pos + 1) % frames;
            faults++;


            printf("PF No. %d: ", faults);
            for(j=0;j<frames;j++){
                if(temp[j] == -1)
                    printf("- ");
                else
                    printf("%d ", temp[j]);
            }
            printf("\n");
        }
    }


    printf("FIFO Page Faults: %d\n", faults);


    // ---------- LRU ----------
    printf("\nLRU Page Replacement Process:\n");


    for(i=0;i<frames;i++)
        temp[i] = -1;


    faults = 0;


    for(i=0;i<n;i++){
        int found = 0;
        for(j=0;j<frames;j++){
            if(temp[j] == ref[i]){
                found = 1;
                break;
            }
        }


        if(found == 0){
            int least, min = 999;
            for(j=0;j<frames;j++){
                int flag = 0;
                for(k=i-1;k>=0;k--){
                    if(temp[j] == ref[k]){
                        flag = 1;
                        if(k < min){
                            min = k;
                            least = j;
                        }
                        break;
                    }
                }


                if(flag == 0){
                    least = j;
                    break;
                }
            }


            temp[least] = ref[i];
            faults++;


            printf("PF No. %d: ", faults);
            for(j=0;j<frames;j++){
                if(temp[j] == -1)
                    printf("- ");
                else
                    printf("%d ", temp[j]);
            }
            printf("\n");
        }
    }


    printf("LRU Page Faults: %d\n", faults);


    // ---------- Optimal ----------
    printf("\nOptimal Page Replacement Process:\n");
    for(i=0;i<frames;i++)
        temp[i] = -1;


    faults = 0;


    for(i=0;i<n;i++){
        int found = 0;
        for(j=0;j<frames;j++){
            if(temp[j] == ref[i]){
                found = 1;
                break;
            }
        }


        if(found == 0){
            int farthest = -1, index = -1;


            for(j=0;j<frames;j++){
                int nextUse = 999;
                for(k=i+1;k<n;k++){
                    if(temp[j] == ref[k]){
                        nextUse = k;
                        break;
                    }
                }


                if(nextUse > farthest){
                    farthest = nextUse;
                    index = j;
                }
            }


            temp[index] = ref[i];
            faults++;


            printf("PF No. %d: ", faults);


            for(j=0;j<frames;j++){
                if(temp[j] == -1)
                    printf("- ");
                else
                    printf("%d ", temp[j]);
            }
            printf("\n");
        }
    }


    printf("Optimal Page Faults: %d\n", faults);
    return 0;
}
