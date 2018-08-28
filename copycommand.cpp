#include "myheader.h"

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
			cout<<"\nnewData : "<<newData<<endl;
			string name;
			size_t pos;
			pos = newData.find_last_of("/\\");
			name = newData.substr(pos+1,newData.length());
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
				//copydirectory(path,des);
			}
			else
			{
				copyfile(path,des);
			}
		}
	}
}