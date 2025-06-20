#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int burstTime;  // CPU Burst Time
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input burst times
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
    }

    // FCFS scheduling logic
    p[0].waitingTime = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        p[i].waitingTime = p[i - 1].waitingTime + p[i - 1].burstTime;
    }

    // Turnaround time = burst + waiting
    for (int i = 0; i < n; i++) {
        p[i].turnaroundTime = p[i].burstTime + p[i].waitingTime;
        totalWaitingTime += p[i].waitingTime;
        totalTurnaroundTime += p[i].turnaroundTime;
    }

    // Output results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}

