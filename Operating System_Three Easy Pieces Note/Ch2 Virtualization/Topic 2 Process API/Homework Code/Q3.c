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
	//if child process, print hello
	else if(rc == 0) {
		printf("Hello\n");
	} 
	//if parent process, print goodbye
	else {
		int rc_wait = wait(NULL);
		printf("Goodbye\n");
	}
	return 0;
}