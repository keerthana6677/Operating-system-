#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt;
pthread_mutex_t mutex;
int readcount = 0;

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt); // First reader locks writer
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading\n", *(int*)arg);

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt); // Last reader unlocks writer
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* writer(void* arg) {
    sem_wait(&wrt);
    printf("Writer %d is writing\n", *(int*)arg);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int id[3] = {1, 2, 3}, wid[2] = {1, 2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&r[0], NULL, reader, &id[0]);
    pthread_create(&w[0], NULL, writer, &wid[0]);
    pthread_create(&r[1], NULL, reader, &id[1]);
    pthread_create(&w[1], NULL, writer, &wid[1]);
    pthread_create(&r[2], NULL, reader, &id[2]);

    for (int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);
    return 0;
}

