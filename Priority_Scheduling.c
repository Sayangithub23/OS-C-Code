// Priority Scheduling (Non-Preemptive) Algorithm
#include <stdio.h>

int main() {
    int n, i;
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    int burst[n], arrival[n], priority[n], waiting[n], turnaround[n], completion[n];
    char process[n][5];

    // ---------- Step 1: Input Process Details ----------
    for (i = 0; i < n; i++) {
        sprintf(process[i], "P%d", i + 1);
        printf("\nEnter Arrival Time for %s: ", process[i]);
        scanf("%d", &arrival[i]);
        printf("Enter Burst Time for %s: ", process[i]);
        scanf("%d", &burst[i]);
        printf("Enter Priority for %s (lower number = higher priority): ", process[i]);
        scanf("%d", &priority[i]);
    } // end of input loop

    // ---------- Step 2: Sort by Arrival Time ----------
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                int tmp;

                tmp = arrival[i]; arrival[i] = arrival[j]; arrival[j] = tmp;
                tmp = burst[i];   burst[i] = burst[j];     burst[j] = tmp;
                tmp = priority[i]; priority[i] = priority[j]; priority[j] = tmp;

                char t[5];
                for (int k = 0; k < 5; k++) {
                    t[k] = process[i][k];
                    process[i][k] = process[j][k];
                    process[j][k] = t[k];
                } // end of process name swap
            } // end of arrival compare
        } // end of inner sort loop
    } // end of outer sort loop

    // ---------- Step 3: Priority Scheduling Logic ----------
    for (i = 0; i < n - 1; i++) {
        int pos = i;

        // Find highest priority (lowest number) among arrived processes
        for (int j = i + 1; j < n; j++) {
            if (arrival[j] <= completion[i]) {
                if (priority[j] < priority[pos]) {
                    pos = j;
                } else if (priority[j] == priority[pos] && arrival[j] < arrival[pos]) {
                    pos = j; // tie-breaker by earlier arrival
                }
            } // end if arrival check
        } // end inner for (find highest priority)

        // Swap next highest priority process to correct position
        if (pos != i) {
            int tmp;

            tmp = arrival[i]; arrival[i] = arrival[pos]; arrival[pos] = tmp;
            tmp = burst[i];   burst[i] = burst[pos];     burst[pos] = tmp;
            tmp = priority[i]; priority[i] = priority[pos]; priority[pos] = tmp;

            char t[5];
            for (int k = 0; k < 5; k++) {
                t[k] = process[i][k];
                process[i][k] = process[pos][k];
                process[pos][k] = t[k];
            } // end of name swap
        } // end if swap needed

        // Compute Completion Time
        if (i == 0) {
            completion[i] = arrival[i] + burst[i];
        } else {
            if (arrival[i] > completion[i - 1]) {
                completion[i] = arrival[i] + burst[i];
            } else {
                completion[i] = completion[i - 1] + burst[i];
            }
        }
    } // end outer for loop

    // ---------- Step 4: Completion Time for Last Process ----------
    if (arrival[n - 1] > completion[n - 2]) {
        completion[n - 1] = arrival[n - 1] + burst[n - 1];
    } else {
        completion[n - 1] = completion[n - 2] + burst[n - 1];
    }

    // ---------- Step 5: Calculate Turnaround & Waiting Times ----------
    for (i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    } // end of turnaround/waiting calc loop

    // ---------- Step 6: Display Process Table ----------
    printf("\n\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i], arrival[i], burst[i], priority[i],
               completion[i], turnaround[i], waiting[i]);
    } // end of display loop

    // ---------- Step 7: Calculate Average Times ----------
    float avg_wait = 0, avg_turn = 0;
    for (i = 0; i < n; i++) {
        avg_wait += waiting[i];
        avg_turn += turnaround[i];
    }
    avg_wait /= n;
    avg_turn /= n;

    printf("\nAverage Waiting Time = %.2f", avg_wait);
    printf("\nAverage Turnaround Time = %.2f\n", avg_turn);

    // ---------- Step 8: Gantt Chart ----------
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
} // end of main
