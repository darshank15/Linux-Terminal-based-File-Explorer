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

string getFileNameFromPath(string newData)
{
	string name;
	size_t pos;
	pos = newData.find_last_of("/\\");
	name = newData.substr(pos+1,newData.length());
	//cout<<"\nfilename : "<<name;
	return name;
}

void showError(string str)
{
	clearCommand();
	cout<<str<<endl;
}