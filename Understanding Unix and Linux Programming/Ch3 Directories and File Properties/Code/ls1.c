#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>


void do_ls(char*);

int main(int argc, char* argv[]) {
	if(argc == 1)
		do_ls(".");
	else
		while(--argc) {
			do_ls(*(++argv));
		}
	return 0;
}

void do_ls(char* dir_name) {
	DIR* directory;
	struct dirent* file_ptr;
	if((directory = opendir(dir_name)) == NULL)
		fprintf(stderr, "Directory open failed");
	else{
		while((file_ptr = readdir(directory)) != NULL) {
			printf("%s\n", file_ptr->d_name);	
		}
		closedir(directory);
	} 
}
