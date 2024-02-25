#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int shared_var = 0;
pthread_mutex_t lock;
void* increment(void* arg) 
{
    pthread_mutex_lock(&lock);
    shared_var++;
    printf("Incremented Shared Variable: %d\n", shared_var);
    pthread_mutex_unlock(&lock);
    return NULL;
}
void* decrement(void* arg) 
{
    pthread_mutex_lock(&lock);
    shared_var--;
    printf("Decremented Shared Variable: %d\n", shared_var);
    pthread_mutex_unlock(&lock);
    return NULL;
}
int main() 
{
    pthread_t t1, t2;
    if (pthread_mutex_init(&lock, NULL) != 0) 
	{
        printf("Mutex init has failed\n");
        return 1;
    }
    if(pthread_create(&t1, NULL, &increment, NULL) != 0) 
	{
        return 1;
    }
    if(pthread_create(&t2, NULL, &decrement, NULL) != 0) 
	{
        return 1;
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    printf("Final Shared Variable: %d\n", shared_var);
    return 0;
}
