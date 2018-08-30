/************************************************************************
**      RollNo:2018201033          Name : Darshan Kansagara			   **
************************************************************************/

/************************************************************************
**      This File is for includeing all header file ,extern            **    
**      variables and global function required by other cpp files.     **
**                                                                     **
************************************************************************/


//**********************************************************************
// All Header file included/imported here
//**********************************************************************
#include<bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
using namespace std;

//**********************************************************************
// Declaring extern global variables
//**********************************************************************
extern char *root;
extern char* curPath;
extern char* pathbeforeSearch;
extern vector< string > dirList;
extern stack <string> back_stack;
extern stack <string> forw_stack;
extern unsigned int rowsize,colsize;
extern unsigned int totalFiles;
extern int wintrack;


//**********************************************************************
// Declaring global method
//**********************************************************************
void openDirecoty(const char *path);
void display(const char *dirName, const char *root);
int getFilePrintingcount();
void clearStack(stack<string> &s);
void navigate();

int isdirectory(char *newpath);
string getFileNameFromPath(string newDataw);

int startCommandMode();
void clearCommand();
string pathProcessing(string str);
void createNewFiles(vector<string> list);
void createSingleFile(char *path);
void makeDirectories(vector<string> list);
void removeDirectories(vector<string> list);
void removeSingleDirectory(char *path);
void removeFiles(vector<string> list);
void removeSingleFile(char *path);
void renameFiles(vector<string> list);
string gotoPath(vector<string> list);
void copycommand(vector<string> list);
void copydirectory(char *path,char *des);
void copyfile(char *path,char *des);
void movecommand(vector<string> list);
void takesnapshot(vector<string> list);
void takeDirSnapshot(char *path, char *dump);
int searchcommand(vector<string> list);
void searchanything(char *path,string filename);
void showError(string str);
