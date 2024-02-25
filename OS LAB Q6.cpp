#include <stdio.h>
#include <stdlib.h>
#define MAX_PROCESSES 100
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;
int findNextProcess(Process processes[], int n, int current_time) 
{
    int highest_priority = 9999;
    int index = -1;
    for (int i = 0; i < n; i++) 
	{
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) 
		{
            if (processes[i].priority < highest_priority) 
			{
                highest_priority = processes[i].priority;
                index = i;
            }
            else if (processes[i].priority == highest_priority) 
			{
                if (processes[i].arrival_time < processes[index].arrival_time) 
				{
                    index = i;
                }
            }
        }
    }
    return index;
}
void preemptivePriorityScheduling(Process processes[], int n) 
{
    int current_time = 0;
    int completed = 0;
    int previous_process = -1;
    while (completed != n) 
	{
        int index = findNextProcess(processes, n, current_time);
        if (index != -1) 
		{
            if (previous_process != index && previous_process != -1) 
			{
                printf("Time %d: P%d preempted by P%d\n", current_time, processes[previous_process].process_id, processes[index].process_id);
            }
            processes[index].remaining_time -= 1;
            if (processes[index].remaining_time == 0) 
			{
                completed++;
                processes[index].completion_time = current_time + 1;
                processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
                processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
                printf("Time %d: P%d completed\n", current_time + 1, processes[index].process_id);
            }
            previous_process = index;
        }
        current_time++;
    }
}
int main() 
{
    Process processes[] = {
        {1, 0, 10, 2},
        {2, 2, 1, 1},
        {3, 3, 2, 4},
        {4, 5, 1, 3},
        {5, 6, 5, 2}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    for (int i = 0; i < n; i++) 
	{
        processes[i].remaining_time = processes[i].burst_time;
    }
    preemptivePriorityScheduling(processes, n);
}

