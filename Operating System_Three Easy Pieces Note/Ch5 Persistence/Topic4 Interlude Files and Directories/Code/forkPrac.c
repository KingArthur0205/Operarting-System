#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
	int fd = open("./foo.txt", O_RDONLY);
	assert(fd >= 0);

	int rc = fork();
	if(rc == 0) {
		rc = lseek(fd, 3, SEEK_SET);
		printf("Child: offset %d\n", rc);
	} else if(rc > 0) {
		(void)wait(NULL);
		printf("Parent: offset %d\n", (int)lseek(fd, 0, SEEK_CUR));
	}
	return 0;
}
