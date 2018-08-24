#include "myheader.h"
unsigned int xcor=1,ycor=1;
char* curPath;
#define esc 27
#define cls printf("%c[2J",esc)
#define pos() printf("%c[%d;%dH",esc,xcor,ycor)

void navigate()
{
	curPath = root;
	xcor=1,ycor=1;
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
	        		if(xcor>1)
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
	        	//If RIGHT-arrow Key press
	        	else if(ch=='C')
	        	{ 
	        		//cout<<"RIGHT"<<endl;
	        		if(!forw_stack.empty())
	        		{
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
	        	back_stack.push(string(curPath));
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
	        		//back_stack.pop();
	        		back_stack.push(string(curPath));

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
	        	string curDir = dirList[xcor-1];
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
	        			//back_stack.pop();
	        			back_stack.push(string(curPath));
					}
					else{
						bkspace_stack.push(string(curPath));
						back_stack.push(string(curPath));	
					}

					curPath = path;
					xcor=1;
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



