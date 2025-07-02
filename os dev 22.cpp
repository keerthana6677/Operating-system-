#include <stdio.h>

int main() {
    int nb, np, i, j;
    int blockSize[10], processSize[10], allocation[10];

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter sizes of %d memory blocks: ", nb);
    for(i = 0; i < nb; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter sizes of %d processes: ", np);
    for(i = 0; i < np; i++)
        scanf("%d", &processSize[i]);

    // Initialize allocation array with -1 (not allocated)
    for(i = 0; i < np; i++)
        allocation[i] = -1;

    // Best Fit allocation
    for(i = 0; i < np; i++) {
        int bestIdx = -1;
        for(j = 0; j < nb; j++) {
            if(blockSize[j] >= processSize[i]) {
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if(bestIdx != -1) {
            // Allocate process to best fitting block
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for(i = 0; i < np; i++) {
        printf(" %d\t\t%d\t\t", i+1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i]+1);  // Block number shown as 1-based index
        else
            printf("Not Allocated\n");
    }

    return 0;
}
