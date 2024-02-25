#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_function(void *arg) 
{
    pthread_t *tid = (pthread_t *)arg;   
    if (pthread_equal(*tid, pthread_self())) 
	{
        printf("Inside the thread function: Thread IDs are equal\n");
    }
	else 
	{
        printf("Inside the thread function: Thread IDs are not equal\n");
    }  
    pthread_exit(NULL);
}
int main() 
{
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid, NULL, thread_function, (void *)&tid);
    if (ret != 0) 
	{
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    printf("Thread created successfully\n");
    pthread_exit(NULL);
}

