#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define TEXT_SZ 2048

struct shared {
    int turn;
    char text[TEXT_SZ];
};

int main() {
    int running = 1;
    void *sharedMemory = (void *)0;
    struct shared *data;
    int shmid;

    shmid = shmget((key_t)1234, sizeof(struct shared), 0666);

    sharedMemory = shmat(shmid, NULL, 0);

    printf("Memory attached at %p\n", sharedMemory);
    data = (struct shared *)sharedMemory;

    while (running) {
        if (data->turn == 1) { 
            printf("You wrote: %s", data->text);
            if (strncmp(data->text, "end", 3) == 0) {
                running = 0;
            }

            data->turn = 0;  
            memset(data->text, '\0', TEXT_SZ);
        } else {
            usleep(100000);  
        }
    }

    if (shmdt(sharedMemory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
