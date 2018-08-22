#include "myheader.h"
int xcor=1,ycor=1;
#define esc 27
#define cls printf("%c[2J",esc)
#define pos() printf("%c[%d;%dH",esc,xcor,ycor)

void navigate()
{
	xcor=1,ycor=1;
	struct termios initialrsettings, newrsettings;
	char ch;

	tcgetattr(fileno(stdin), &initialrsettings);

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
	        	if(ch=='A')
	        	{
	        		if(xcor>1)
	        			--xcor;
	        		pos();
	        	}
	        	else if(ch=='B')
	        	{
	        		++xcor;
	        		pos();
	        	}
	        	else if(ch=='C')
	        	{

	        	}
	        	else if(ch=='D')
	        	{

	        	}
	        	else
	        	{

	        	}
	        }
	        else if(ch==104 || ch==72)
	        {
	        	openDirecoty(root);
	        }
	        else if(ch==127)
	        	cout<<"Back";
		}

		
	        
	}

	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);

}



