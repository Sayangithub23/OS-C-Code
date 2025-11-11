#include <stdio.h>

int main() {
    int m, n; // m = number of memory blocks, n = number of processes
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int block[m], process[n], allocation[n];

    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &block[i]);

    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &process[i]);

    for (int i = 0; i < n; i++)
        allocation[i] = -1;  // initially no block assigned

    // First Fit allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (block[j] >= process[i]) {
                allocation[i] = j;
                block[j] -= process[i];  // reduce block size
                break;  // assign first suitable block
            }
        }
    }

    // Display result
    printf("\nProcess\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], allocation[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }

    return 0;
}
