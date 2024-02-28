#include <stdio.h>
#include <stdlib.h>
#define DISK_SIZE 200
int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
void SCAN(int requests[], int n, int start, int direction) {
    int totalHeadMovement = 0;
    int currentPosition = start;
    qsort(requests, n, sizeof(int), cmpfunc);
    printf("Sequence of head movement:\n");
    if (direction >= 0) {
        for (int i = 0; i < n; i++) {
            if (requests[i] >= start) {
                totalHeadMovement += abs(currentPosition - requests[i]);
                currentPosition = requests[i];
                printf("%d ", currentPosition);
            }
        }
        if (currentPosition < DISK_SIZE - 1) {
            totalHeadMovement += DISK_SIZE - 1 - currentPosition;
            currentPosition = DISK_SIZE - 1;
            printf("%d ", currentPosition);
    }
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < start) {
                totalHeadMovement += abs(currentPosition - requests[i]);
                currentPosition = requests[i];
                printf("%d ", currentPosition);
            }
        }
    } else 
    
    printf("\nTotal head movement: %d cylinders.\n", totalHeadMovement);
}
int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int start = 53; 
    int direction = 1; 
    printf("SCAN Disk Scheduling\n");
    printf("Starting position of the disk head: %d\n", start);
    printf("Direction: %s\n", direction == 1 ? "Towards the end" : "Towards the beginning");
    SCAN(requests, n, start, direction);
    return 0;
}

