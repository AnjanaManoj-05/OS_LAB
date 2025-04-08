#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void wait(int *S) {
    (*S)--;
}

void signal(int *S) {
    (*S)++;
}

void one_eat(int pos[], int hungry, int *chopstick, int n) {
    printf("Allow one philosopher to eat at any time\n");

    for (int i = 0; i < hungry; i++) {
        // Show all are waiting
        for (int j = 0; j < hungry; j++) {
            printf("P %d is waiting\n", pos[j]);
        }

        int p = pos[i] - 1;
        int left = p;
        int right = (p + 1) % n;

        if (chopstick[left] == 1 && chopstick[right] == 1) {
            wait(&chopstick[left]);
            wait(&chopstick[right]);

            printf("P %d is granted to eat\n", pos[i]);
            sleep(1); // Simulate eating
            printf("P %d has finished eating\n", pos[i]);

            signal(&chopstick[left]);
            signal(&chopstick[right]);
        } else {
            printf("P %d cannot eat (chopsticks unavailable)\n", pos[i]);
        }
    }
}

void two_eat(int pos[], int hungry, int *chopstick, int n) {
    printf("Allow up to two philosophers to eat at a time\n");
    int eating = 0;

    for (int i = 0; i < hungry && eating < 2; i++) {
        int p = pos[i] - 1;
        int left = p;
        int right = (p + 1) % n;

        if (chopstick[left] == 1 && chopstick[right] == 1) {
            wait(&chopstick[left]);
            wait(&chopstick[right]);

            printf("P %d is granted to eat\n", pos[i]);
            sleep(1);
            printf("P %d has finished eating\n", pos[i]);

            signal(&chopstick[left]);
            signal(&chopstick[right]);
            eating++;
        } else {
            printf("P %d is waiting (chopsticks unavailable)\n", pos[i]);
        }
    }

    if (eating == 0) {
        printf("No philosopher could eat this round.\n");
    }
}

int main() {
    int n, hungry, ch;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);

    int *chopstick = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        chopstick[i] = 1; // all chopsticks available
    }

    do {
        printf("How many are hungry: ");
        scanf("%d", &hungry);
    } while (hungry > n || hungry <= 0);

    int pos[hungry];
    for (int i = 0; i < hungry; i++) {
        do {
            printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
            scanf("%d", &pos[i]);
        } while (pos[i] < 1 || pos[i] > n);
    }

    do {
        printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                one_eat(pos, hungry, chopstick, n);
                break;
            case 2:
                two_eat(pos, hungry, chopstick, n);
                break;
            case 3:
                free(chopstick);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (1);

    return 0;
}
