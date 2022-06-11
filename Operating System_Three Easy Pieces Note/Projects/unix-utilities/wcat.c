#include <stdio.h>
#include <stdlib.h>

/*
 * 1. If there is no input file, return 0
 * 2. Iterate through all of the files:
 * 	a. If the call of fopen() to a file fails, print error "wcat: cannot open file\n" and return 1
 * 	b. Create a char buffer. Read a line at one time using gets(char*) until gets() returns NULL
 * 	c. Write the buffer to the stdout
 * 	d. Close the stream by calling fclose()
 * 3. Return 0
 *
 */
int main(int argc, char** argv) {
	if (argc == 1)
		exit(0);

	FILE *f_stream;
	int file_counter = 1;
	char buffer[BUFSIZ];
	while (++file_counter <= argc) {
		if (!(f_stream = fopen(argv[file_counter - 1], "r"))) {
			printf("wcat: cannot open file\n");
			exit(1);
		}

		while (fgets(buffer, BUFSIZ, f_stream)) {
			printf("%s", buffer);
		}
		fclose(f_stream);	

	}	
	return 0;
}