#include "myheader.h"

void makeDirectory(vector<string> list)
{
	for(unsigned int i=1;i<list.size();i++)
	{
		 char *path = new char[list[i].length() + 1];
		 strcpy(path, list[i].c_str());
		 int status= mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		 if(-1 == status)
		 {
		 	printf("Error in creating the Directory !!!");
		 }
	}
}