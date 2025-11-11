#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, disk_size, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }

    int i, total_movement = 0;
    for (i = 0; i < n; i++)
        if (head < requests[i])
            break;

    printf("\nCSCAN Disk Scheduling Order:\n");

    // Move right first
    for (int j = i; j < n; j++) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
        printf("%d -> ", head);
    }

    // Jump to start
    total_movement += (disk_size - 1 - head); // move to end
    total_movement += (disk_size - 1);        // jump to start
    head = 0;

    for (int j = 0; j < i; j++) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
        printf("%d -> ", head);
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
    return 0;
}
