#include <stdio.h>
#include <pthread.h>

int counter = 0;                   // Shared resource
pthread_mutex_t lock;             // Mutex lock

void* increment(void* arg) {
    pthread_mutex_lock(&lock);    // Locking
    for(int i = 0; i < 100000; i++)
        counter++;
    pthread_mutex_unlock(&lock);  // Unlocking
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);
    pthread_mutex_destroy(&lock);

    return 0;
}

