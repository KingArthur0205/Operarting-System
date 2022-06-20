/*
 * Run loc3.c before this program.
 * Use loc3 & lock_test to test for the lock
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_TO_ADD 5

const char *file_path = "./tmp.txt";

void show_lock_info(struct flock *lock) {
	printf("\tl_type: %d\t", lock->l_type);
	printf("l_whence: %d\t", lock->l_whence);
	printf("l_start: %ld\t", lock->l_start);
	printf("l_len: %ld\t", lock->l_len);
	printf("l_pid: %d\n", lock->l_pid);
}

int main(int argc, char** argv) {
	int fd;
	struct flock region_to_test;

	if ((fd = open(file_path, O_CREAT | O_RDWR, 0666)) == 0) {
		fprintf(stderr, "Fail to open file %s.\n", file_path);
		exit(1);
	}

	int byte_start = 0;
	for(; byte_start < 99; byte_start += SIZE_TO_ADD) {
		region_to_test.l_type = F_WRLCK;
		region_to_test.l_whence = SEEK_SET;
		region_to_test.l_start = byte_start;
		region_to_test.l_len = SIZE_TO_ADD;
		region_to_test.l_pid = -1;

		printf("Test lock on region %d to %d\n", byte_start, byte_start + SIZE_TO_ADD);
		if (fcntl(fd, F_GETLK, &region_to_test) == -1) {
			fprintf(stderr, "Fail to obtain information about the lock.\n");
			exit(1);
		}

		if (region_to_test.l_pid != -1) {
			printf("Lock would fail. Information about the lock:\n");
			show_lock_info(&region_to_test);
		}
		else {
			printf("F_WRLCK - Lock would succeed.\n");
		}
	}

	close(fd);

	return 0;
}