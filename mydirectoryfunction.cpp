#include "myheader.h"

//************************************************************************
// function to open Directory Content
//************************************************************************
void openDirecoty(const char *path)
{
	DIR *d;
	struct dirent *dir;
	system("clear");
	d = opendir(path);
	if (d) {

	    while ((dir = readdir(d)) != NULL) {
	      //printf("\n%-10s", dir->d_name);
	      display((dir->d_name), path);
	    }

	    closedir(d);
	}
	else{
		cout<<"No such Directiory Exist !!!"<<endl;
	}
}


//************************************************************************
// function to display file/Directory's MetaDta
//************************************************************************
void display(const char *dirName, const char *root)
{
	string finalpath=string(root) + "/" +string(dirName);;
	char* path = new char[finalpath.length() + 1];
	strcpy(path, finalpath.c_str());
	//cout<<finalpath<<endl;
	//cout<<path<<endl;

	struct stat sb;
	if (stat(path,&sb) == -1) {
               perror("lstat");
    }
	
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
