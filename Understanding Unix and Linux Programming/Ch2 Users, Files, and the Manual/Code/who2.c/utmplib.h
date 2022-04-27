/**
 * Library functions for buffered read/write of utmp records.
 * int utmp_open(char*): Open the provided file. Set cur_rec and rec_num. Return the file descriptor
 * int utmp_reload(): Return the number of utmp records read. Set rec_num and cur_rec. 
 * struct utmp *utmp_next(): Return the utmp record denoted by index. If empty or read fails, return NULL_UTMP
 * void utmp_close(): Close the file descriptor
 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <stdlib.h>

#define NULL_UTMP ((struct utmp*)NULL)
#define UTMP_SIZE sizeof(struct utmp)
#define CAPACITY 16

struct utmp utmp_buffer[CAPACITY];
int cur_rec; /* The current utmp index. */
int rec_num; /* The number of utmp records in the buffer. */
int utmp_fd;

int utmp_open(char *file_name) {
	utmp_fd = open(file_name, O_RDONLY);
	cur_rec = rec_num = 0;
	return utmp_fd;
}

int utmp_reload() {
	// Attempt to read CAPACITY utmp records into the buffer.
	int amt_read = read(utmp_fd, utmp_buffer, CAPACITY * UTMP_SIZE);
	// Actual number of utmp records read.
	rec_num = amt_read / UTMP_SIZE;
	// Reset the cur_rec.
	cur_rec = 0;
	return rec_num; 
}

struct utmp* utmp_next() {
	// Check the file descriptor to be valid
	if(utmp_fd == -1)
		return NULL_UTMP;
	// Check empty or read fails
	if(cur_rec == rec_num && utmp_reload() == 0)
		return NULL_UTMP;

	// Get address of the next record.
	struct utmp *recp;
	recp = &utmp_buffer[cur_rec++];
	return recp;
}

void utmp_close() {
	// Check if utmp_fd is valid
	if(utmp_fd != -1)
		close(utmp_fd);
}
