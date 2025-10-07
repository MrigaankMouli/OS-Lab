#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int ref_bit[MAX_FRAMES];
    int num_pages, num_frames;
    int page_faults = 0, hits = 0;
    int pointer = 0;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);
    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter page reference string: ");
    for (int i = 0; i < num_pages; i++)
        scanf("%d", &pages[i]);

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        ref_bit[i] = 0;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                ref_bit[j] = 1;  
                hits++;
                break;
            }
        }

        if (!found) {
            while (ref_bit[pointer] == 1) {
                ref_bit[pointer] = 0; 
                pointer = (pointer + 1) % num_frames;
            }
            frames[pointer] = page;
            ref_bit[pointer] = 1;
            pointer = (pointer + 1) % num_frames;
            page_faults++;
        }

        printf("\nAfter page %d: ", page);
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != -1)
                printf("%d(%d) ", frames[j], ref_bit[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults: %d", page_faults);
    printf("\nTotal Hits: %d", hits);
    printf("\nHit Ratio: %.2f\n", (float)hits / num_pages);

    return 0;
}
