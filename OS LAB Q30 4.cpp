#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_function(void *arg) 
{
    printf("Inside the thread function\n");
    pthread_exit(NULL);
}
int main() 
{
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid, NULL, thread_function, NULL);
    if (ret != 0) 
	{
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    printf("Thread created successfully\n");
    pthread_exit(NULL); 
}

