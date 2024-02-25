#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
int main() 
{
    pid_t pid; 
    pid = fork();
    if (pid == -1) 
	{
        perror("fork failed");
        return 1;
    } 
	else if (pid == 0) 
	{
        printf("Child Process:\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
    } 
	else 
	{
        printf("Parent Process:\n");
        printf("PID: %d, Child PID: %d\n", getpid(), pid);
        wait(NULL);
    }
    return 0;
}

