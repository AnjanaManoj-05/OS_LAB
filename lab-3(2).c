#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 5
#define SIMULATION_TIME 20


typedef struct {
    int id;
    int period;
    int execution;
    int deadline;
    int remaining;
} Task;

Task tasks[MAX_TASKS];
int task_count;


int compare_EDF(const void *a, const void *b) {
    return ((Task *)a)->deadline - ((Task *)b)->deadline;
}


void earliest_deadline_first() {
    printf("\nEarliest Deadline First (EDF) Scheduling Simulation:\n");

    for (int time = 0; time < SIMULATION_TIME; time++) {

        for (int i = 0; i < task_count; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].deadline = time + tasks[i].period;
            }
        }


        qsort(tasks, task_count, sizeof(Task), compare_EDF);

        int selected_task = -1;
        for (int i = 0; i < task_count; i++) {
            if (tasks[i].remaining > 0) {
                selected_task = i;
                break;
            }
        }

        if (selected_task != -1) {
            tasks[selected_task].remaining--;
            printf("Time %d: Task %d executing (Deadline: %d)\n", time, tasks[selected_task].id, tasks[selected_task].deadline);
        } else {
            printf("Time %d: CPU idle\n", time);
        }
    }
}

int main() {
    printf("Enter number of tasks (max %d): ", MAX_TASKS);
    scanf("%d", &task_count);

    if (task_count > MAX_TASKS || task_count <= 0) {
        printf("Invalid number of tasks!\n");
        return 1;
    }


    for (int i = 0; i < task_count; i++) {
        printf("Enter Task %d execution time and period: ", i + 1);
        scanf("%d %d", &tasks[i].execution, &tasks[i].period);
        tasks[i].id = i + 1;
        tasks[i].deadline = tasks[i].period;
        tasks[i].remaining = tasks[i].execution;
    }


    earliest_deadline_first();

    return 0;
}
