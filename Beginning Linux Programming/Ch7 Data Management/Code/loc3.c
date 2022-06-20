#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

const char *file_path = "./tmp.txt";

int main(int argc, char** argv) {
	int fd, byte_count = 0;
	struct flock lock1, lock2;
	const char *to_write_str = "A";

	if ((fd = open(file_path, O_CREAT | O_RDWR, 0777)) == 0) {
		printf("Open %s failed.\n", file_path);
		exit(1);
	}
	
	for(; byte_count < 100; ++byte_count)
		write(fd, to_write_str, sizeof(char));

	// Lock byte 10 to 20
	lock1.l_type = F_RDLCK;
	lock1.l_whence = SEEK_SET;
	lock1.l_start = 10;
	lock1.l_len = 10;
	if (fcntl(fd, F_SETLK, &lock1) == -1)
		fprintf(stderr, "Lock 1 fails to lock file %s\n", file_path);
	printf("%d locks byte 10 to 20 \n", getpid());


	// Lock byte 50 to 70
	lock2.l_type = F_WRLCK;
	lock2.l_whence = SEEK_SET;
	lock2.l_start = 50;
	lock2.l_len = 20;
	if (fcntl(fd, F_SETLK, &lock2) == -1)
		fprintf(stderr, "Lock 2 fails to lock file %s\n", file_path);
	printf("%d locks byte %d to %d\n", getpid(), lock2.l_start, lock2.l_start + lock2.l_len);
	sleep(60);

	close(fd);

	return 0;
}