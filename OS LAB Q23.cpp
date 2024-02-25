#include <stdio.h>
#define MAX 10
void firstFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++) 
	{
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < m; j++) 
		{
            if (blockSize[j] >= processSize[i]) 
			{
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break; 
            }
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) 
	{
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1); 
        else
            printf("Not Allocated");
        printf("\n");
    }
}
int main() 
{
    int blockSize[MAX], processSize[MAX], m, n;
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    printf("Enter the size of each block:\n");
    for (int i = 0; i < m; i++) 
	{
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) 
	{
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    firstFit(blockSize, m, processSize, n);
    return 0;
}

