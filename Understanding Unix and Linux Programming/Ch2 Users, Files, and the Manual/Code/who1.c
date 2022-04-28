// Contain the user login information - struct utmp
#include <utmp.h>
#include <stdlib.h>
// Contains the falgs O_RDONLY, O_WRONLY, O_RDWR
#include <fcntl.h>
// Contains read and write system call
#include <unistd.h>
#include <stdio.h>

#define SHOWHOST //include remote machine on output
#define REC_LEN (sizeof(struct utmp))

void show_info(struct utmp*);

int main(int argc, char* argv[]) {
	// 1. Define the buffer(struct utmp) and the file descriptor
	int utmp_fd;
	struct utmp log_in_info;

	char *utmp_file = argc > 1 ? argv[1] : UTMP_FILE;
	// 2. Call the open system call to open the utmp file
	// UTMP_FILE is defined in <utmp.h>
	if((utmp_fd = open(utmp_file, O_RDONLY)) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}
	fprintf(stdout,"File Opened Successfull. File Descriptor: %d\n", utmp_fd);

	// Only print out the information if sizeof(struct utmp) bytes are read
	while(read(utmp_fd, &log_in_info, REC_LEN) == REC_LEN)
		show_info(&log_in_info);
	close(utmp_fd);
	return 0;
}

void show_info(struct utmp *log_in_info) {
	printf("%-8.8s", log_in_info -> ut_name); // Print the log name
	printf(" ");
	printf("%-8.8s", log_in_info -> ut_line); // Print the tty
	printf(" ");
	printf("%-101d", log_in_info -> ut_time); // Print the log-in time
	printf(" ");
#ifdef SHOWHOST
	printf("(%s)", log_in_info -> ut_host);
#endif
	printf("\n");
}
