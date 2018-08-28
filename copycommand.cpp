#include "myheader.h"

void copydirectory(char *path, char *des)
{
	int status= mkdir(des,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	 if(-1 == status)
	 {
	 	showError("Error in creating the Directory in path :::::  "+string(path));
	 }

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
		  	  		string finalpath=string(path) + "/" +string(dir->d_name);
					char* newpath = new char[finalpath.length() + 1];
					strcpy(newpath, finalpath.c_str());

					string finaldestpath=string(des) + "/" +string(dir->d_name);
					char* newdestpath = new char[finaldestpath.length() + 1];
					strcpy(newdestpath, finaldestpath.c_str());

		  			struct stat sb;
					if (stat(newpath,&sb) == -1) {
				        perror("lstat");
				    }
				    else{

				    	if((S_ISDIR(sb.st_mode)))
					    {
					    	copydirectory(newpath,newdestpath);
					    }
					    else
					    {
					    	 copyfile(newpath,newdestpath);
					    }
				    }
		  	  		
		  	  }

	    }

	}
	else{
		showError("No such Directory Exist !!!");
	}
}

void copyfile(char *path, char *des)
{
	cout<<"\nsource path : "<<path<<endl;
	cout<<"\ndestination path :"<<des<<endl;

	char block[1024];
	int in, out;
	int nread;
	
	in = open(path, O_RDONLY);
	out = open(des, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while((nread = read(in,block,sizeof(block))) > 0)
		write(out,block,nread);

	struct stat sourcestat,deststat;
	if (stat(path,&sourcestat) != -1) {  
    }
    if (stat(des,&deststat) != -1) {  
    }
    
    int status1=chown(des,sourcestat.st_uid, sourcestat.st_gid);
    int status2=chmod(des,sourcestat.st_mode);


}
void copycommand(vector<string> list)
{
	unsigned int len = list.size();
	if(len < 3)
	{
		showError("Less number of Argument in copy command !!!");
	}
	else{

		
		for(unsigned int i=1;i<len-1;i++)
		{
			string newData = list[i];
			string name = getFileNameFromPath(newData);
			cout<<"\nfilename : "<<name;

			string destpath= list[len-1];
			destpath =destpath + "/" + name;
			char *des = new char[destpath.length() + 1];
			strcpy(des, destpath.c_str());
			cout<<"\ndespath in copy : "<<des<<endl;
	
			char *path = new char[newData.length() + 1];
			strcpy(path, newData.c_str());
			if(isdirectory(path))
			{
				copydirectory(path,des);
			}
			else
			{
				copyfile(path,des);
			}
		}
	}
}