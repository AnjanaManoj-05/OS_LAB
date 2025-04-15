#include <stdio.h>
int count=0;
typedef struct {
int p_id;
int allocation[3];
int max[3];

int need[3];
}process;
int available[3];

void safety_algo(int p, int r, int available[r], process process[p]) {
    int work[r];
    int finish[p];
    int safe_sequence[p];
    int index = 0;

    for (int i = 0; i < r; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < p; i++) {
        finish[i] = 0;
    }

    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < r; j++) {
                    if (process[i].need[j] > work[j])
                        break;
                }

                if (j == r) {
                    for (int k = 0; k < r; k++) {
                        work[k] += process[i].allocation[k];
                    }

                    safe_sequence[index++] = process[i].p_id;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is **NOT** in a safe state.\n");
            return;
        }
    }

    printf("\nSystem is in a **SAFE** state.");
    printf("\nSafe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");
}




void main(){
int p,r;
printf("Enter number of processes:");
scanf("%d",&p);
process process[p];
printf("Enter the number of resources:");
scanf("%d",&r);
for(int i=0;i<p;i++){
        process[i].p_id=i;
    printf("Enter details for P%d\n",i);
    printf("Enter the allocation:");
    for(int j=0;j<r;j++){
    scanf("%d",&process[i].allocation[j]);
    }
    printf("Enter max:");
     for(int j=0;j<r;j++){
     scanf("%d",&process[i].max[j]);
     }
     for(int j=0;j<r;j++){
    process[i].need[j]=process[i].max[j]-process[i].allocation[j];
     }
}
printf("Enter available resources: ");
for(int j=0;j<r;j++){
scanf("%d",&available[j]);
}
safety_algo(p,r,available,process);
printf("\nProcess\tAllocation\tMax\t\tNeed\n");
for (int i = 0; i < p; i++) {
    printf("P%d\t", process[i].p_id);
    for (int j = 0; j < r; j++) {
        printf("%d ", process[i].allocation[j]);
    }
    printf("\t\t");
    for (int j = 0; j < r; j++) {
        printf("%d ", process[i].max[j]);
    }
    printf("\t\t");
    for (int j = 0; j < r; j++) {
        printf("%d ", process[i].need[j]);
    }
    printf("\n");
}

}
