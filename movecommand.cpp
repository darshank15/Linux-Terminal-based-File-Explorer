#include "myheader.h"

void movecommand(vector<string> list)
{
	unsigned int len = list.size();
	if(len < 3)
	{
		showError("Less number of Argument in move command !!!");
	}
	else{

		for(unsigned int i=1;i<len-1;i++)
		{			
			string newData = list[i];
			string name = getFileNameFromPath(list[i]);
			//cout<<"\nfilename : "<<name;

			string destpath= list[len-1];
			destpath =destpath + "/" + name;
			char *des = new char[destpath.length() + 1];
			strcpy(des, destpath.c_str());
			//cout<<"\ndespath in copy : "<<des<<endl;
	
			char *path = new char[newData.length() + 1];
			strcpy(path, newData.c_str());
			if(isdirectory(path))
			{
				copydirectory(path,des);
				removeSingleDirectory(path);
			}
			else
			{
				copyfile(path,des);
				removeSingleFile(path);
			}
		}
	}
}