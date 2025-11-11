#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], done[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        done[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nGantt Chart:\n");
    printf("| %d ", head);

    for (int count = 0; count < n; count++) {
        int min = 9999, index = -1;

        // Find nearest request
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                int diff = abs(head - req[i]);
                if (diff < min) {
                    min = diff;
                    index = i;
                }
            }
        }

        total += min;
        head = req[index];
        done[index] = 1;

        printf("| %d ", head);
    }

    printf("|\n");
    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}
