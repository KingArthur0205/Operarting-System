#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_dir(const char* dir_path, int depth) {
	DIR *cur_dir;
       if ((cur_dir = opendir(dir_path)) == NULL) {
	       fprintf(stderr, "Fail to open directory: %s\n", dir_path);
	       return;
	}

       chdir(dir_path);

       struct dirent *file;
       struct stat file_stat;
       while ((file = readdir(cur_dir)) != NULL) {
		     lstat(file->d_name, &file_stat);
		     if (S_ISDIR(file_stat.st_mode)) {
			     if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
				     continue;
			     printf("%*s%s/\n", depth, "",  file->d_name);
			     print_dir(file->d_name, depth + 4);
		     } 
		     else {
		     	printf("%*s%s\n", depth, "", file->d_name);	
		     }
       }
       chdir("..");
       closedir(cur_dir);

}

int main(int argc, char** argv) {
	char* dir_path = "./";
	print_dir(dir_path, 0);
	return 0;
}