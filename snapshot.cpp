//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

//*************************************************************************
// This function recursively traverse dir and append files
//				and dirs name into dump file
//*************************************************************************
void takeDirSnapshot(char *path, char *dump)
{
	vector<string> dirv;
	vector<string> content;
	fstream fs;
	fs.open(dump, fstream::app);

	fs << endl << path << endl;

	DIR *dp;
	struct dirent *dir;
	if ((dp = opendir(path)) == NULL)
	{
		showError("Can not open FolderPath while snapshot:::::" + string(path));
		return;
	}
	while ((dir = readdir(dp)) != NULL)
	{

		if ((string(dir->d_name) == "..") || (string(dir->d_name) == "."))
		{
		}
		else
		{
			string name = string(dir->d_name);
			content.push_back(name);
			string finalpath = string(path) + "/" + name;
			char *newpath = new char[finalpath.length() + 1];
			strcpy(newpath, finalpath.c_str());
			if (isdirectory(newpath))
			{
				dirv.push_back(finalpath);
			}
		}
	}
	for (unsigned int i = 0; i < content.size(); i++)
	{
		fs << endl << "\t" << left << content[i];
	}
	fs << endl;
	fs.close();
	for (unsigned int i = 0; i < dirv.size(); i++)
	{
		string popdir = dirv[i];
		char *popdirpath = new char[popdir.length() + 1];
		strcpy(popdirpath, popdir.c_str());
		takeDirSnapshot(popdirpath, dump);
	}
	closedir(dp);
}

//**********************************************************************
// Function process argument provided by user and handle error if any
//**********************************************************************
void takesnapshot(vector<string> list)
{
	unsigned int len = list.size();
	if (len < 3)
	{
		showError("Less number of Argument in snapshot command !!!");
	}
	else
	{
		string foldername = list[1];
		string dumpfilename = list[2];
		char *path = new char[foldername.length() + 1];
		strcpy(path, foldername.c_str());

		char *dumppath = new char[dumpfilename.length() + 1];
		strcpy(dumppath, dumpfilename.c_str());
		createSingleFile(dumppath);
		ofstream ofs;
		ofs.open(dumppath, ofstream::out | ofstream::trunc);
		ofs.close();
		takeDirSnapshot(path, dumppath);
	}
}