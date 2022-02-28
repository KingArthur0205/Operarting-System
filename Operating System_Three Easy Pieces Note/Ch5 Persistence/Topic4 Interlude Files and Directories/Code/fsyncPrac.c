#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>

int main() {
	int fd = open("./foo.txt", O_CREAT|O_TRUNC|O_WRONLY);
	assert(fd > -1);
	int rc = write(fd, "Hello", 6);
	assert(rc == 6);
	rc = fsync(fd);
	assert(rc == 0);
	return 0;
}
