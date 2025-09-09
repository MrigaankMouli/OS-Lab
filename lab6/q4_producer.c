#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"

int main() {
    int fd;
    int item;
    int shelf_count = 5;

    // Create FIFO if not exists
    if (access(FIFO_NAME, F_OK) == -1) {
        if (mkfifo(FIFO_NAME, 0666) != 0) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    // Open FIFO for writing only
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Producer: Shelf initialized to %d items.\n", shelf_count);

    while (1) {
        printf("Enter 1 to add an item, 0 to do nothing: ");
        if (scanf("%d", &item) != 1) {
            fprintf(stderr, "Invalid input.\n");
            break;
        }

        if (item == 1) {
            // Tell consumer we want to add item
            if (write(fd, &item, sizeof(item)) == -1) {
                perror("write");
                break;
            }
            printf("Producer: Added 1 item.\n");
        } else if (item == 0) {
            // Do nothing, but can send 0 as no-op (optional)
            if (write(fd, &item, sizeof(item)) == -1) {
                perror("write");
                break;
            }
        } else {
            printf("Please enter 0 or 1 only.\n");
        }
    }

    close(fd);
    return 0;
}
