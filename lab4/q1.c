#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	char c;
	char* file;
	int in;
	scanf("%s", &file);
	in = open(file, O_RDONLY);
	while(read(in, &c, 1) == 1){
		write(1, &c, 1);
	}
	exit(0);
}
	
