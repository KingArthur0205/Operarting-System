#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 1. If no files are given(argc==1), print "wzip: file1 [file2 ...]\n" and exit with 1
 * 2. Determine the output stream. wzip should output to stdout.
 * 3. Iterate through all the files(file_counter=1;file_counter<argc;file_counter++)
 * 	a. Construct a file stream. Read one character at a time using getc(FILE*). 
 * 	b. If char_counter=0, set prev_char to the character. 
 * 	c. Otherwise, compare the character to prev_char. If they are equal, char_counter++. Else, write char_counter and prev_char to the destination. And set char_counter=1 and prev_char=cur_char.
 * 	d. Close the stream
 */
void write_zip(int char_count, char cur_char);

int main(int argc, char** argv) {
	// When no files are given
	if (argc == 1) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}

	int file_counter;
	FILE *src_file;

	int char_counter = 0;
	char cur_char, prev_char;
	for (file_counter = 1; file_counter < argc; ++file_counter) {
		if (!(src_file = fopen(argv[file_counter], "r"))) {
			printf("wzip: cannot open file\n");
			exit(1);
		}

		while ((cur_char = getc(src_file)) != EOF) {
			if (char_counter == 0) {
				prev_char = cur_char;
				char_counter++;
			} else {
				if (prev_char == cur_char) {
					char_counter++;
				}
				else {
					write_zip(char_counter, prev_char);
					char_counter = 1;
					prev_char = cur_char;
				}
			}
		}
		fclose(src_file);
	}
	write_zip(char_counter, prev_char);
	return 0;
}

void write_zip(int char_count, char cur_char) {
	fwrite(&char_count, sizeof(int), 1, stdout);
	fwrite(&cur_char, sizeof(char), 1, stdout);
}
