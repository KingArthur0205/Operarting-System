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
		char *args[] = { "ls"};
		//The following all list all of the files in the current directory
		//ls defined in path enviornment
		execl("/bin/ls", "ls", NULL);
		execlp("ls", "ls", NULL);
		execv("/bin/ls", args);
		execvp("ls", args);
		
	} 
	//if parent process, print goodbye
	else {
		int rc_wait = wait(NULL);
	}
	return 0;
}
