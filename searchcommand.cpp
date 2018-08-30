#include "myheader.h"

vector<string> searchResult;

int isNameMatch(string filename,string name)
{
	if(filename==name)
		return 1;
	else
		return 0;	

}

void printsearchData()
{
	totalFiles = dirList.size();
	unsigned int len = getFilePrintingcount();
	sort(dirList.begin(),dirList.end());
	wintrack=0;
	printf("\033[H\033[J");
	printf("%c[%d;%dH",27,1,1);

	for(unsigned int i=0,itr=1;i<totalFiles && itr<=len ; i++,itr++)
	{		
			cout<<dirList[i]<<endl;
	}

	printf("%c[%d;%dH",27,1,1);	
}

void searchanything(char *path,string filename)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d) 
	{
	    while ((dir = readdir(d)) != NULL) 
	    {
		      if( (string(dir->d_name) == "..") || (string(dir->d_name) == ".") )	
		      {   } 
		  	  else
		  	  {		
		  	  		string name = string(dir->d_name);
		  	  		string finalpath= string(path) + "/" + name;
					char* newpath = new char[finalpath.length() + 1];
					strcpy(newpath, finalpath.c_str());

		  			struct stat sb;
					if (stat(newpath,&sb) == -1) {
				        perror("lstat");
				    }
				    else{

				    	if((S_ISDIR(sb.st_mode)))
					    {
					    	if(isNameMatch(filename,name))
					    	{
					    		searchResult.push_back(string(newpath));
					    	}
					    	searchanything(newpath,filename);
					    }
					    else
					    {
					    	if(isNameMatch(filename,name))
					    	{
					    		searchResult.push_back(string(newpath));
					    	}
					    }
				    }
		  	  		
		  	  }

	    }

	}
	else{

		showError("No such Directory path Exist while searching !!!");
	}

}
void searchcommand(vector<string> list)
{
	searchResult.clear();
	unsigned int len = list.size();
	if(len != 2)
	{
		showError("Less number of Argument in copy command !!!");
	}
	else{
		string filename = list[1];
		char *path = new char[strlen(curPath) + 1];
		strcpy(path, curPath);
		cout<<"\npath : "<<path<<endl;
		cout<<"\nfilename : "<<filename<<endl;
		searchanything(path,filename);
		
		back_stack.push(string(curPath));
		clearStack(forw_stack);

		string emptypath="";
		strcpy(curPath, emptypath.c_str());

		dirList.clear();
		dirList = searchResult;
		printsearchData();
	}

}

