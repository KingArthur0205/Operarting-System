#include <stdio.h>
#include <stdlib.h>

/*
 * 1. If there is no input file(argc==1), print "wunzip: file1 [file2 ...]\n" and exit(1)
 * 2. Iterate through all the files:
 * 	a. Construct a stream to each. Print the error and exit with code 1 if open fails.
 * 	b. Read the number of characters(n_char) and the character(cur_char) at a time. Write the character to stdout n_char times
 * 	c. Close the stream
 */

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}

	int file_counter;
	FILE *src_file;
	for (file_counter = 1; file_counter < argc; file_counter++) {
		if ((src_file = fopen(argv[file_counter], "r")) == NULL) {
			printf("wunzip: cannot open file\n");
			exit(1);
		}

		int n_char; char cur_char;
		while (fread(&n_char, sizeof(int), 1, src_file) != 0) {
			fread(&cur_char, sizeof(char), 1, src_file);
			int i;
			for (i = 0; i < n_char; ++i) {
				fwrite(&cur_char, sizeof(char), 1, stdout);
			}
		}
		fclose(src_file);
	}
	return 0;
}