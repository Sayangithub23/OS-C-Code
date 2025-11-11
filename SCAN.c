#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, size, direction;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (req[i] > req[j]) {
                int temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }

    int total = 0, pos;
    for (pos = 0; pos < n; pos++)
        if (head < req[pos])
            break;

    printf("\n\nDisk Head Movement Order (SCAN):\n");
    printf("---------------------------------\n");

    int curr = head;

    // Print Gantt chart start
    printf("\nGantt Chart:\n");
    printf("| %d ", curr);

    if (direction == 1) { // moving right
        for (int i = pos; i < n; i++) {
            total += abs(curr - req[i]);
            curr = req[i];
            printf("| %d ", curr);
        }
        // Go to end
        if (curr != size - 1) {
            total += abs(size - 1 - curr);
            curr = size - 1;
            printf("| %d ", curr);
        }
        // Reverse
        for (int i = pos - 1; i >= 0; i--) {
            total += abs(curr - req[i]);
            curr = req[i];
            printf("| %d ", curr);
        }
    } else { // moving left
        for (int i = pos - 1; i >= 0; i--) {
            total += abs(curr - req[i]);
            curr = req[i];
            printf("| %d ", curr);
        }
        // Go to start
        if (curr != 0) {
            total += curr;
            curr = 0;
            printf("| %d ", curr);
        }
        // Reverse
        for (int i = pos; i < n; i++) {
            total += abs(curr - req[i]);
            curr = req[i];
            printf("| %d ", curr);
        }
    }

    printf("|\n");
    printf("---------------------------------\n");
    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}
