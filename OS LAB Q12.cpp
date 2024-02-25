#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_PHILOSOPHERS 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopher_number + 4) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_number + 1) % NUM_PHILOSOPHERS
int state[NUM_PHILOSOPHERS];
int philosophers[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};
pthread_mutex_t mutex;
pthread_mutex_t fork_mutex[NUM_PHILOSOPHERS];
void test(int philosopher_number) 
{
    if (state[philosopher_number] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) 
	{
        state[philosopher_number] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", philosopher_number + 1, LEFT + 1, philosopher_number + 1);
        printf("Philosopher %d is Eating\n", philosopher_number + 1);
        pthread_mutex_unlock(&fork_mutex[philosopher_number]);
    }
}
void take_fork(int philosopher_number) 
{
    pthread_mutex_lock(&mutex);
    state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopher_number + 1);
    test(philosopher_number);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&fork_mutex[philosopher_number]);
    sleep(1);
}
void put_fork(int philosopher_number) 
{
    pthread_mutex_lock(&mutex);
    state[philosopher_number] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", philosopher_number + 1, LEFT + 1, philosopher_number + 1);
    printf("Philosopher %d is thinking\n", philosopher_number + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}
void* philosopher(void* num) 
{
    int* i =num;
    for (int j = 0; j < 5; j++) 
	{
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}
int main() 
{
    int i;
    pthread_t thread_id[NUM_PHILOSOPHERS];
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
	{
        pthread_mutex_init(&fork_mutex[i], NULL);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
	{
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
	{
        pthread_join(thread_id[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
	{
        pthread_mutex_destroy(&fork_mutex[i]);
    }
    return 0;
}

