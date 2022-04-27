#include <time.h>
#include "utmplib.h"

#define SHOW_HOST
void show_info(struct utmp*);
void show_time(long);

extern int utmp_fd;
struct utmp *rec;

int main(int argc, char* argv[]) {
	// If open failed
	if(utmp_open(UTMP_FILE) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}

	// While read succeed
	while((rec = utmp_next()) != NULL) {
		show_info(rec);
	}

	utmp_close();
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
