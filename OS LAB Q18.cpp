#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t full, empty;
pthread_mutex_t mutex;
void* producer(void* arg) {
    int item;
    for(int i = 0; i < 10; i++) {
        item = i;
        printf("Producer produced item: %d\n", item);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}
void* consumer(void* arg) {
    int item;
    for(int i = 0; i < 10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer consumed item: %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
}
int main() {
    pthread_t tid_producer, tid_consumer;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);
    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);   
    return 0;
}
