#include <stdio.h>

// Function to calculate waiting time, turnaround time, and display the results for Priority Scheduling
void calculatePriorityTimes(int processes[], int n, int burst_time[], int priority[]) {
    int wt[n], tat[n], total = 0;

    // Sorting processes based on priority in descending order
    for (int i = 0; i < n; i++) {
        int pos = i;
        for (int j = i + 1; j < n; j++) {
            if (priority[j] > priority[pos])
                pos = j;
        }

        // Swapping processes, burst times, and priorities to maintain sorted order
        int temp = burst_time[i];
        burst_time[i] = burst_time[pos];
        burst_time[pos] = temp;

        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;

        temp = priority[i];
        priority[i] = priority[pos];
        priority[pos] = temp;
    }

    wt[0] = 0; // The first process has a waiting time of 0

    // Calculating waiting time for each process
    for (int i = 1; i < n; i++) {
        wt[i] = 0;
        // Waiting time is the sum of burst times of previous processes
        for (int j = 0; j < i; j++)
            wt[i] += burst_time[j];

        total += wt[i]; // Accumulating total waiting time
    }

    // Calculating turnaround time and displaying results for each process
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    float avg_wt = (float)total / n; // Calculating average waiting time
    float avg_tat = 0; // Initializing average turnaround time
    for (int i = 0; i < n; i++) {
        tat[i] = burst_time[i] + wt[i]; // Turnaround time = Burst time + Waiting time
        avg_tat += tat[i]; // Accumulating total turnaround time
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], priority[i], wt[i], tat[i]);
    }

    avg_tat /= n; 
    printf("\nAverage Waiting Time = %.2f\n", avg_wt); 
    printf("Average Turnaround Time = %.2f\n", avg_tat); 
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], priority[n];

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);

        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);

        processes[i] = i + 1; 
    }

    calculatePriorityTimes(processes, n, burst_time, priority);

    return 0;
}
