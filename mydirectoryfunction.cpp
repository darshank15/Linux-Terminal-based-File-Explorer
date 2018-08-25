#include "myheader.h"
vector< string > dirList;

//************************************************************************
// function to open Directory Content
//************************************************************************
void openDirecoty(const char *path)
{
	dirList.clear();
	DIR *d;
	struct dirent *dir;
	printf("\033[H\033[J");
	printf("%c[%d;%dH",27,1,1);
	d = opendir(path);
	//printf("\n");
	if (d) {

	    while ((dir = readdir(d)) != NULL) {
	      //printf("\n%-10s", dir->d_name);
	      if( (string(dir->d_name) == "..") && (strcmp(path,root) == 0))	
	      {   } 
	  	  else{

	  	  		dirList.push_back(string(dir->d_name));	
	      		display((dir->d_name), path);
	  	   }

	    }

	    closedir(d);
	}
	else{
		//perror(d);
	}
	printf("%c[%d;%dH",27,0,1);
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
    printf(  (S_ISDIR(sb.st_mode)) ? "d" : "-");
	printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
	printf("\t%10.2fK", ((double) sb.st_size)/1024);
	char *tt=(ctime(&sb.st_mtime));
	tt[strlen(tt)-1]='\0';
	printf("\t%s",tt);
	printf("\t%-20s \n",dirName);
}
