#include <stdio.h>
#define MAXBLOCKS 50

int main() {
    int n, start, length, flag, j;
    int memory[MAXBLOCKS] = {0};

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nFile %d\n", i + 1);
        printf("Enter the starting block: ");
        scanf("%d", &start);
        printf("Enter the length: ");
        scanf("%d", &length);

        if (start < 0 || start + length > MAXBLOCKS) {
            printf("Not possible: Block range out of bounds.\n");
            continue;
        }

        flag = 1;
        for (j = start; j < start + length; j++) {
            if (memory[j] == 1) {
                flag = 0;
                break;
            }
        }

        if (flag == 1) {
            printf("File allocated in blocks: ");
            for (j = start; j < start + length; j++) {
                memory[j] = 1;
                printf("%d ", j);
            }
            printf("\n");
        } else {
            printf("File allocation failed. Some blocks are already allocated.\n");
        }
    }

    printf("\nFinal block allocation status:\n");
    for (int i = 0; i < MAXBLOCKS; i++) {
        if (memory[i] == 1) {
            printf("Block %d: Allocated\n", i);
        } else {
            printf("Block %d: Not Allocated\n", i);
        }
    }

    return 0;
}
