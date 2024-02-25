#include <stdio.h>
typedef struct {
    int process_id;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
} Process;
void sortByPriority(Process p[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
	{
        int min_index = i;
        for (int j = i + 1; j < n; j++) 
		{
            if (p[j].priority < p[min_index].priority) 
			{
                min_index = j;
            }
        }
        Process temp = p[i];
        p[i] = p[min_index];
        p[min_index] = temp;
    }
}
void calculateTimes(Process p[], int n) 
{
    p[0].waiting_time = 0; 
    for (int i = 1; i < n; i++) 
	{
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
    }
    for (int i = 0; i < n; i++) 
	{
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}
void printProcesses(Process p[], int n) 
{
    int total_waiting_time = 0, total_turnaround_time = 0;
    printf("Process ID\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
	{
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].process_id, p[i].priority, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
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
        printf("Enter priority for process %d (lower number means higher priority): ", i+1);
        scanf("%d", &p[i].priority);
        p[i].process_id = i+1; 
    }
    sortByPriority(p, n);
    calculateTimes(p, n);
    printProcesses(p, n);
    return 0;
}

