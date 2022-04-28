#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * cp source-file dest-file
 * 1. Make sure that argc == 3
 * 2. Make sure the source and destination file is not the same.
 * 3. Open the two files. If dest-file doesn't exist, create.
 * 4. Read the file. If the returned read-size is > 0, put it in the dest-file
 */

#define READ_SIZE 128
#define CREAT_MODE 0644

void oops(const char*, const char*);

int main(int argc, char* argv[]) {
	char buffer[READ_SIZE];
	int src_fd, dest_fd;

	// If source or destination file is missing
	if(argc != 3) {
		fprintf(stderr, "Missing file argument.\n");
		exit(1);
	}

    // If the source of destination file is the same
    if(strcmp(argv[1], argv[2]) == 0)
        oops("Cannot copy the same file: ", argv[1]);

	// Open the source file
	if((src_fd = open(*++argv, O_RDONLY)) == -1) {
		oops("Cannot open:", argv[1]);
	}

	// Create the destination file
	if((dest_fd = creat(*++argv, CREAT_MODE)) == -1) {
		oops("Cannot create:", argv[2]);
	}
	
	int size;
	// Read READ_SIZE to the buffer.
	while((size = read(src_fd, buffer, READ_SIZE)) >  0) {
		// Write the buffer to the destination file. If the written size isn't correct, exit.
		if(write(dest_fd, buffer, size) != size)
			oops("Write error: ", argv[2]);
	}

	if(size == -1)
		oops("Read error: ", argv[1]);

	// CLose the files.
	if(close(src_fd) == -1 || close(dest_fd) == -1)
		oops("Close error: ", "");

	return 0;
}

void oops(const char* s1, const char* s2) {
	fprintf(stderr, "%s%s\n", s1, s2);
	perror(s2);
	exit(1);	
}