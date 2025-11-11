#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }

    int total_movement = 0, i;
    for (i = 0; i < n; i++)
        if (head < requests[i])
            break;

    printf("\nLOOK Disk Scheduling Order:\n");

    // Move right
    for (int j = i; j < n; j++) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
        printf("%d -> ", head);
    }

    // Move left (reverse)
    for (int j = i - 1; j >= 0; j--) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
        printf("%d -> ", head);
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
    return 0;
}
