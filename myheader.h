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
#include <string>
#include <stdio.h>
#include <stdlib.h>
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
void navigate();

void startCommandMode();
string pathProcessing(string str);
void createNewFiles(vector<string> list);
void createSingleFile(char *path);
void makeDirectories(vector<string> list);
void removeDirectories(vector<string> list);
void removeSingleDirectory(char *path);
void removeFiles(vector<string> list);
void removeSingleFile(char *path);