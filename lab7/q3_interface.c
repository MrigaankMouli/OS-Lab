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
    char buffer[BUFSIZ];
    int shmid;

    shmid = shmget((key_t)1234, sizeof(struct shared), 0666 | IPC_CREAT);
    sharedMemory = shmat(shmid, NULL, 0);


    printf("Memory attached at %p\n", sharedMemory);
    data = (struct shared *)sharedMemory;

    data->turn = 0;

    while (running) {
        while (data->turn == 1) {  
            sleep(1);
            printf("Waiting for Display to read...\n");
        }

        printf("Enter some text: ");
        if (!fgets(buffer, BUFSIZ, stdin)) {
            fprintf(stderr, "fgets error\n");
            break;
        }

        strncpy(data->text, buffer, TEXT_SZ - 1);
        data->text[TEXT_SZ - 1] = '\0';

        data->turn = 1; 

        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }

    if (shmdt(sharedMemory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
