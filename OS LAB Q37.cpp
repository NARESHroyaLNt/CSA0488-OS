#include <stdio.h>
#include <stdlib.h>
int abs(int n) {
    return (n > 0) ? n : -n;
}
void FCFS(int requests[], int n, int start) 
{
    int totalHeadMovement = 0;
    int currentPosition = start;
    printf("Sequence of head movement:\n");
    for (int i = 0; i < n; i++) 
	{
        int distance = abs(requests[i] - currentPosition);
        totalHeadMovement += distance;
        currentPosition = requests[i];
        printf("%d ", requests[i]);
    }
    printf("\nTotal head movement: %d cylinders.\n", totalHeadMovement);
}
int main() 
{
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int start = 53; 
    printf("First Come First Served Disk Scheduling\n");
    printf("Starting position of the disk head: %d\n", start);
    FCFS(requests, n, start);
    return 0;
}

