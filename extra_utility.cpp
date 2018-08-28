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

void showError(string str)
{
	clearCommand();
	cout<<str<<endl;
}