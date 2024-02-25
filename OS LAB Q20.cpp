#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
sem_t rw_mutex;
sem_t mutex;
int data = 0;
int read_count = 0;
void *reader(void *arg) 
{
    int f;
    f = ((int)arg);
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mutex);
    printf("Data read by the reader%d is %d\n", f, data);
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mutex);
}
void *writer(void *arg) 
{
    int f;
    f = ((int) arg);
    sem_wait(&rw_mutex);
    data++;
    printf("Data written by the writer%d is %d\n", f, data);
    sem_post(&rw_mutex);
}
int main() 
{
    int i, b; 
    pthread_t rtid[5], wtid[5];
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    for (i = 0; i <= 2; i++) 
	{
        pthread_create(&wtid[i], NULL, writer, (void *)i);
        pthread_create(&rtid[i], NULL, reader, (void *)i);
    }
    for (i = 0; i <= 2; i++) 
	{
        pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    return 0;
}
