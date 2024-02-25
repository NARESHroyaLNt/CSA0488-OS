#include <stdio.h>
#include <stdbool.h>
typedef struct {
    int process_id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;
void roundRobinScheduling(Process p[], int n, int time_quantum) 
{
    int total_time = 0; 
    bool done;
    for (int i = 0; i < n; i++) 
	{
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = 0;
    }
    do {
        done = true;
        for (int i = 0; i < n; i++) 
		{
            if (p[i].remaining_time > 0) 
			{
                done = false; 
                if (p[i].remaining_time > time_quantum) 
				{
                    total_time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                } else {
                    total_time += p[i].remaining_time;
                    p[i].waiting_time = total_time - p[i].burst_time;
                    p[i].remaining_time = 0;
                }
            }
        }
    } while (!done);
    for (int i = 0; i < n; i++) 
	{
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
    }
}
void printProcesses(Process p[], int n) 
{
    int total_waiting_time = 0, total_turnaround_time = 0;
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
	{
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].process_id, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
    printf("Average Waiting Time = %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_turnaround_time / n);
}
int main() 
{
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];
    for (int i = 0; i < n; i++) 
	{
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    roundRobinScheduling(processes, n, time_quantum);
    printProcesses(processes, n);
    return 0;
}

