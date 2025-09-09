#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char **argv){
	int n;
	int fd[2];
	char buf[1025];
	assert(argc == 2);
	pipe(fd);
	write(fd[1], argv[1], strlen(argv[1]));
	if ((n = read(fd[0], buf, 1024)) >= 0) {
		buf[n] = '\0';
		printf("read %d bytes from the pipe: \"%s\"\n", n, buf);
	}
	else
		perror("read");
	exit(0);
}
