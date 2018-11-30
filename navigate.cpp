/************************************************************************
**      RollNo:2018201033          Name : Darshan Kansagara			   **
************************************************************************/

//**********************************************************************
// This File is used to navigate through using arrow key,Home,Enter
// backspace and allow scrolling through list
//**********************************************************************

//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Global Declaration & #defined macros
//**********************************************************************
unsigned int xcor = 1, ycor = 80;
char *curPath;
#define esc 27
#define cls printf("%c[2J", esc)
#define pos() printf("%c[%d;%dH", esc, xcor, ycor)
#define posx(x,y) printf("%c[%d;%dH", esc, x, y)

//**********************************************************************
// Method that update current path when backspace key pressed
//**********************************************************************
void setBackPath(char *path)
{
	size_t pos;
	string newPath;
	string tempPath = string(path);
	pos = tempPath.find_last_of("/\\");
	newPath = tempPath.substr(0, pos);
	strcpy(curPath, newPath.c_str());
}

//**********************************************************************
// This Method Clear the stack contents
//**********************************************************************
void clearStack(stack<string> &s)
{
	while (!s.empty())
	{
		s.pop();
	}
}

//**********************************************************************
// Method for navigation on key press in a Normal mode
//**********************************************************************
void navigate()
{

	curPath = root;
	xcor = 1, ycor = 80;
	pos();
	char ch;

	struct termios initialrsettings, newrsettings;
	tcgetattr(fileno(stdin), &initialrsettings);
	//switch to canonical mode and echo mode
	newrsettings = initialrsettings;
	newrsettings.c_lflag &= ~ICANON;
	newrsettings.c_lflag &= ~ECHO;

	if (tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0)
	{
		fprintf(stderr, "Could not set attributes\n");
	}
	else
	{

		while (1)
		{
			int lastLine = rowsize + 1;
			posx(lastLine,1);
			cout << "-----NORMAL MODE-----";
			pos();

			ch = cin.get();
			if (ch == 27)
			{
				ch = cin.get();
				ch = cin.get();

				//If UP-arrow Key press
				if (ch == 'A')
				{
					if (xcor + wintrack > 1)
					{
						xcor--;
						if (xcor > 0)
						{
							pos();
						}
						else if (xcor <= 0 && xcor + wintrack >= 1)
						{
							cls;
							if (wintrack > 0)
							{
								wintrack--;
							}
							//cout<<"wintrack : "<<wintrack<<"***********";
							posx(1,1);
							for (unsigned int i = wintrack; i <= rowsize + wintrack - 1; i++)
							{
								char *tempFileName = new char[dirList[i].length() + 1];
								strcpy(tempFileName, dirList[i].c_str());
								display(tempFileName, curPath);
							}
							xcor++;
							pos();
						}
					}
				}
				//If DOWN-arrow Key press
				else if (ch == 'B')
				{
					//cout<<"\n*******************DOWN";
					int lenRecord;
					if (xcor + wintrack < (totalFiles))
					{
						xcor++;
						if (xcor <= rowsize)
						{
							pos();
						}
						else if (xcor > rowsize && xcor + wintrack <= totalFiles)
						{
							cls;
							lenRecord = getFilePrintingcount() - 1;
							if (totalFiles > rowsize)
							{
								wintrack++;
							}
							//cout<<"wintrack : "<<wintrack<<"***********";
							posx(1,1);
							for (int i = wintrack; i <= lenRecord + wintrack; i++)
							{
								char *tempFileName = new char[dirList[i].length() + 1];
								strcpy(tempFileName, dirList[i].c_str());
								display(tempFileName, curPath);
							}
							xcor--;
						}
						pos();
					}
				}
				//If RIGHT-arrow Key press
				else if (ch == 'C')
				{
					//cout<<"RIGHT"<<endl;
					if (!forw_stack.empty())
					{
						string cpath = string(curPath);
						if(searchflag!=1)
							back_stack.push(string(curPath));
						string top = forw_stack.top();
						forw_stack.pop();
						strcpy(curPath, top.c_str());
						//cout<<"******* RIGHT: "<<curPath;
						searchflag=0;
						openDirecoty(curPath);
						xcor = 1, ycor = 80;
						pos();
					}
				}
				//If LEFT-arrow Key press
				else if (ch == 'D')
				{
					//cout<<"LEFT"<<endl;
					if (!back_stack.empty())
					{
						string cpath = string(curPath);
						if(searchflag!=1)
							forw_stack.push(string(curPath));
						string top = back_stack.top();
						back_stack.pop();
						strcpy(curPath, top.c_str());
						searchflag=0;
						//cout<<"******* : LEFT"<<curPath;
						openDirecoty(curPath);
						xcor = 1, ycor = 80;
						pos();
					}
				}
				else
				{
				}
			}
			//If HOME key pressed
			else if (ch == 104 || ch == 72)
			{
				string cpath = string(curPath);
				if(cpath!=string(root))
				{
					if(searchflag!=1)
						back_stack.push(string(curPath));
					clearStack(forw_stack);
					strcpy(curPath, root);
					searchflag=0;
					openDirecoty(curPath);
					xcor = 1, ycor = 80;
					pos();
				}
				
			}
			//If Back-Space key pressed
			else if (ch == 127)
			{
				//cout<<"*************curPathr"<<curPath<<"***********";
				string cpath = string(curPath);
				if ((strcmp(curPath, root) != 0) && searchflag!=1)
				{
					//cout<<"**************Root : "<<root<<"***********";
					back_stack.push(curPath);
					clearStack(forw_stack);
					setBackPath(curPath);
					openDirecoty(curPath);
					xcor = 1, ycor = 80;
					pos();
				}
			}
			//If Enter key pressed
			else if (ch == 10)
			{
				//cout<<"********prev curPath : "<<curPath<<endl;
				string curDir = dirList[xcor + wintrack - 1];
				//cout<<"********CurDir/file  : "<<curDir<<endl;
				string fullPath;
				if(searchflag==1)
				{
					fullPath = curDir;
				}
				else
				{
					fullPath = string(curPath) + "/" + curDir;
				}

				char *path = new char[fullPath.length() + 1];
				strcpy(path, fullPath.c_str());
				//cout<<"**************"<<path<<"************";

				struct stat sb;
				stat(path, &sb);

				//If file type is Directory
				if ((sb.st_mode & S_IFMT) == S_IFDIR)
				{
					//cout<<"DIR"<<endl;
					xcor = 1;
					searchflag=0;
					if (curDir == string("."))
					{
					}
					else if (curDir == string(".."))
					{
						back_stack.push(string(curPath));
						clearStack(forw_stack);
						setBackPath(curPath);
					}
					else
					{
						if (curPath != NULL)
						{
							back_stack.push(string(curPath));
							clearStack(forw_stack);
						}
						curPath = path;
					}

					openDirecoty(curPath);
				}
				//If file type is Regular File
				else if ((sb.st_mode & S_IFMT) == S_IFREG)
				{
					//cout<<"**************File Path : "<<filepath<<"***************"<<endl;
					int fileOpen=open("/dev/null",O_WRONLY);
					dup2(fileOpen,2);
					close(fileOpen);
					pid_t processID = fork();
					if(processID == 0)
					{
						execlp("xdg-open","xdg-open",path,NULL);
						exit(0);
					} 
				}
				else
				{
					showError("Unknown File !!! :::::"+string(curDir));
				}
			}
			//If : pressed , went into command mode
			else if (ch == 58)
			{
				int lastLine = rowsize + 1;
				posx(lastLine,1);
				printf("%c[2K", 27);
				cout << ":";
				//cout<<"going into command mode :"<<endl;
				int result = startCommandMode();
				xcor = 1;
				pos();
				if (result == 1)
				{
					openDirecoty(curPath);
					//cout<<"goto out : ";
				}
				else if (result == 2)
				{
					//cout<<"search out : ";
				}
				else
				{
					//cout<<"Normal out : ";
					searchflag=0;
					openDirecoty(curPath);
				}
			}
		}
	}

	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
}
