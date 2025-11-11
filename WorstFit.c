#include <stdio.h>

int main() {
    int m, n;
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
        allocation[i] = -1;

    // Worst Fit allocation
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (block[j] >= process[i]) {
                if (worstIdx == -1 || block[j] > block[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            block[worstIdx] -= process[i];
        }
    }

    printf("\nProcess\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], allocation[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }

    return 0;
}
