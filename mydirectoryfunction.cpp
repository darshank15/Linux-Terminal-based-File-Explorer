/************************************************************************
** RollNo:2018201033  Name : Darshan Kansagara						   **
************************************************************************/

//**********************************************************************
// Header file included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Declaration of global variables
//**********************************************************************
vector<string> dirList;
unsigned int totalFiles;
int wintrack;
int searchflag = 0;

//**********************************************************************
// Method returns total number of files + Directory withing given path
//**********************************************************************
int getDirectoryCount(const char *path)
{
	int count = 0;
	dirList.clear();
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			//printf("\n%-10s", dir->d_name);
			if ((string(dir->d_name) == "..") && (strcmp(path, root) == 0))
			{
			}
			else
			{
				dirList.push_back(string(dir->d_name));
				count++;
			}
		}
		closedir(d);
	}
	else
	{
		showError("No such Directory Exist:::");
	}
	return count;
}

//************************************************************************
// function that prints directory/file within given terminal size
//************************************************************************
void openDirecoty(const char *path)
{
	DIR *d;
	d = opendir(path);
	if (!d)
	{
		int lastLine = rowsize + 1;
		printf("%c[%d;%dH",27,lastLine,1);
		printf("%c[2K", 27);
		cout<<":";
		showError("Ops something wrong to open Dir :::"+string(path));
		return;
	}
	//cout << "openDir Path : " << path << endl;
	dirList.clear();
	totalFiles = getDirectoryCount(path);
	unsigned int len = getFilePrintingcount();
	sort(dirList.begin(), dirList.end());
	wintrack = 0;
	printf("\033[H\033[J");
	printf("%c[%d;%dH", 27, 1, 1);

	for (unsigned int i = 0, itr = 1; i < totalFiles && itr <= len; i++, itr++)
	{
		char *tempFileName = new char[dirList[i].length() + 1];
		strcpy(tempFileName, dirList[i].c_str());
		display(tempFileName, path);
	}

	printf("%c[%d;%dH", 27, 1, 80);
}

//************************************************************************
// function to display file/Directory's MetaDta
//************************************************************************
void display(const char *dirName, const char *root)
{
	string finalpath;
	if (searchflag == 1)
	{
		finalpath = string(dirName);
	}
	else
	{
		finalpath = string(root) + "/" + string(dirName);
	}
	char *path = new char[finalpath.length() + 1];
	strcpy(path, finalpath.c_str());
	//cout<<"Display path : "<<path<<"     ";;
	struct stat sb;
	if (stat(path, &sb) == -1)
	{
		perror("lstat");
	}

	printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
	printf((sb.st_mode & S_IRUSR) ? "r" : "-");
	printf((sb.st_mode & S_IWUSR) ? "w" : "-");
	printf((sb.st_mode & S_IXUSR) ? "x" : "-");
	printf((sb.st_mode & S_IRGRP) ? "r" : "-");
	printf((sb.st_mode & S_IWGRP) ? "w" : "-");
	printf((sb.st_mode & S_IXGRP) ? "x" : "-");
	printf((sb.st_mode & S_IROTH) ? "r" : "-");
	printf((sb.st_mode & S_IWOTH) ? "w" : "-");
	printf((sb.st_mode & S_IXOTH) ? "x" : "-");

	//stat(filename, &info);  // Error check omitted
	struct passwd *pw = getpwuid(sb.st_uid);
	struct group *gr = getgrgid(sb.st_gid);
	if (pw != 0)
		printf("\t%-8s", pw->pw_name);
	if (gr != 0)
		printf(" %-8s", gr->gr_name);

	printf("%10.2fK", ((double)sb.st_size) / 1024);
	char *tt = (ctime(&sb.st_mtime));
	tt[strlen(tt) - 1] = '\0';
	printf("%30s", tt);
	if(S_ISDIR(sb.st_mode))
	{
		printf("\033[1;32m");
		printf("\t%-20s\n", dirName);
		printf("\033[0m");
	}
	else
		printf("\t%-20s\n", dirName);
}
