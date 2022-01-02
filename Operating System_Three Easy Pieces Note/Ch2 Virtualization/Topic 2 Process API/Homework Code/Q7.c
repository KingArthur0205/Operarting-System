#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "Fork failed");
		exit(1);
	} 
	else if(rc == 0) {
		close(STDOUT_FILENO);
		printf("Parent: Hello");
	} 
	else {
		int rc_wait = wait(NULL);
		printf("Parent: Hello");
	}
	return 0;
}
