#include <stdio.h>

int main() {
    int m, n;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int memorySize[m], processSize[n], allocation[n];
    
    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &memorySize[i]);

    printf("Enter sizes of processes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    // Initialize all allocations to -1 (unallocated)
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    // Best Fit Allocation
    for (int i = 0; i < n; i++) {     // For each process
        int bestIdx = -1;
        for (int j = 0; j < m; j++) { // Find best (smallest) memory block that fits
            if (memorySize[j] >= processSize[i]) {
                if (bestIdx == -1 || memorySize[j] < memorySize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) { // If a block found
            allocation[i] = bestIdx;
            memorySize[bestIdx] -= processSize[i]; // Reduce memory size
        }
    }

    // Display results
    printf("\nProcess No.\tProcess Size\tMemory Block No.\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
