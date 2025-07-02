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

    // Initialize allocation array with -1 (means not allocated)
    for(i = 0; i < np; i++)
        allocation[i] = -1;

    // First Fit allocation
    for(i = 0; i < np; i++) {
        for(j = 0; j < nb; j++) {
            if(blockSize[j] >= processSize[i]) {
                allocation[i] = j; // Allocate block j to process i
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for(i = 0; i < np; i++) {
        printf(" %d\t\t%d\t\t", i+1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i]+1);  // +1 for 1-based indexing
        else
            printf("Not Allocated\n");
    }

    return 0;
}
