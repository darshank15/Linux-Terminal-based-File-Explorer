//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

vector<string> searchResult;

//**********************************************************************
// It match two file name are same or not
//**********************************************************************
int isNameMatch(string tobesearch, string name)
{
	if (tobesearch == name)
		return 1;
	else
		return 0;
}

//**********************************************************************
// This function used to print the search Data
//**********************************************************************
void printsearchData()
{
	totalFiles = dirList.size();
	unsigned int len = getFilePrintingcount();
	sort(dirList.begin(), dirList.end());
	wintrack = 0;
	printf("\033[H\033[J");
	printf("%c[%d;%dH", 27, 1, 1);

	for (unsigned int i = 0, itr = 1; i < totalFiles && itr <= len; i++, itr++)
	{
		cout << dirList[i] << endl;
	}

	printf("%c[%d;%dH", 27, 1, 1);
}

//**********************************************************************
// It searches given filename into its recursive subfolder 
// if filename found push its absolute path into searchResult vector
//**********************************************************************
void searchanything(char *path, string filename)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if ((string(dir->d_name) == "..") || (string(dir->d_name) == "."))
			{
			}
			else
			{
				string name = string(dir->d_name);
				string finalpath = string(path) + "/" + name;
				char *newpath = new char[finalpath.length() + 1];
				strcpy(newpath, finalpath.c_str());

				struct stat sb;
				if (stat(newpath, &sb) == -1)
				{
					perror("lstat");
				}
				else
				{

					if ((S_ISDIR(sb.st_mode)))
					{
						if (isNameMatch(filename, name))
						{
							searchResult.push_back(string(newpath));
						}
						searchanything(newpath, filename);
					}
					else
					{
						if (isNameMatch(filename, name))
						{
							searchResult.push_back(string(newpath));
						}
					}
				}
			}
		}
	}
	else
	{

		showError("No such Directory path Exist while searching !!!");
	}
}

//**********************************************************************
//This function process search argument given by user & display results
//**********************************************************************
int searchcommand(vector<string> list)
{
	searchResult.clear();
	unsigned int len = list.size();
	if (len != 2)
	{
		showError("Less number of Argument in search command !!!");
		return 0;
	}
	else
	{
		string filename = list[1];
		char *path = new char[strlen(curPath) + 1];
		strcpy(path, curPath);
		//cout<<"\npath : "<<path<<endl;
		//cout<<"\nfilename : "<<filename<<endl;
		searchanything(path, filename);

		if (searchResult.size() < 1)
		{
			showError("No search result found  for file/Dir ::::: " + filename);
			return 0;
		}
		else
		{
			back_stack.push(string(curPath));
			clearStack(forw_stack);

			string emptypath = "";
			strcpy(curPath, emptypath.c_str());

			dirList.clear();
			dirList = searchResult;
			printsearchData();
		}
	}

	return 1;
}
