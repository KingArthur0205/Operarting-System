#include "utmplib.h"
#include <errno.h>

void show_info(struct utmp*);

int main(int argc, char *argv[]) {
	// Load the UTMP_FILE
	if(utmp_open(UTMP_FILE) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}

	struct utmp *rec;
	while((rec = utmp_next()) != NULL) {
		// User id found. Print and exit the loop.
		if(rec->ut_type == USER_PROCESS) {
			show_info(rec);	
			break;
		}
	}

	utmp_close();
	return 0;
}

void show_info(struct utmp *rec) {
	printf("%-*.*s\n", UT_NAMESIZE, UT_NAMESIZE, rec->ut_user);
}
