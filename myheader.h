#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include<termios.h>

using namespace std;

extern char *root;
extern vector< string > dirList;
extern stack <string> bkspace_stack;


void openDirecoty(const char *path);
void display(const char *dirName, const char *root);

void navigate();