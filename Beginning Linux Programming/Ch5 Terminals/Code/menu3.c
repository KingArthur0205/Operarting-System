#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char* menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greeting, char* options[], FILE *in, FILE *out);

int main(int argc, char** argv) {
	FILE *input, *output;
	if (!isatty(fileno(stdout))) 
		fprintf(stdout, "You are not a terminal. But ok.\n");

	// Open the terminal for reading and writing
	input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if (!input || !output) {
		fprintf(stderr, "Fail to open file /dev/tty.\n");
		exit(1);
	}

	int choice;
	do {
		choice = getchoice("Please make a selection:", menu, input, output);
		// Write to the directed file
		printf("Your selection is %c\n", choice);
	} while(choice != 'q');
	return 0;
}


int getchoice(char *greeting, char* options[], FILE *in, FILE *out) {
	int selected;
	// Keep record of whether a valid option has been chosen
	int chosen = 0;
	char** option;

	// Keep asking for input if input not valid
	do {
		fprintf(out, "%s\n", greeting);
		option = options;
		while (*option) { 
			fprintf(out, "%s\n", *option++);
		}
		
		do {
			selected = getc(in);
		} while (selected == '\n');

		option = options;
		while (*option) {
			if (selected == (*option)[0]) {
				chosen = 1;
				break;
			}
			option++;
		}

		if (!chosen)
			fprintf(out, "%c is an invalid input, please select again.\n", selected);
	} while (!chosen);

	return selected;
}