#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rem_bt[n], wt[n], tat[n], arrival[n], completion[n];
    char process[n][5];

    for (int i = 0; i < n; i++) {
        sprintf(process[i], "P%d", i + 1);
        printf("%s Arrival Time: ", process[i]);
        scanf("%d", &arrival[i]);
        printf("%s Burst Time: ", process[i]);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
        wt[i] = tat[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, done = 0;
    printf("\nGantt Chart:\n0");
    
    while (done < n) {
        int check = 0;
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && rem_bt[i] > 0) {
                check = 1;
                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                    printf(" | %s | %d", process[i], time);
                } else {
                    time += rem_bt[i];
                    tat[i] = time - arrival[i];
                    wt[i] = tat[i] - bt[i];
                    completion[i] = time;
                    rem_bt[i] = 0;
                    done++;
                    printf(" | %s | %d", process[i], time);
                }
            }
        }
        if (!check) time++; 
    }

    printf("\n");

    // Results table
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t\t%d\t\t%d\n", process[i], arrival[i], bt[i], completion[i], tat[i], wt[i]);

    float avg_wait = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", avg_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
  