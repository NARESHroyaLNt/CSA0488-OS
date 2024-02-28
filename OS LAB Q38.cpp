#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define DISK_SIZE 200
int compare(const void *a, const void *b) 
{
    int A = *(int *)a;
    int B = *(int *)b;
    return A - B;
}
void CSCAN(int arr[], int n, int head) 
{
    qsort(arr, n, sizeof(int), compare);
    int total_movement = 0;
    int distance, cur_track;
    printf("C-SCAN Order: ");
    for (int i = 0; i < n; i++) 
	{
        cur_track = arr[i];
        if (cur_track >= head) 
		{
            distance = abs(cur_track - head);
            total_movement += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
    }
    if (head < DISK_SIZE - 1) 
	{
        total_movement += DISK_SIZE - 1 - head; 
        total_movement += DISK_SIZE - 1; 
        head = 0;
    }
    for (int i = 0; i < n; i++) 
	{
        cur_track = arr[i];
        if (cur_track < arr[0]) 
		{
            distance = abs(cur_track - head);
            total_movement += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
    }
    printf("\nTotal head movement: %d\n", total_movement);
}
int main() 
{
    int arr[] = {95, 180, 34, 119, 11, 123, 62, 64};
    int n = sizeof(arr) / sizeof(arr[0]);
    int head = 50; 
    printf("Initial position of head: %d\n", head);
    CSCAN(arr, n, head);
    return 0;
}

