#include "myheader.h"
unsigned int xcor=0,ycor=1;
char* curPath;
#define esc 27
#define cls printf("%c[2J",esc)
#define pos() printf("%c[%d;%dH",esc,xcor,ycor)

void navigate()
{
	curPath = root;
	xcor=0,ycor=1;
	pos();
	struct termios initialrsettings, newrsettings;
	char ch;

	tcgetattr(fileno(stdin), &initialrsettings);

	//switch to canonical mode and echo mode
	newrsettings = initialrsettings;
	newrsettings.c_lflag &= ~ICANON;
	newrsettings.c_lflag &= ~ECHO;

	if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
	fprintf(stderr,"Could not set attributes\n");
	}
	else {

		while(1){		
			ch=cin.get();

	        //printf("%d",ch);
	        if(ch==27)
	        {
	        	ch=cin.get();
	        	ch=cin.get();

	        	//If UP-arrow Key press
	        	if(ch=='A')
	        	{
	        		if(xcor>0)
	        			--xcor;
	        		pos();

	        	}
	        	//If DOWN-arrow Key press
	        	else if(ch=='B')
	        	{
	        		if(xcor < (dirList.size()))
	        			xcor++;
	        		pos();
	        	}
	        	//If LEFT-arrow Key press
	        	else if(ch=='C')
	        	{

	        	}
	        	//If RIGHT-arrow Key press
	        	else if(ch=='D')
	        	{

	        	}
	        	else
	        	{

	        	}
	        }
	        //If HOME key pressed
	        else if(ch==104 || ch==72)
	        {
	        	while(!bkspace_stack.empty())
	        	{
	        		bkspace_stack.pop();
	        	}
	        	curPath = root;
	        	openDirecoty(root);
	        }
	        //If Back-Space key pressed
	        else if(ch==127)
	        {
	        	if(!bkspace_stack.empty())
	        	{
	        		string top = bkspace_stack.top();
	        		bkspace_stack.pop();
	        		strcpy(curPath,top.c_str());
	        		openDirecoty(curPath);
	        		//cout<<"back space dir : "<<curPath<<endl;
	        	}
	        }
	        //If Enter key pressed
	        else if(ch==10)
	        {
	       
	        	//cout<<"********prev curPath : "<<curPath<<endl;
	        	string curDir = dirList[--xcor];
	        	//cout<<"********CurDir/file  : "<<curDir<<endl;
	        	string fullPath = string(curPath) + "/" + curDir;
				char* path = new char[fullPath.length() + 1];
				strcpy(path, fullPath.c_str());
	        	//cout<<"**************"<<path<<"************";

	        	struct stat sb;
				stat(path,&sb);

				//If file type is Directory
				if((sb.st_mode & S_IFMT) == S_IFDIR) {
					//cout<<"DIR"<<endl;

					if(curDir == string("."))
					{  }
					else if(curDir == string(".."))
					{
						bkspace_stack.pop();	
					}
					else{
						bkspace_stack.push(string(curPath));	
					}

					curPath = path;
					xcor=0;
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

		}
        
	}

	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);

}



