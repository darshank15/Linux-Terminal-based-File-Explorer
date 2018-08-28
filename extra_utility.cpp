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
			cout<<"\nInvalid Argument in Goto :::::"<<endl;
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