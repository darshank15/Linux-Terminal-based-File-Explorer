#include "myheader.h"

char *root;

void checkFile()
{
	struct stat sb;
	stat("FileName",&sb);
	if((sb.st_mode & S_IFMT) == S_IFDIR) {
		cout<<"DIR"<<endl;
	}
	else if((sb.st_mode & S_IFMT) == S_IFREG)
	{
		cout<<"FILE"<<endl;
	}
	else{
		cout<<"unknown?"<<endl;
	}

  // printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	// if (S_ISREG(mode))
 //        c = '-';
 //    else if (S_ISDIR(mode))
 //        c = 'd';
 //    else if (S_ISBLK(mode))
 //        c = 'b';
 //    else if (S_ISCHR(mode))
 //        c = 'c';
		  
}

int main(int argc, char *argv[])
{
	
	if(argc == 1)
	{
		openDirecoty(".");	
	}
	else if(argc == 2){
		root= argv[1];
		openDirecoty(argv[1]);		
	}
	else{
		cout<<"Invalid Argument !!!"<<endl;
	}
	//checkFile();
	//chmod("Assi-1.cpp", S_IRWXU|S_IRWXG|S_IROTH|S_IWOTH);
	//int mkdir(const char *path, mode_t mode)                      page No: 121 
	//int rmdir(const char *path);
	return 0;
}
