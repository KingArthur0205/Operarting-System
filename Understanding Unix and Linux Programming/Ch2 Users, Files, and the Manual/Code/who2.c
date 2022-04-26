#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <utmp.h>

#define SHOW_HOST
void show_info(struct utmp*);
void show_time(long);

int main(int argc, char* argv[]) {
	struct utmp cur_record;
	int utmp_fd;
	int size = sizeof(struct utmp);

	// If open failed
	if((utmp_fd = open(UTMP_FILE, O_RDONLY)) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}

	// While read succeed
	while(read(utmp_fd, &cur_record, size) != 0) {
		show_info(&cur_record);
	}

	close(utmp_fd);
	return 0;
}

// Print out the user info from struct utmp
void show_info(struct utmp* record) {
	printf("%-8.8s ", record->ut_user);
	printf("%-*.*s ", 8, 8, record->ut_line);
	show_time(record->ut_time);
#ifdef SHOW_HOST
	printf("(%-8.8s) ", record->ut_host);
#endif
	printf("\n");
}

// Print out time in the correct way
void show_time(long time) {
	char *time_str;
	time_str = ctime(&time);
	// The first four characters are the weekday and an empty space(e.x. Wed )
	printf("%-12.12s ", time_str + 4);
}
