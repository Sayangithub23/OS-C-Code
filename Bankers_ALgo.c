#include <stdio.h>

int main() {
    int n, m; 
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    int finished[n], safeSeq[n];
    
    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Input Max Matrix
    printf("Enter Max Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input Available Resources
    printf("Enter Available Resources:\n");
    for(int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Initialize all as unfinished
    for(int i = 0; i < n; i++)
        finished[i] = 0;

    int count = 0;
    while(count < n) {
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(finished[i] == 0) {
                int j;
                for(j = 0; j < m; j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == m) { // If all needs can be satisfied
                    for(int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finished[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found) {
            printf("\nSystem is in DEADLOCK (Not Safe)\n");
            return 0;
        }
    }

    // Print Safe Sequence
    printf("\nSystem is in SAFE STATE\nSafe Sequence: ");
    for(int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 0;
}
