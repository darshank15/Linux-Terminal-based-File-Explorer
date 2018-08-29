//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

vector<string> tokens;

//**********************************************************************
// It handles absolute and relative paths in cmd mode
//**********************************************************************
string pathProcessing(string str)
{
	char firstchar = str[0];
	// cout<<"curPath : "<<curPath<<endl;
	// cout<<"root :" <<root<<endl;
	// cout<<"given path  : "<<str<<endl;
	// cout<<"firstchar: "<<firstchar<<endl;
	string absolutePath="";
	string basepath = string(root);
	if(firstchar =='/')
	{
		
		absolutePath = basepath + str;
	}
	else if(firstchar=='~')
	{
		absolutePath = basepath + str.substr(1,str.length());
	}
	else if(firstchar=='.')
	{
		absolutePath = string(curPath) + str.substr(1,str.length());	
	}
	else
	{
		absolutePath = string(curPath)+ "/" + str;
	}
	
	//cout<<"absolutePath : "<<absolutePath<<endl;
	return absolutePath;
}

//**********************************************************************
// It splits input string into tokens separeted by space
//**********************************************************************
void inputProcessing(string str)
{
	
	unsigned int i=0;
	tokens.clear();
	int flag=0;
	while(i<str.length())
	{
		string sub="";
		while(str[i]!=' ' && i<str.length())
		{
			sub += str[i];
			i++;
		}
		if(flag==1)
		{
			string abspath=pathProcessing(sub);
			tokens.push_back(abspath);
		}
		else{

			tokens.push_back(sub);
			if(tokens[0]!="create_file" && tokens[0]!="create_dir")
			{
				flag=1;	
			}
			
		}
		i++;	
	}
	
	//see the list of commands in vector
	// for(unsigned int i=0;i<tokens.size();i++)
	// {
	// 	cout<<"   tokens : "<<tokens[i];
	// }

}

//**********************************************************************
// After each command runs, it clear command line area
//**********************************************************************
void clearCommand()
{
	int lastLine = rowsize + 1;
	printf("%c[%d;%dH",27,lastLine,1);
	printf("%c[2K", 27);
	cout<<":";
}

//**********************************************************************
// Method that starts the CommandMode
//**********************************************************************
void startCommandMode()
{
	char ch;
	do{
		string input;
		while(((ch = getchar())!= 10) && ch!=27)
		{
			if(ch==127)
			{
				clearCommand();
				if(input.length()<=1)
				{
					input="";
				}
				else{
					input = input.substr(0,input.length()-1);
				}
				cout<<input;
				
			}
			else{
				input = input + ch;
				cout<<ch;	
			}
			
		}
		//cout<<"\n ch :::"<<(int)ch<<endl;
		//cout<<"\ninput : "<<input<<endl;
		inputProcessing(input);
		if(ch==10)
		{
			string command= tokens[0];
			if(command == "copy")
			{
				//cout<<"Copy command  : "<<endl;
				copycommand(tokens);
				clearCommand();
			}
			else if(command == "move")
			{
				//cout<<"Move command  : "<<endl;
				movecommand(tokens);
				clearCommand();
			}
			else if(command == "rename")
			{
				//cout<<"rename command  : "<<endl;
				renameFiles(tokens);
				clearCommand();
			}
			else if(command == "create_file")
			{
				//cout<<"create_file command  : "<<endl;
				createNewFiles(tokens);
				clearCommand();
			}
			else if(command == "create_dir")
			{
				//cout<<"create_dir command  : "<<endl;
				makeDirectories(tokens);
				clearCommand();
			}
			else if(command == "delete_file")
			{
				//cout<<"delete_file command  : "<<endl;
				removeFiles(tokens);
				clearCommand();
			}
			else if(command == "delete_dir")
			{
				//cout<<"delete_dir command  : "<<endl;
				removeDirectories(tokens);
				clearCommand();
			}
			else if(command == "goto")
			{
				cout<<"goto command  : "<<endl;
				string gpath = gotoPath(tokens);
				char *path = new char[gpath.length() + 1];
		 		strcpy(path, gpath.c_str());
		 		curPath = path;
		 		break;
			}
			else if(command == "search")
			{
				cout<<"search command  : "<<endl;
				
			}
			else if(command == "snapshot")
			{
				cout<<"snapshot command  : "<<endl;
				takesnapshot(tokens);
				
			}
			else{
				cout<<"Invalid Command  !!!"<<endl;
				clearCommand();
			}
		}	

	}while(ch != 27);


}