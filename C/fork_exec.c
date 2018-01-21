#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	pid_t pid;
	int exit_status;

	if((pid=fork()) < 0) {
		perror("fork error");
		exit(1);
	} else if(pid == 0) {
		printf("Before exec\n");
		execl("./fork", "fork", (char *)0);
		printf("After exec\n");
	} else {
		pid = wait(&exit_status);
	} 
	printf("Parent\n");
	return 0;
}
