//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

//**********************************************************************
// Global Declaration & #defined macros
//**********************************************************************
unsigned int xcor=1,ycor=1;
char* curPath;
#define esc 27
#define cls printf("%c[2J",esc)
#define pos() printf("%c[%d;%dH",esc,xcor,ycor)
#define posx(x) printf("%c[%d;%dH",esc,x,ycor)

//**********************************************************************
// Method that update current path when backspace key pressed
//**********************************************************************
void setBackPath(char *path)
{
	size_t pos;
	string newPath;
	string  tempPath= string(path);
	pos = tempPath.find_last_of("/\\");
	newPath = tempPath.substr(0,pos);
	strcpy(curPath,newPath.c_str());
}

//**********************************************************************
// This Method Clear the stack contents
//**********************************************************************
void clearStack(stack<string> &s)
{
	while(!s.empty())
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
	xcor=1,ycor=1;
	pos();
	char ch;
	
	struct termios initialrsettings, newrsettings;
	tcgetattr(fileno(stdin), &initialrsettings);
	//switch to canonical mode and echo mode
	newrsettings = initialrsettings;
	newrsettings.c_lflag &= ~ICANON;
	newrsettings.c_lflag &= ~ECHO;

	if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
	fprintf(stderr,"Could not set attributes\n");
	}
	else {

		while(1)
		{	
			int lastLine = rowsize + 1;
	        posx(lastLine);
	        cout<<"-----NORMAL MODE-----";
	        pos();

			ch=cin.get();
	        //printf("%d",ch);
	        if(ch==27)
	        {
	        	ch=cin.get();
	        	ch=cin.get();

	        	//If UP-arrow Key press
	        	if(ch=='A')
	        	{
	        		if(xcor+wintrack > 1)
	        		{
	        			//cout<<"**********xcor"<<xcor<<"*****wintrack"<<wintrack<<endl;
	        			xcor--;
	        			if(xcor>0){
	        				pos();
	        			}
	        			else if(xcor<=0 && xcor+wintrack >= 1)
	        			{
	        				cls;
	        				if(wintrack > 0)
	        				{
	        					wintrack--;
	        				}
	        				//cout<<"wintrack : "<<wintrack<<"***********";
	        				
	        				for(unsigned int i=wintrack;i<=rowsize+wintrack-1;i++)
	        				{
	        					char *tempFileName = new char[dirList[i].length() + 1];
	        					strcpy(tempFileName,dirList[i].c_str());
	        					display(tempFileName,root);
	        				}
	        				xcor++;
	        				pos();
	        			}
	        		}
	        		
	        	}
	        	//If DOWN-arrow Key press
	        	else if(ch=='B')
	        	{	
	        		//cout<<"\n*******************DOWN";
	        		int lenRecord;
	        		if(xcor+wintrack < (totalFiles))
	        		{
	        			xcor++;
	        			//cout<<"**********xcor"<<xcor<<"*****"<<endl;
	        			if(xcor<=rowsize){
	        				pos();
	        			}
	        			else if(xcor>rowsize && xcor+wintrack<=totalFiles)
	        			{
	        				cls;
	        				//cout<<"***********2st if"<<"*****"<<endl;
	        				lenRecord = getFilePrintingcount()-1;
	        				if(totalFiles > rowsize)
	        				{
	        					wintrack++;
	        				}
	        				//cout<<"wintrack : "<<wintrack<<"***********";
	        				
	        				for(int i=wintrack;i<=lenRecord+wintrack;i++)
	        				{
	        					char *tempFileName = new char[dirList[i].length() + 1];
	        					strcpy(tempFileName,dirList[i].c_str());
	        					display(tempFileName,root);
	        				}
	        				xcor--;
	        			}
	        			pos();
	        		}
	        		
	        	}
	        	//If RIGHT-arrow Key press
	        	else if(ch=='C')
	        	{ 
	        		//cout<<"RIGHT"<<endl;
	        		if(!forw_stack.empty())
	        		{
	        			string cpath = string(curPath);
	        			if(cpath!="")
	        				back_stack.push(string(curPath));
	        			string top = forw_stack.top();
						forw_stack.pop();
	        			strcpy(curPath,top.c_str());
	        			//cout<<"******* RIGHT: "<<curPath;
	        			openDirecoty(curPath);
	        		}

	        	}
	        	//If LEFT-arrow Key press
	        	else if(ch=='D')
	        	{
					//cout<<"LEFT"<<endl;
	        		if(!back_stack.empty())
	        		{
	        			string cpath = string(curPath);
	        			if(cpath!="")
	        				forw_stack.push(string(curPath));
	        			string top = back_stack.top();
	        			back_stack.pop();
	        			strcpy(curPath,top.c_str());
	        			//cout<<"******* : LEFT"<<curPath;
	        			openDirecoty(curPath);
	        		}	        		
	        	}
	        	else
	        	{

	        	}
	        }
	        //If HOME key pressed
	        else if(ch==104 || ch==72)
	        {
	        	string cpath = string(curPath);
	        	if(cpath!="")
					back_stack.push(string(curPath));
	        	clearStack(forw_stack);
	        	strcpy(curPath,root);
	        	openDirecoty(curPath);
	        }
	        //If Back-Space key pressed
	        else if(ch==127)
	        {
	        	//cout<<"*************curPathr"<<curPath<<"***********";
	        	string cpath = string(curPath);
	        	if((strcmp(curPath,root) != 0) && cpath!="")
	        	{
		        	//cout<<"**************Root : "<<root<<"***********";
	        		back_stack.push(curPath);
	        		clearStack(forw_stack);
	        		setBackPath(curPath);
		        	openDirecoty(curPath);
		 
	        	}
	        	

	        }
	        //If Enter key pressed
	        else if(ch==10)
	        {
	       
	        	//cout<<"********prev curPath : "<<curPath<<endl;
	        	string curDir = dirList[xcor+wintrack-1];
	        	//cout<<"********CurDir/file  : "<<curDir<<endl;
	        	string fullPath;
	        	string cpath=string(curPath);
	        	if(cpath=="")
	        	{
	        		fullPath=curDir;
	        	}
	        	else{
	        		fullPath = string(curPath) + "/" + curDir;
	        	}

				char* path = new char[fullPath.length() + 1];
				strcpy(path, fullPath.c_str());
				//cout<<"**************"<<path<<"************";	

	        	struct stat sb;
				stat(path,&sb);

				//If file type is Directory
				if((sb.st_mode & S_IFMT) == S_IFDIR) {
					//cout<<"DIR"<<endl;
					xcor=1;

					if(curDir == string("."))
					{  }
					else if(curDir == string(".."))
					{
	        			back_stack.push(string(curPath));
	        			clearStack(forw_stack);
	        			setBackPath(curPath);
	        			
					}
					else{
						if(curPath!=NULL)
						{
							back_stack.push(string(curPath));
							clearStack(forw_stack);
						}
						curPath = path;
	        			
					}

					openDirecoty(curPath);
					
				}
				//If file type is Regular File
				else if((sb.st_mode & S_IFMT) == S_IFREG)
				{
					string cmd = "xdg-open "+string(path);
					char *filepath = new char[cmd.length() + 1];
					strcpy(filepath, cmd.c_str());
					//cout<<"**************File Path : "<<filepath<<"***************"<<endl;
					system(filepath);
					//cout<<"FILE"<<endl;
				}
				else{
					cout<<"unknown?"<<endl;
					cout<<"****************************"<<endl;
				}
	        }

	        else if(ch==58)
	        {
	        	int lastLine = rowsize + 1;
	        	posx(lastLine);
	        	printf("%c[2K", 27);
	        	//newrsettings=initialrsettings;
	        	//newrsettings.c_lflag &= ~ICANON;
	        	//newrsettings.c_lflag &= ~ECHO;
	        	//tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings);
	        	cout<<":";
	        	//cout<<"going into command mode :"<<endl;
	        	int result =startCommandMode();
	        	xcor=1;
	        	pos();
	        	if(result == 1)
	        	{	
	        		openDirecoty(curPath);
	        		cout<<"goto out : ";
	        	}
	        	else if(result == 2)
	        	{
	        		//cout<<"search out : ";
	        	}
	        	else{
	        		openDirecoty(curPath);
	        		cout<<"normal exit";
	        	}
	        	
	        }

		}
        
	}

	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);

}



