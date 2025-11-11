#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nOrder of head movement:\n");
    printf("%d", head);

    for (int i = 0; i < n; i++) {
        total += abs(request[i] - head);
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement = %d", total);
    printf("\nAverage Head Movement = %.2f\n", (float)total / n);

    return 0;
}
