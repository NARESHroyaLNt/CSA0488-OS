#include <stdio.h>
typedef struct {
    int process_id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;
void sortProcessesByBurstTime(Process p[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
	{
        int min_idx = i;
        for (int j = i + 1; j < n; j++) 
		{
            if (p[j].burst_time < p[min_idx].burst_time) 
			{
                min_idx = j;
            }
        }
        Process temp = p[i];
        p[i] = p[min_idx];
        p[min_idx] = temp;
    }
}
void calculateWaitingTime(Process p[], int n) 
{
    p[0].waiting_time = 0; 
    for (int i = 1; i < n; i++) 
	{
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
    }
}
void calculateTurnaroundTime(Process p[], int n) 
{
    for (int i = 0; i < n; i++) 
	{
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
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
    printf("Average waiting time = %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time = %.2f\n", (float)total_turnaround_time / n);
}
int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++) 
	{
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &p[i].burst_time);
        p[i].process_id = i+1;
    }
    sortProcessesByBurstTime(p, n);
    calculateWaitingTime(p, n);
    calculateTurnaroundTime(p, n);
    printProcesses(p, n);
    return 0;
}

