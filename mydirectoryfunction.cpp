#include "myheader.h"

//************************************************************************
// function to open Directory Content
//************************************************************************
void openDirecoty(const char *dirName)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(dirName);
	if (d) {

	    while ((dir = readdir(d)) != NULL) {
	      //printf("\n%-10s", dir->d_name);
	      display(dir->d_name);
	    }

	    closedir(d);
	}
}


//************************************************************************
// function to display file/Directory's MetaDta
//************************************************************************
void display(const char *dirName)
{
	struct stat sb;
	stat(dirName,&sb);
	 	
		printf("\n");
		printf("%-20s",dirName);
		printf("\t");
		printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
	    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
    	printf("\t%10lld bytes", (long long) sb.st_size);
    	printf("\t%s ",ctime(&sb.st_mtime));	
}
