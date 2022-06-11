#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

void work() {
	FILE *f;
	int i;
	double x = 4.5;
	f = tmpfile();
	for (i = 0; i < 10000; ++i) {
		fprintf(f, "Do some output.\n");
		if (ferror(f)) {
			fprintf(stderr, "Error writing to tmp file.\n");
			exit(1);
		}
	}

	for (i = 0; i < 1000000; ++i)
		x = log(x * x + 3.21);
}

int main(int argc, char** argv) {
	struct rusage r_usage;
	int priority;
	struct rlimit r_limit;

	work();
	getrusage(RUSAGE_SELF, &r_usage);
	printf("Process %d\nCPU usage: User = %ld.%06ld, System = %ld.%06ld\n", getpid(), r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec, r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);

	priority = getpriority(PRIO_PROCESS, getpid());
	printf("Current priority: %d\n", priority);

	getrlimit(RLIMIT_FSIZE, &r_limit);
	printf("Current FSIZE limit: soft = %ld, hard = %ld\n", r_limit.rlim_cur, r_limit.rlim_max);
	r_limit.rlim_cur = 2048;
	r_limit.rlim_cur = 4096;
	printf("Setting a 2K file size limit.\n");
	setrlimit(RLIMIT_FSIZE, &r_limit);

	work();
	return 0;
}