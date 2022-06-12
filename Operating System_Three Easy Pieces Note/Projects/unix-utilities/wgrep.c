#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function to Read a Line: 
 * #include <stdio.h>
 * ssize_t  getline(char **lineptr, size_t *n, FILE *stream)
 * If the read fails, getline return -1.(including end-of-file)
 *
 * Function to Search for a String:
 * #include <string.h>
 * char *strstr(const char *haystack, const char *needle);
 * The strstr function finds the first occurence of "needle" in "haystack". 
 * The function returns a pointer to the beginning of the located substring, or NULL if the substring is not found.
 */

/*
 * 1. If no argument is given(argc==1), print "wgrep: searchterm [file...]\n" and exit with 1
 * 2. If only the word is given(argc==2), search the word from stdin.
 * 3. Iterate through the given files:
 * 	a. If the file can't be opened, print "wgrep: cannot open file\n" and exit with code 1
 * 	b. Read a line by using getline.(Create a char* buffer and take the address of it as an argument to the call)
 * 	c. If the string is found(strstr()!=NULL) by calling strstr(), print that line. 
 * 	d. fclose() the stream
 * 4. Return 0
 */
void do_grep(FILE *stream, const char *key) {
	char *buffer = (char*)malloc(sizeof(char) * BUFSIZ);
	size_t *n = (size_t*)malloc(sizeof(size_t));
	*n = BUFSIZ;

	while (getline(&buffer, n, stream) != -1) {
		if (strstr(buffer, key))
			printf("%s", buffer);
	}
}

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	char *key = argv[1];
	if (argc == 2) {
		do_grep(stdin, key);		
	}

	int file_counter;
	for (file_counter = 2; file_counter < argc; ++file_counter) {
		FILE *stream;
		if (!(stream = fopen(argv[file_counter], "r"))) {
			printf("wgrep: cannot open file\n");
			exit(1);
		}

		do_grep(stream, key);
		fclose(stream);
	}

	return 0;
}