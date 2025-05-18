#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], bt[n], at[n], wt[n], tat[n];
    float total_wt = 0, total_tat = 0;

    // Input burst times and arrival times
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        pid[i] = i + 1;
    }

    // Sort by Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                // Swap arrival time
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process ID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    int start_time = 0;
    for (int i = 0; i < n; i++) {
        if (start_time < at[i])
            start_time = at[i];

        wt[i] = start_time - at[i];
        tat[i] = wt[i] + bt[i];
        start_time += bt[i];

        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Output
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
