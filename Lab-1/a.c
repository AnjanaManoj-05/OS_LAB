#include <stdio.h>
//FCFS
int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n], wt[n], tat[n],wtavg,tatavg;
    float total_wt = 0, total_tat = 0;


    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        processes[i] = i + 1;
    }


     wt[0] = 0;

    for (i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];

    }


    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }


    printf("\nProcesses \t BurstTime \t TurnaroundTime \t WaitingTime\n");
    for (i = 0; i < n; i++) {
        printf(" %d \t\t %d \t\t %d \t\t %d\n", processes[i], bt[i], tat[i],wt[i]);
    }


    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}






