#include <stdio.h>
#define P 5  // processes
#define R 3  // resources

int main() {
    int i, j, k, flag, count = 0;
    int alloc[P][R] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[P][R]   = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int avail[R]   = {3,3,2};
    int need[P][R], finish[P] = {0}, safeSeq[P];

    // Calculate Need matrix
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while (count < P) {
        flag = 0;
        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                for (j = 0; j < R; j++)
                    if (need[i][j] > avail[j]) break;
                if (j == R) {
                    for (k = 0; k < R; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    flag = 1;
                }
            }
        }
        if (!flag) break; // No safe process found
    }

    if (count == P) {
        printf("System is in a Safe State.\nSafe Sequence: ");
        for (i = 0; i < P; i++)
            printf("P%d ", safeSeq[i]);
    } else {
        printf("System is in Deadlock!");
    }
    return 0;
}

