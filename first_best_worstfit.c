#include <stdio.h>
#include <stdlib.h>

void bestfit(int *blockSize, int totalBlocks, int *processSize, int totalProcesses) {
    int i, j, allocation[totalProcesses], fit, flag[totalBlocks], externalFrag = 0, internalFrag = 0, totalInternal = 0;

    for (i = 0; i < totalProcesses; i++) {
        allocation[i] = -1;
    }

    for (i = 0; i < totalBlocks; i++) {
        flag[i] = 0;
    }

    for (i = 0; i < totalProcesses; i++) {
        fit = -1;

        for (j = 0; j < totalBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (flag[j] == 0) {
                    if (fit == -1) {
                        fit = j;
                    } else if (blockSize[j] < blockSize[fit]) {
                        fit = j;
                    }
                }
            }
        }

        if (fit != -1) {
            allocation[i] = fit;
            flag[fit] = 1;
            internalFrag = blockSize[fit] - processSize[i];
            blockSize[fit] = internalFrag;
            totalInternal += internalFrag;
        }
    }

    for (i = 0; i < totalProcesses; i++) {
        if (allocation[i] == -1) {
            externalFrag += processSize[i];
        }
    }

    printf("\nProcess\tProcess Size\tBlock No.\n");

    for (i = 0; i < totalProcesses; i++) {
        printf("%d\t\t%d\t\t", (i + 1), processSize[i]);

        if (allocation[i] != -1) {
            printf("%d", (allocation[i] + 1));
        } else {
            printf("Not Allocated");
        }

        printf("\n");
    }

    printf("\n\tTotal Internal Fragmentation: %d", totalInternal);
    printf("\n\tTotal External Fragmentation: %d", externalFrag);
}

void firstfit(int *blockSize, int totalBlocks, int *processSize, int totalProcesses) {
    int i, j, allocation[totalProcesses], externalFrag = 0, internalFrag = 0, totalInternal = 0;

    for (i = 0; i < totalProcesses; i++) {
        allocation[i] = -1;
    }

    for (i = 0; i < totalProcesses; i++) {
        for (j = 0; j < totalBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                internalFrag = blockSize[j] - processSize[i];
                blockSize[j] = internalFrag;
                totalInternal += internalFrag;
                break;
            }
        }
    }

    for (i = 0; i < totalProcesses; i++) {
        if (allocation[i] == -1) {
            externalFrag += processSize[i];
        }
    }

    printf("\nProcess\tProcess Size\tBlock No.\n");

    for (i = 0; i < totalProcesses; i++) {
        printf("%d\t\t%d\t\t", (i + 1), processSize[i]);

        if (allocation[i] != -1) {
            printf("%d", (allocation[i] + 1));
        } else {
            printf("Not Allocated");
        }

        printf("\n");
    }

    printf("\n\tTotal Internal Fragmentation: %d", totalInternal);
    printf("\n\tTotal External Fragmentation: %d", externalFrag);
}

void worstfit(int *blockSize, int totalBlocks, int *processSize, int totalProcesses) {
    int i, j, allocation[totalProcesses], fit, flag[totalBlocks], externalFrag = 0, internalFrag = 0, totalInternal = 0;

    for (i = 0; i < totalProcesses; i++) {
        allocation[i] = -1;
    }

    for (i = 0; i < totalBlocks; i++) {
        flag[i] = 0;
    }

    for (i = 0; i < totalProcesses; i++) {
        fit = -1;

        for (j = 0; j < totalBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (flag[j] == 0) {
                    if (fit == -1) {
                        fit = j;
                    } else if (blockSize[j] > blockSize[fit]) {
                        fit = j;
                    }
                }
            }
        }

        if (fit != -1) {
            allocation[i] = fit;
            flag[fit] = 1;
            internalFrag = blockSize[fit] - processSize[i];
            blockSize[fit] = internalFrag;
            totalInternal += internalFrag;
        }
    }

    for (i = 0; i < totalProcesses; i++) {
        if (allocation[i] == -1) {
            externalFrag += processSize[i];
        }
    }

    printf("\nProcess\tProcess Size\tBlock No.\n");

    for (i = 0; i < totalProcesses; i++) {
        printf("%d\t\t%d\t\t", (i + 1), processSize[i]);

        if (allocation[i] != -1) {
            printf("%d", (allocation[i] + 1));
        } else {
            printf("Not Allocated");
        }

        printf("\n");
    }

    printf("\n\tTotal Internal Fragmentation: %d", totalInternal);
    printf("\n\tTotal External Fragmentation: %d", externalFrag);
}

int main() {
    int *blockSize, *processSize, numBlock, numProcess, choice, i;
    char c;

    do {
        printf("\n**********************\n* MEMORY ALLOCATION *\n**********************\n");
        printf("\n1. Best Fit\n2. First Fit\n3. Worst Fit\n4. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // BEST FIT CASE
                printf("\n\n\t\t\tBEST FIT\n\n");
                printf("\nEnter total blocks: ");
                scanf("%d", &numBlock);

                blockSize = (int *)malloc(numBlock * sizeof(int));
                for (i = 0; i < numBlock; i++) {
                    printf("\nEnter Block %d's Size: ", (i + 1));
                    scanf("%d", &blockSize[i]);
                }

                printf("\nEnter total blocks of processes: ");
                scanf("%d", &numProcess);

                processSize = (int *)malloc(numProcess * sizeof(int));
                for (i = 0; i < numProcess; i++) {
                    printf("\nEnter Process %d's Size: ", (i + 1));
                    scanf("%d", &processSize[i]);
                }

                bestfit(blockSize, numBlock, processSize, numProcess);

                free(blockSize);
                free(processSize);
                break;

            case 2: // FIRST FIT CASE
                printf("\n\n\t\t\tFIRST FIT\n\n");
                printf("\nEnter total blocks: ");
                scanf("%d", &numBlock);

                blockSize = (int *)malloc(numBlock * sizeof(int));
                for (i = 0; i < numBlock; i++) {
                    printf("\nEnter Block %d's Size: ", (i + 1));
                    scanf("%d", &blockSize[i]);
                }

                printf("\nEnter total blocks of processes: ");
                scanf("%d", &numProcess);

                processSize = (int *)malloc(numProcess * sizeof(int));
                for (i = 0; i < numProcess; i++) {
                    printf("\nEnter Process %d's Size: ", (i + 1));
                    scanf("%d", &processSize[i]);
                }

                firstfit(blockSize, numBlock, processSize, numProcess);

                free(blockSize);
                free(processSize);
                break;

            case 3: // WORST FIT CASE
                printf("\n\n\t\t\tWORST FIT\n\n");
                printf("\nEnter total blocks: ");
                scanf("%d", &numBlock);

                blockSize = (int *)malloc(numBlock * sizeof(int));
                for (i = 0; i < numBlock; i++) {
                    printf("\nEnter Block %d's Size: ", (i + 1));
                    scanf("%d", &blockSize[i]);
                }

                printf("\nEnter total blocks of processes: ");
                scanf("%d", &numProcess);

                processSize = (int *)malloc(numProcess * sizeof(int));
                for (i = 0; i < numProcess; i++) {
                    printf("\nEnter Process %d's Size: ", (i + 1));
                    scanf("%d", &processSize[i]);
                }

                worstfit(blockSize, numBlock, processSize, numProcess);

                free(blockSize);
                free(processSize);
                break;

            case 4:
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &c);

    } while (c == 'y' || c == 'Y');

    return 0;
}
