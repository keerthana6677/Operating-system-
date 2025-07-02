#include <stdio.h>
#include <stdlib.h>

int mutex = 1;     // Semaphore for mutual exclusion
int full = 0;      // Counts full slots
int empty = 3;     // Total buffer size = 3
int item = 0;      // Item produced

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    wait(&mutex);
    wait(&empty);
    item++;
    printf("Producer produced item %d\n", item);
    signal(&full);
    signal(&mutex);
}

void consumer() {
    wait(&mutex);
    wait(&full);
    printf("Consumer consumed item %d\n", item);
    item--;
    signal(&empty);
    signal(&mutex);
}

int main() {
    int choice;

    printf("Producer-Consumer Problem Simulation\n");
    while(1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("Buffer is full! Cannot produce.\n");
                break;
            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("Buffer is empty! Cannot consume.\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
