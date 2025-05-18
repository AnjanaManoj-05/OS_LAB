#include <stdio.h>

struct Process {
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int completed;
};

int main() {
    int n, completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input arrival and burst times
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    while (completed < n) {
        int idx = -1, min_bt = 99999;

        // Find process with min burst time among arrived and not completed
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].completed == 0 && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].wt = current_time - p[idx].at;
            p[idx].tat = p[idx].wt + p[idx].bt;
            current_time += p[idx].bt;
            p[idx].completed = 1;
            completed++;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        } else {
            current_time++; // CPU idle
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
