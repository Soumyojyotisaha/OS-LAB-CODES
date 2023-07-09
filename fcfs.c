#include <stdio.h>

// Function to find the waiting time for all processes
void waitingTime(int burst_time[], int wait_time[], int n) {
    wait_time[0] = 0; // waiting time for the first process is 0
    int i;
    // Calculating waiting time
    for (i = 1; i < n; i++)
        wait_time[i] = burst_time[i - 1] + wait_time[i - 1];
}

// Function to calculate turnaround time
void turnaroundTime(int burst_time[], int wait_time[], int tat[], int n) {
    // Calculating turnaround time by adding burst_time[i] + wait_time[i]
    int i;
    for (i = 0; i < n; i++)
        tat[i] = burst_time[i] + wait_time[i];
}

// Function to calculate average time
void avgTime(int burst_time[], int n) {
    int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
    // Function to find waiting time of all processes
    waitingTime(burst_time, wait_time, n);
    // Function to find turnaround time for all processes
    turnaroundTime(burst_time, wait_time, tat, n);
    // Display processes along with all details
    printf("Processes\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wait_time[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], wait_time[i], tat[i]);
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);
}

// Main function
int main() {
    // Process id's
    int proc[] = {1, 2, 3, 4, 5};
    int n = sizeof(proc) / sizeof(proc[0]);
    // Burst time of all processes
    int burst_time[] = {5, 4, 3, 2, 4};
    avgTime(burst_time, n);
    return 0;
}
