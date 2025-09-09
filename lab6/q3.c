#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024 * 1024 * 10)

int main(){
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    char buffer[1024] = "This is the write side of FIFO";

    if (access(FIFO_NAME, F_OK) == -1){
        res = mkfifo(FIFO_NAME, 0777);
        if(res != 0){
            fprintf(stderr, "Could not create FIFO\n");
            exit(EXIT_FAILURE);
        }
    }

    pipe_fd = open(FIFO_NAME, open_mode);
    if(pipe_fd != -1){
        res = write(pipe_fd, buffer, sizeof(buffer));
        if (res == -1) {
            fprintf(stderr, "Write error on pipe\n");
            exit(EXIT_FAILURE);
        }
    }
    (void)close(pipe_fd);
    
    exit(EXIT_SUCCESS);
}
