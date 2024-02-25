#include <stdio.h>
#include <stdlib.h>
#define MEMORY_BLOCKS 5
#define PROCESSES 4
void firstFit(int memory[], int processes[]) 
{
    int allocation[PROCESSES];
    for (int i = 0; i < PROCESSES; i++) 
	{
        allocation[i] = -1;
    }
    for (int i = 0; i < PROCESSES; i++) 
	{
        for (int j = 0; j < MEMORY_BLOCKS; j++) 
		{
            if (memory[j] >= processes[i]) 
			{
                allocation[i] = j;
                memory[j] -= processes[i];
                break;
            }
        }
    }
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < PROCESSES; i++) 
	{
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
    printf("\n");
}
void bestFit(int memory[], int processes[]) 
{
    int allocation[PROCESSES];
    for (int i = 0; i < PROCESSES; i++) 
	{
        allocation[i] = -1;
    }
    for (int i = 0; i < PROCESSES; i++) 
	{
        int bestIdx = -1;
        for (int j = 0; j < MEMORY_BLOCKS; j++) 
		{
            if (memory[j] >= processes[i]) 
			{
                if (bestIdx == -1 || memory[j] < memory[bestIdx]) 
				{
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) 
		{
            allocation[i] = bestIdx;
            memory[bestIdx] -= processes[i];
        }
    }
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < PROCESSES; i++) 
	{
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
    printf("\n");
}
void worstFit(int memory[], int processes[]) 
{
    int allocation[PROCESSES];
    for (int i = 0; i < PROCESSES; i++) 
	{
        allocation[i] = -1;
    }
    for (int i = 0; i < PROCESSES; i++) 
	{
        int worstIdx = -1;
        for (int j = 0; j < MEMORY_BLOCKS; j++) 
		{
            if (memory[j] >= processes[i]) 
			{
                if (worstIdx == -1 || memory[j] > memory[worstIdx]) 
				{
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) 
		{
            allocation[i] = worstIdx;
            memory[worstIdx] -= processes[i];
        }
    }
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < PROCESSES; i++) 
	{
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
    printf("\n");
}
int main() 
{
    int memory[MEMORY_BLOCKS] = {100, 500, 200, 300, 600};
    int processes[PROCESSES] = {212, 417, 112, 426};
    printf("First Fit:\n");
    int memoryCopy[MEMORY_BLOCKS];
    memcpy(memoryCopy, memory, sizeof(memory));
    firstFit(memoryCopy, processes);
    printf("Best Fit:\n");
    memcpy(memoryCopy, memory, sizeof(memory));
    bestFit(memoryCopy, processes);
    printf("Worst Fit:\n");
    memcpy(memoryCopy, memory, sizeof(memory));
    worstFit(memoryCopy, processes);
    return 0;
}

