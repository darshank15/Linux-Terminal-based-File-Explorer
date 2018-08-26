#include "myheader.h"

unsigned int rowsize,colsize;

int getFilePrintingcount()
{
	int lenRecord;
	struct winsize win;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	rowsize = win.ws_row-1;
	colsize = win.ws_col;
	if(totalFiles <= rowsize)
		lenRecord = totalFiles;
	else
	{
		lenRecord = rowsize;
	}
	return lenRecord;
}