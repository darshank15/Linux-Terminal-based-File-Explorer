#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>
//#include <string.h> 

using namespace std;

extern char *root;
extern vector< string > dirList;
extern stack <string> back_stack;
extern stack <string> forw_stack;
extern unsigned int rowsize,colsize;
extern unsigned int totalFiles;
extern int wintrack;


void openDirecoty(const char *path);
void display(const char *dirName, const char *root);
int getFilePrintingcount();
void navigate();