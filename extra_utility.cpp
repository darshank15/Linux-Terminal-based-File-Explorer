/************************************************************************
**      RollNo:2018201033          Name : Darshan Kansagara			   **
************************************************************************/

//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Function to handle goto Directory Part
//**********************************************************************
string gotoPath(vector<string> list)
{
		string str="";
		if(list.size()!=2)
		{
			showError("Invalid Argument in Goto");
		}
		else{
			str= list[1];
		}
		return str;
}

//**********************************************************************
// This Function returns whether given path is of directory or file
//**********************************************************************
int isdirectory(char *newpath)
{
	struct stat sb;
	if (stat(newpath,&sb) == -1) {
        perror("lstat");
    }
    else
    {
    	if((S_ISDIR(sb.st_mode)))
	    {
	    	return 1;
	    }
	    else
	    {
	    	return 0;
	    }
    }

    return -1;
}

//**********************************************************************
// This Function extract filename from its full path
//**********************************************************************
string getFileNameFromPath(string newData)
{
	string name;
	size_t pos;
	pos = newData.find_last_of("/\\");
	name = newData.substr(pos+1,newData.length());
	//cout<<"\nfilename : "<<name;
	return name;
}

//**********************************************************************
// This Function used to display error in Red Formate
//**********************************************************************
void showError(string str)
{
	clearCommand();
	cout<<"\033[0;31m"<<str<<endl;
	cout<<"\033[0m";
}