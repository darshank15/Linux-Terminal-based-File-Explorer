#include "myheader.h"

//**********************************************************************
// This function recursively remove all file and dir inside it.
// and finally delete dir itself
//**********************************************************************
void removeSingleDirectory(char *path)
{
	int status= rmdir(path);
	 if(-1 == status)
	 {
	 	printf("\nError in removing the Directory with path ::: %s",path);
	 }
	
}

//**********************************************************************
// It removes multiple directory that passed by User in argument
//**********************************************************************
void removeDirectory(vector<string> list)
{
	for(unsigned int i=1;i<list.size();i++)
	{
		 char *path = new char[list[i].length() + 1];
		 strcpy(path, list[i].c_str());
		 removeSingleDirectory(path);
	}	 
}