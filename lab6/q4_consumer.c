#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define MAX_SHELF 5

int main() {
    int fd;
    int item;
    int shelf_count = 5; 

    fd = open(FIFO_NAME, O_RDONLY);

    printf("Consumer: Starting with shelf count %d\n", shelf_count);

    while (1) {
        ssize_t bytes = read(fd, &item, sizeof(item));

        if (item == 1) {
            if (shelf_count < MAX_SHELF) {
                shelf_count++;
                printf("Consumer: Producer added an item. Shelf count: %d\n", shelf_count);
            } else {
                printf("Consumer: Shelf full! Cannot add more items.\n");
            }
        } else if (item == 0) {
            if (shelf_count > 0) {
                shelf_count--;
                printf("Consumer: Removed one item. Shelf count: %d\n", shelf_count);
            } else {
                printf("Consumer: Shelf empty, no items to remove.\n");
            }
        } else {
            printf("Consumer: Received unknown command %d\n", item);
        }
    }

    close(fd);
    return 0;
}
