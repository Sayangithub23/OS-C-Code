// First Come First Serve (FCFS) Scheduling Algorithm

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

    // Sort by arrival time
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                int tmp;

                tmp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = tmp;

                tmp = burst[i];
                burst[i] = burst[j];
                burst[j] = tmp;

                char t[5];
                for (int k = 0; k < 5; k++) t[k] = process[i][k];
                for (int k = 0; k < 5; k++) process[i][k] = process[j][k];
                for (int k = 0; k < 5; k++) process[j][k] = t[k];
            }
        }
    }

    // Calculate Completion Times
    completion[0] = arrival[0] + burst[0];
    for (i = 1; i < n; i++) {
        if (arrival[i] > completion[i - 1])
            completion[i] = arrival[i] + burst[i];
        else
            completion[i] = completion[i - 1] + burst[i];
    }

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
