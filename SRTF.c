#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    int complete = 0, t = 0, shortest = -1;
    float total_wt = 0, total_tat = 0;
    int finish_time;

    printf("\nGantt Chart:\n0");

    while (complete < n) {
        int minm = INT_MAX;
        shortest = -1;

        // 🔹 Find process with smallest remaining time among arrived
        for (int j = 0; j < n; j++) {
            if (at[j] <= t && rt[j] > 0 && rt[j] < minm) {
                minm = rt[j];
                shortest = j;
            }
        }

        // 🔹 If no process ready → CPU idle
        if (shortest == -1) {
            t++;
            continue;
        }

        // 🔹 Execute for 1 unit
        rt[shortest]--;
        t++;

        // 🔹 If finished
        if (rt[shortest] == 0) {
            complete++;
            finish_time = t;

            int tat = finish_time - at[shortest];
            int wt = tat - bt[shortest];
            if (wt < 0) wt = 0;

            total_tat += tat;
            total_wt += wt;

            // 🔹 Print only when process completes
            printf(" | P%d | %d", shortest + 1, t);
        }
    }

    printf("\n");
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
