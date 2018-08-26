//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Global declaration
//**********************************************************************
unsigned int rowsize,colsize;


//**********************************************************************
// Method returns count of maximun file to be printed on terminal
//**********************************************************************
int getFilePrintingcount()
{
	int lenRecord;
	struct winsize win;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	rowsize = win.ws_row-1;
	colsize = win.ws_col;
	if(totalFiles <= rowsize) {
		lenRecord = totalFiles;
	}
	else {
		lenRecord = rowsize;
	}
	return lenRecord;
}