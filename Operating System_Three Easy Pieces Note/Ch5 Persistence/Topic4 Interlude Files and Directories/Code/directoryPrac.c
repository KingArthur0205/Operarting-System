#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	DIR *dp = opendir(".");
	assert(dp != NULL);

	struct dirent *d;
	while((d = readdir(dp)) != NULL) {
		printf("Ino_Number:%lu Name:%s\n", (unsigned long)d->d_ino, d->d_name);
	}
	closedir(dp);
	return 0;
}
