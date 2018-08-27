//**********************************************************************
// Header file Included
//**********************************************************************
#include "myheader.h"

vector<string> tokens;

void inputProcessing(string str)
{
	
	unsigned int i=0;
	tokens.clear();
	while(i<str.length())
	{
		string sub="";
		while(str[i]!=' ' && i<str.length())
		{
			sub += str[i];
			i++;
		}
		tokens.push_back(sub);
		i++;	
	}
	
	// for(unsigned int i=0;i<tokens.size();i++)
	// {
	// 	cout<<"   tokens : "<<tokens[i];
	// }

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
			input = input + ch;
			cout<<ch;
		}
		//cout<<"input : "<<input;
		inputProcessing(input);
		if(ch==10)
		{
			string command= tokens[0];
			if(command == "copy")
			{
				cout<<"Copy command  : "<<endl;
			}
			else if(command == "move")
			{
				cout<<"Move command  : "<<endl;
			}
			else if(command == "rename")
			{
				cout<<"rename command  : "<<endl;
			}
			else if(command == "create_file")
			{
				cout<<"create_file command  : "<<endl;
			}
			else if(command == "create_dir")
			{
				cout<<"create_dir command  : "<<endl;
			}
			else if(command == "delete_file")
			{
				cout<<"delete_file command  : "<<endl;
			}
			else if(command == "delete_dir")
			{
				cout<<"delete_dir command  : "<<endl;
			}
			else if(command == "goto")
			{
				cout<<"goto command  : "<<endl;
			}
			else if(command == "search")
			{
				cout<<"search command  : "<<endl;
			}
		}	

	}while(ch != 27);


}