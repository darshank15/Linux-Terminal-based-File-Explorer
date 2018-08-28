//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// This Function used to create directory(s) 
//**********************************************************************
void makeDirectories(vector<string> list)
{
	
	unsigned int len=list.size();
	if(list.size() <= 2)
	{
		showError("Lesser Number of Argument in create_dir!!!");
	}
	else{
		string destpath= pathProcessing(list[len-1]);
		//cout<<"\ndestpath : "<<destpath<<endl;
		for(unsigned int i=1;i<len-1;i++)
		{
			 string dir = destpath + "/" + list[i];
			 char *path = new char[dir.length() + 1];
			 strcpy(path, dir.c_str());
			 //cout<<"\nmkdir name :"<<dir<<endl;
			 int status= mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			 if(-1 == status)
			 {
			 	showError("Error in creating the Directory in path :::::  "+string(path));
			 }
		}	
	}
	
}