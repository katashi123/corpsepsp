#include <stdio.h>


unsigned long int GetDirList(char* string, char** &dirs, char divider)
{
unsigned long int dirnum,len,x,i;
x=0;
i=0;
dirnum=0;
dirs=(char**)malloc(strlen(string)*sizeof(char**));
dirs[dirnum]=(char *)malloc(strlen(string)*sizeof(char));
while (string[x] != 0x00)
{
  if (string[x] != divider)
  {
    //sprintf(dirs[dirnum],"%s%c",dirs[dirnum],string[x]);
	  dirs[dirnum][i]=string[x];
	  i+=1;
  }
  else
  {
    dirs[dirnum][i]=0;
    //printf("%s\n",dirs[dirnum]);
	dirnum+=1;
    dirs[dirnum]=(char *)malloc(strlen(string)*sizeof(char));
	i=0;
  }
x+=1;
}
dirs[dirnum][i]=0;
//printf("%s\n",dirs[dirnum]);
dirnum+=1;
return (dirnum);
}