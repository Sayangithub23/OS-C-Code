#include <stdio.h>

int main() {
    int pages[30], frames[10], n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    int page_faults = 0, next = 0;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // 🔹 Check if page already in frame
        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // 🔹 If not found → page fault
        if (!found) {
            frames[next] = page;      // Replace oldest page
            next = (next + 1) % f;    // Move pointer  in circular way
            page_faults++;
        }

        // 🔹 Print frame contents
        printf("Page %d -> ", page);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
    return 0;
}
