// Shortest Job First (SJF) Non-Preemptive Scheduling Algorithm

#include <stdio.h>

int main() {
    int n, i;
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    int burst[n], arrival[n], waiting[n], turnaround[n], completion[n];
    char process[n][5];

    // Input process details
    for (i = 0; i < n; i++) { 
        sprintf(process[i], "P%d", i + 1);
        printf("\nEnter arrival time for %s: ", process[i]);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for %s: ", process[i]);
        scanf("%d", &burst[i]);
    }

    // Step 1: Sort by Arrival Time
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                int tmp;

                tmp = arrival[i]; arrival[i] = arrival[j]; arrival[j] = tmp;
                tmp = burst[i];   burst[i] = burst[j];   burst[j] = tmp;

                char t[5];
                for (int k = 0; k < 5; k++) { t[k] = process[i][k]; process[i][k] = process[j][k]; process[j][k] = t[k]; }
            }
        }
    }

    // Step 2: SJF Logic
    for (i = 0; i < n - 1; i++) {
        int pos = i;

        // Find shortest job among arrived processes
        for (int j = i + 1; j < n; j++) {
            if (arrival[j] <= completion[i] && burst[j] < burst[pos]) {
                pos = j;
            }
        }

        // Swap to place shortest next
        if (pos != i) {
            int tmp;

            tmp = arrival[i]; arrival[i] = arrival[pos]; arrival[pos] = tmp;
            tmp = burst[i];   burst[i] = burst[pos];   burst[pos] = tmp;

            char t[5];
            for (int k = 0; k < 5; k++) { t[k] = process[i][k]; process[i][k] = process[pos][k]; process[pos][k] = t[k]; }
        }

        // Compute Completion Time for first process or next process
        if (i == 0)
            completion[i] = arrival[i] + burst[i];
        else {
            if (arrival[i] > completion[i-1])
                completion[i] = arrival[i] + burst[i];
            else
                completion[i] = completion[i-1] + burst[i];
        }
    }

    // Completion for last process
    if (arrival[n-1] > completion[n-2])
        completion[n-1] = arrival[n-1] + burst[n-1];
    else
        completion[n-1] = completion[n-2] + burst[n-1];

    // Calculate Turnaround and Waiting Times
    for (i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    // Display table
    printf("\n\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t\t%d\t\t%d\n", process[i], arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    // Calculate averages
    float avg_wait = 0, avg_turn = 0;
    for (i = 0; i < n; i++) {
        avg_wait += waiting[i];
        avg_turn += turnaround[i];
    }
    avg_wait /= n;
    avg_turn /= n;

    printf("\nAverage Waiting Time = %.2f", avg_wait);
    printf("\nAverage Turnaround Time = %.2f\n", avg_turn);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf(" |  %s  ", process[i]);
    }
    printf("|\n0");
    for (i = 0; i < n; i++) {
        printf("\t%d", completion[i]);
    }
    printf("\n");

    return 0;
}
