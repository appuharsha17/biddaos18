#include <stdio.h>

// Function to calculate average waiting time and average turnaround time
void calculateAvgTimes(int processes[], int n, int bt[], int wt[], int tat[], int quantum) {
    // Initialize remaining time for all processes
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    int t = 0; // Current time

    // Continue the loop until all processes are done
    while (1) {
        int done = 1; // Flag to check if all processes are done

        // Traverse all processes
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0; // At least one process is not done

                // Execute the process for the time quantum or the remaining time, whichever is smaller
                if (remaining_time[i] > quantum) {
                    t += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    t += remaining_time[i];
                    wt[i] = t - bt[i];
                    remaining_time[i] = 0;
                    tat[i] = t;
                }
            }
        }

        // If all processes are done, exit the loop
        if (done)
            break;
    }
}

// Function to calculate average of an array
float calculateAverage(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return (float)sum / (float)n;
}

// Function to display the table with process details
void displayTable(int processes[], int n, int bt[], int wt[], int tat[]) {
    printf("\nProcess\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], tat[i], wt[i], tat[i] - wt[i]);
    }
}

int main() {
    int n, quantum;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], waiting_time[n], turnaround_time[n];

    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1; // Process numbers starting from 1
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Calculate waiting time and turnaround time
    calculateAvgTimes(processes, n, burst_time, waiting_time, turnaround_time, quantum);

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = calculateAverage(waiting_time, n);
    float avg_turnaround_time = calculateAverage(turnaround_time, n);

    // Display the table with process details
    displayTable(processes, n, burst_time, waiting_time, turnaround_time);

    // Display average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}