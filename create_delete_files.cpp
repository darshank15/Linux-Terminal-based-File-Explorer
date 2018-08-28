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
	 	showError("Error in removing the File with path ::::: "+string(path));
	 }
	
}

//**********************************************************************
// It removes multiple files that passed by User in argument
//**********************************************************************
void removeFiles(vector<string> list)
{	
	if(list.size()<2)
	{
		 showError("Less number of Argument in delete_file command");
	}
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
		int status=open(path,O_RDONLY | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ); 	
		if (status ==-1)
	    {
			 showError("Error in creating new file path :::::  " + string(path));	       
	    }
}

void createNewFiles(vector<string> list)
{

	if(list.size() < 3)
	{
		showError("Less Number of Argument in Renaming !!!");
		return ;
	}
	unsigned int len=list.size();
	string destpath= pathProcessing(list[len-1]);
	cout<<"\ndestpath : "<<destpath<<endl;
	for(unsigned int i=1;i<len-1;i++)
	{
		 string fileName = destpath + "/" + list[i];
		 char *path = new char[fileName.length() + 1];
		 strcpy(path, fileName.c_str());
		 createSingleFile(path);
		 
	}
		
}

void renameFiles(vector<string> list)
{
	if(list.size()!=3)
	{
		showError("Invalid Argument in Renaming !!!");
	}
	else{
		string initName = list[1];
		string finalName = list[2];
		rename(initName.c_str(),finalName.c_str());
	}
	
}