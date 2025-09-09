#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	pid = fork();
	if (pid < 0){
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	
	else if (pid == 0){
		execlp("./q1", "q1", NULL);
	}
	else{
		wait(NULL);
		printf("Now in Current program Parent Process\n");
		exit(0);
	}
	return 0;
}
