#include <stdio.h>

struct arr {
    int process_id, burst_time;
};

typedef struct arr S;

void main() {
    int n_sp, n_up, total_wt = 0, total_tat = 0;

    printf("Enter number of system processes: ");
    scanf("%d", &n_sp);

    S sp[n_sp];
    int d = n_sp;  // starting user process ID from n_sp+1
    printf("Enter burst times for system processes:\n");
    for (int i = 0; i < n_sp; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &sp[i].burst_time);
        sp[i].process_id = i + 1;
    }

    printf("Enter number of user processes: ");
    scanf("%d", &n_up);

    S up[n_up];
    printf("Enter burst times for user processes:\n");
    for (int i = 0; i < n_up; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &up[i].burst_time);
        up[i].process_id = ++d;
    }

    // Create a combined array to hold both system and user processes
    S all_processes[n_sp + n_up];
    for (int i = 0; i < n_sp; i++) {
        all_processes[i] = sp[i];
    }
    for (int i = 0; i < n_up; i++) {
        all_processes[n_sp + i] = up[i];
    }

    // Initialize waiting time and turnaround time arrays
    int wt[n_sp + n_up], tat[n_sp + n_up];

    // Calculate Waiting Time for all processes
    wt[0] = 0;  // First process has no waiting time
    for (int i = 1; i < n_sp + n_up; i++) {
        wt[i] = all_processes[i - 1].burst_time + wt[i - 1]; // Sum of all previous burst times
    }

    // Calculate Turnaround Time for all processes
    for (int i = 0; i < n_sp + n_up; i++) {
        tat[i] = all_processes[i].burst_time + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nProcesses \t BurstTime \t TurnaroundTime \t WaitingTime\n");

    // Print all processes from the final combined queue
    for (int i = 0; i < n_sp + n_up; i++) {
        printf(" %d \t\t %d \t\t %d \t\t %d\n", all_processes[i].process_id, all_processes[i].burst_time, tat[i], wt[i]);
    }

    // Calculate average waiting time and turnaround time
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / (n_sp + n_up));
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / (n_sp + n_up));
}
