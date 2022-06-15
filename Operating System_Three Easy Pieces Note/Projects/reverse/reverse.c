#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * Invoke Arguments:
 * 1. When reverse is invoked with 2 arguments, the first file is the source file and the second one is the destination file.
 * 2. When invoked with 1 argument, the user supplies the input file, but the result is printed to stdout.
 * 3. When invoked with 0 arguments, the program reads from stdin and prints to stdout
 * Note: 
 * a. If the input file and output file are the same(same pathname or same hard-linked file), print and error "Input and output file must differ" and exit with code 1
 * b. If the number of arguments exceed 2, print "usage: reverse <intput> <output> and exit with code 1.
 */

/*
 * 1. Test for arguments.
 * 2. Construct a stream to the src_file and a stream to the dest_file. If the open fails, print out "error: cannot open file 'input.txt'" and exit with code 1.
 * 3. Malloc a string to store the read using malloc. If the malloc fails, print error "malloc failed\n" and exit with code 1.
 * 4. Read one line each time using the getline(char**, size_t*,  int, FILE*) function, and push the line onto the stack.
 * 5. Write the strings in the stack to the dest_file in reverse order.
 * 6. Free the malloced memory.
 */

int main(int argc, char** argv) {
	if (argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}

	// Check if the files exist.
	FILE *src_file = stdin, *dest_file = stdout;
	if (argc >= 2 && (src_file = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
		exit(1);
	} 
	if (argc == 3 && (dest_file = fopen(argv[2], "w")) == NULL) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
		exit(1);
	}

	// If the input file and output file are the same, print the error.
	if (argc == 3) {
		// Get the stat of the two files
		struct stat input_stat, output_stat;
		stat(argv[1], &input_stat);
		stat(argv[2], &output_stat);
		// 1. Check if their paths are the same.
		// 2. Check if the are the same hard-linked files
		if (strcmp(argv[1], argv[2]) == 0 || (input_stat.st_dev == output_stat.st_dev && input_stat.st_ino == output_stat.st_ino)) {
			fprintf(stderr, "reverse: input and output file must differ\n");
			exit(1);
		}
	}

	char *buffer = (char*)malloc(sizeof(char) * BUFSIZ);
	size_t *buf_size = (size_t*)malloc(sizeof(size_t));
	*buf_size = BUFSIZ;

	// Stack buffer to store the data
	char** stack = (char**)malloc(sizeof(char*) * BUFSIZ);
	int stackTop = 0;
	int capacity = BUFSIZ;

	while (getline(&buffer, buf_size, src_file) != -1) {
		char *str_cpy = (char*)malloc(sizeof(char) * (*buf_size));
		memcpy(str_cpy, buffer, *buf_size);

		// If the nmber of elements reached the stack's capacity, resize the stack.
		if (stackTop == capacity) {
			capacity *= 2;
			stack = realloc(stack, sizeof(char*) * capacity);
			if (!stack) {
				fprintf(stderr, "malloc failed\n");
				exit(1);
			}
		}
		stack[stackTop++] = str_cpy;
	}

	int nelem = stackTop;
	// Write the data to the dest_file
	for (stackTop--; stackTop >= 0; stackTop--) {
		fprintf(dest_file, "%s", stack[stackTop]);
	}

	// Free memory
	free(buffer);
	free(buf_size);
	int i;
	for (i = 0; i < nelem; ++i)
		free(stack[i]);
	free(stack);

	if (argc >= 2) 
		fclose(src_file);
	if (argc == 3)
		fclose(dest_file);
	return 0;
}