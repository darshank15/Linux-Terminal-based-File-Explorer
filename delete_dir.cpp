#include "myheader.h"

//**********************************************************************
// This function recursively remove all file and dir inside it.
// and finally delete dir itself
//**********************************************************************
void removeSingleDirectory(char *path)
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
		  	  		string finalpath=string(path) + "/" +string(dir->d_name);;
					char* newpath = new char[finalpath.length() + 1];
					strcpy(newpath, finalpath.c_str());

		  			struct stat sb;
					if (stat(newpath,&sb) == -1) {
				        perror("lstat");
				    }
				    else{

				    	if((S_ISDIR(sb.st_mode)))
					    {
					    	removeSingleDirectory(newpath);
					    }
					    else
					    {
					    	removeSingleFile(newpath);
					    }
				    }
		  	  		
		  	  }

	    }
	    closedir(d);
	    int status= rmdir(path);
		if(-1 == status)
		{
		 	showError("Error in removing the Directory with path ::::: "+string(path));
		}


	}
	else{
		
		showError("No such Directory Exist !!!");
	}


}

//**********************************************************************
// It removes multiple directory that passed by User in argument
//**********************************************************************
void removeDirectories(vector<string> list)
{
	if(list.size() < 2)
	{
		showError("Less number of argument in delete_dir !!!");
	}
	for(unsigned int i=1;i<list.size();i++)
	{
		 char *path = new char[list[i].length() + 1];
		 strcpy(path, list[i].c_str());
		 //cout<<"\nrmdir path :"<<path<<endl;
		 removeSingleDirectory(path);
	}	 
}