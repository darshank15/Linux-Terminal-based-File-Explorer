//**********************************************************************
// Header file
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Global variable Declaration area
//**********************************************************************
char *root;
stack <string> back_stack;
stack <string> forw_stack;

//**********************************************************************
// Main Method
//**********************************************************************
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

	//Start Navigating through Command prompt
	navigate();


	//checkFile();
	//chmod("Assi-1.cpp", S_IRWXU|S_IRWXG|S_IROTH|S_IWOTH);
	//int mkdir(const char *path, mode_t mode)                      page No: 121 
	//int rmdir(const char *path);
	
	return 0;
}
