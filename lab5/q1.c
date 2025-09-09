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
		for(int i = 0;i<5;i++){
			printf("Still in Child Process : %d. Waiting ...\n", pid);
			sleep(1);
		}
	}
	else{
		wait(NULL);
		printf("Child Process complete\n");
		printf("Now in Parent Process\n");
		exit(0);
	}
	return 0;
}
