#include <stdio.h>
#include <stdlib.h>
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

int isPalindrome(int num){
    int n = num;
    int rev = 0;
    while (n){
        int d = n%10;
        rev = rev*10 + d;
        n = n / 10;
    }
    return (rev == num);
}

int main() {
    int running = 1;
    int msgid;
    struct msg data;
    long int msgReceived = 0;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    while(running) {
        msgrcv(msgid, (void *)&data, sizeof(data), msgReceived, 0);
        printf("You wrote: %d\n", data.num);
        if (data.num == 0){
            running = 0;
            continue;
        }
        if (isPalindrome(data.num))
            printf("It is a Palindrome\n");
        else printf("It is not a Palindrome\n");
    }
    msgctl(msgid, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}