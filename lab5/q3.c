#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	pid = fork();
	
	if (pid == 0){
		printf("Currently in child process\n");
		printf("The Process ID of the current process is : %d\n", getpid());
		printf("The Process ID of the parent process is : %d\n", getppid());
	}
	else{
		wait(NULL);
		printf("Currently in parent process\n");
		printf("The Process ID of the current process is: %d\n", getpid());
		exit(0);
	}
	return 0;
}
