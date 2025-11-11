#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    int complete = 0, t = 0, shortest = 0, finish_time;
    float total_wt = 0, total_tat = 0;
    int check = 0;

    // --- New variables for Gantt Chart ---
    int current_process = -1; // -1: None, -2: IDLE
    int block_start_time = 0;
    printf("\n--- Gantt Chart ---\n");
    // -------------------------------------

    while (complete != n) {
        int minm = INT_MAX;
        shortest = -1;
        check = 0;

        for (int j = 0; j < n; j++) {
            if (at[j] <= t && rt[j] < minm && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        // --- Gantt Chart Logic: Handle IDLE time ---
        if (check == 0) {
            if (current_process != -2) { // If not already IDLE
                if (current_process != -1) { // A process was running
                    printf("| P%d (%d-%d) ", current_process + 1, block_start_time, t);
                }
                current_process = -2; // Set state to IDLE
                block_start_time = t;
            }
            t++;
            continue;
        }
        // ------------------------------------------

        // --- Gantt Chart Logic: Handle Context Switch ---
        if (shortest != current_process) {
            if (current_process == -2) { // Was IDLE
                printf("| IDLE (%d-%d) ", block_start_time, t);
            } else if (current_process != -1) { // Was a different process
                printf("| P%d (%d-%d) ", current_process + 1, block_start_time, t);
            }
            current_process = shortest;
            block_start_time = t;
        }
        // ----------------------------------------------

        // 🔹 Process runs for 1 unit
        rt[shortest]--;
        t++;

        // 🔹 If finished
        if (rt[shortest] == 0) {
            complete++;
            check = 0;
            finish_time = t;

            // --- Gantt Chart Logic: Print final block for the process ---
            printf("| P%d (%d-%d) ", shortest + 1, block_start_time, t);
            current_process = -1; // Reset current process
            block_start_time = t; // Set start time for next block (might be IDLE)
            // -----------------------------------------------------------

            int tat = finish_time - at[shortest];
            int wt = tat - bt[shortest];
            if (wt < 0) wt = 0;

            total_tat += tat;
            total_wt += wt;
        }
    }

    printf("|\n"); // Close the Gantt Chart
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    return 0;
}