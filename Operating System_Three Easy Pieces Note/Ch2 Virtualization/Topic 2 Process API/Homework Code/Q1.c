#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int val = 50;
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "Fork failed");
		exit(1);
	} else if(rc == 0) {
		printf("This is child process: %d\n", (int)getpid());
		val = -10;
		printf("Value: %d\n", val);
	} else {
		int wc = wait(NULL);
		printf("This is parrent proces: %d\n", (int)getpid());
		printf("Value: %d\n", val);
	}
	return 0;
}
