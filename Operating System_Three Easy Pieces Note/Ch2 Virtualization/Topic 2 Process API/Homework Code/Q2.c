#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fd = open("/File.txt", O_WRONLY|O_CREAT|O_APPEND);
	int rfd = open("/File.txt", O_RDONLY);
	char buffer[100];
	char childString[] = "This is children process writing.\n";
	char *parentString = "This is parent process writing.\n";
	int rc = fork();

    //if fork fails
	if(rc < 0) {
        //send fork fail string to stderr
		fprintf(stderr, "Fork failed");
		exit(1);
	} 
    //if the current process is child process
    else if(rc == 0) {
		printf("This is child process: %d\n", (int)getpid());
		int childStringLength = strlen(childString);
        //write the childString to the file
		write(fd, childString, sizeof(childString));
        //read from the file into the buffer
		read(rfd, buffer, sizeof(childString));
        //print out the buffer
		int i;
		for(i = 0; i <  childStringLength; ++i) {
			printf("%c", buffer[i]);
		}
		printf("\n");
	} else {
        //wait for the child process to finish
		int wc = wait(NULL);
		printf("This is parrent proces: %d\n", (int)getpid());
		write(fd, parentString, strlen(parentString));
		read(rfd, buffer, strlen(parentString));
		int i;
		for(i = 0; i <  strlen(parentString); ++i) {
			printf("%c", buffer[i]);
		}
		printf("\n");
	}
	return 0;
}
