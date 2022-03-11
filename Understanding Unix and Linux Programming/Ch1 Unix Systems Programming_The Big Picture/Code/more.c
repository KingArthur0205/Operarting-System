#include <stdio.h>
#include <stdlib.h>

#define PAGE_LEN 24
#define LINE_LEN 512

void do_more(FILE*);
int see_more();

int main(int argc, char* argv[]) {
	// Used to access the files provided
	FILE *fp; 

	// If the user does not provide a file path, exit.
	if(argc == 1) {
		fprintf(stderr, "Please provide  at least one input\n");
		exit(-1);
	} else {
		// Loop through all of the files and access them all
		// "--argc" is the number of files that we still need to access.
		while(--argc) {
			// Open up a stream to the files
			// argv points to the file before the one we want to access, increment it by one gives us the desired file 
			if((fp = fopen(*++argv, "r")) != NULL) {
				// See the file
				do_more(fp);
				fclose(fp);
			} else {
				fprintf(stderr, "The file %s isn't readable\n", *argv);
			}
		}
	}
	return 0;
}

void do_more(FILE *fp) {
	// Line of text to print
	char line[LINE_LEN];
	// Number of lines on this page
	int num_of_lines = 0;
	// The response that see_more function returns. Indicate whether the user wants to see more of the file
	int reply;

	while( fgets(line, LINE_LEN, fp) ) {
		// Check if the number of lines printed exceed that of the maximum line boundary
		if(num_of_lines == PAGE_LEN) {
			// Get user response from see_more
			reply = see_more();
			if(reply == 0)
				// The user does not want to see more. Exit the program
				break;
			// reply now stands for the number of lines that the user wants to see more of
			num_of_lines -= reply;
		}

		if(fputs(line, stdout) == EOF)
			exit(1);
		num_of_lines++;
	}
}

int see_more() {
	int c;
	fprintf(stdout, "Want more?\n");

	// Use while loop to avoid invalid input
	while( (c = getchar()) != EOF) {
		switch(c) {
			case 'q':
				return 0;
			case ' ':
				return PAGE_LEN;
			case '\n':
				return 1;

		}
	}
	return 0;
}
