#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long int type;
    int num;
};

int main() {
    int running = 1;
    struct msg data;
    int msgid, num;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    while(running) {
        printf("Enter a number :");
        scanf("%d", &num);
        data.type = 1;
        data.num = num;
        msgsnd(msgid, (void *)&data, sizeof(data), 0);
        if (num == 0)
            running = 0;
    }
    exit(EXIT_SUCCESS);
}