#include <stdio.h>
#include <stdbool.h>

#define MAX 50

int search(int key, int frame[], int f) {
    for (int i = 0; i < f; i++)
        if (frame[i] == key)
            return i;
    return -1;
}

void printFrames(int frame[], int f) {
    for (int i = 0; i < f; i++) {
        if (frame[i] != -1)
            printf("%d ", frame[i]);
        else
            printf("- ");
    }
    printf("\n");
}

void fifo(int pages[], int n, int f) {
    int frame[f];
    for (int i = 0; i < f; i++) frame[i] = -1;

    int index = 0, faults = 0;

    printf("\nFIFO Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, f) == -1) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            faults++;
            printf("PF No. %d: ", faults);
            printFrames(frame, f);
        }
    }
    printf("FIFO Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int f) {
    int frame[f];
    for (int i = 0; i < f; i++) frame[i] = -1;

    int faults = 0;

    printf("\nLRU Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int hit = search(pages[i], frame, f);

        if (hit != -1) {
            // Page is already in frame: do nothing (hit)
            continue;
        }

        // Page fault
        faults++;

        int lru_index = -1, min_recent = i;

        // Find empty frame or least recently used
        for (int j = 0; j < f; j++) {
            if (frame[j] == -1) {
                lru_index = j;
                break;
            }

            int last_used = -1;
            for (int k = i - 1; k >= 0; k--) {
                if (pages[k] == frame[j]) {
                    last_used = k;
                    break;
                }
            }

            if (last_used < min_recent) {
                min_recent = last_used;
                lru_index = j;
            }
        }

        frame[lru_index] = pages[i];
        printf("PF No. %d: ", faults);
        printFrames(frame, f);
    }

    printf("LRU Page Faults: %d\n", faults);
}


void optimal(int pages[], int n, int f) {
    int frame[f];
    for (int i = 0; i < f; i++) frame[i] = -1;

    int faults = 0;

    printf("\nOptimal Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, f) != -1)
            continue;

        int idx = -1, farthest = i + 1;

        for (int j = 0; j < f; j++) {
            int k;
            for (k = i + 1; k < n; k++) {
                if (frame[j] == pages[k])
                    break;
            }

            if (k == n) {
                idx = j;
                break;
            } else if (k > farthest) {
                farthest = k;
                idx = j;
            } else if (idx == -1) {
                idx = j;
            }
        }

        frame[idx] = pages[i];
        faults++;
        printf("PF No. %d: ", faults);
        printFrames(frame, f);
    }

    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int n, s;
    printf("Enter the number of frames: ");
    scanf("%d", &n);
    printf("Enter the length of reference string: ");
    scanf("%d", &s);
    int pages[s];
    printf("Enter the reference string: ");
    for (int i = 0; i < s; i++) {
        scanf("%d", &pages[i]);
    }

    fifo(pages, s, n);
    lru(pages, s, n);
    optimal(pages, s, n);

    return 0;
}
