#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *printMessage(void *threadid) 
{
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL); 
}
int main () 
{
    pthread_t threads[2]; 
    int rc;
    long t;
    for(t=0; t<2; t++)
	{
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, printMessage, (void *)t); 
        if (rc)
		{
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    for(t=0; t<2; t++) 
	{
        pthread_join(threads[t], NULL);
    }
    printf("In main: All threads have completed\n");
    pthread_exit(NULL); 
}

