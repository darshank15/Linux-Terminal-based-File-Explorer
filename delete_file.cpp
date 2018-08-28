#include "myheader.h"

//**********************************************************************
// This function is to remove single file 
//**********************************************************************
void removeSingleFile(char *path)
{
	//cout<<"path for deleting file : "<<path<<endl;
	int status= remove(path);
	 if(status != 0)
	 {
	 	printf("\nError in removing the File with path ::::: %s",path);
	 }
	
}

//**********************************************************************
// It removes multiple files that passed by User in argument
//**********************************************************************
void removeFiles(vector<string> list)
{
	for(unsigned int i=1;i<list.size();i++)
	{
		 char *path = new char[list[i].length() + 1];
		 strcpy(path, list[i].c_str());
		 removeSingleFile(path);
	}	 
}

void createSingleFile(char *path)
{
		cout<<"\ncreateSingleFile path : "<<path<<endl;
		open(path,O_RDWR); 
}

void createNewFiles(vector<string> list)
{

	for(unsigned int i=1;i<list.size();i++)
	{
		 char *path = new char[list[i].length() + 1];
		 strcpy(path, list[i].c_str());
		 createSingleFile(path);
	}			
}
