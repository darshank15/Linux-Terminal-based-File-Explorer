#include "myheader.h"

char *root;
stack <string> bkspace_stack;

int main(int argc, char *argv[])
{
	//
	if(argc == 1)
	{
		string s=".";
		char* path = new char[s.length() + 1];
		strcpy(path, s.c_str());
		root = path;
		openDirecoty(".");	
	}
	else if(argc == 2){
		root= argv[1];
		openDirecoty(argv[1]);		
	}
	else{
		cout<<"Invalid Argument !!!"<<endl;
	}
	navigate();
	//checkFile();
	//chmod("Assi-1.cpp", S_IRWXU|S_IRWXG|S_IROTH|S_IWOTH);
	//int mkdir(const char *path, mode_t mode)                      page No: 121 
	//int rmdir(const char *path);
	return 0;
}
