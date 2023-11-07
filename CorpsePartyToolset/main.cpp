#include <stdio.h>
#include <Windows.h>
#include <direct.h>
#include "funcs.h"
#include "lzss.h"

int main()
{
FILE *bin,*ext;
BYTE *dmp,*unc;
unsigned long int compflag,num,i,*pointer,*size,usize,dirnum,x;
char **name,**dirlist,header[5];

printf("Corpse Party IMAGE.BIN Extractor by Vash v0.1 -vash.romhacking.it-\n\n");

bin=fopen("IMAGE.BIN","rb");
if (!bin)
{
  printf("Can't find or open IMAGE.BIN. Be sure it's in the same directory of the tool\n");
  return 0;
}

_mkdir("Image");
_chdir("Image");

fseek(bin,4,SEEK_SET);
fread(&num,4,1,bin);
pointer=(unsigned long int *)malloc(num*sizeof(unsigned long int *));
size=(unsigned long int *)malloc(num*sizeof(unsigned long int *));
name=(char**)malloc(num*sizeof(char**));

fseek(bin,0x0C,SEEK_SET);

for (i=0;i<num;i++)
    {
		fseek(bin,0x08,SEEK_CUR); //skip what appears to be a CRC check
		fread(&pointer[i],4,1,bin);
		fread(&size[i],4,1,bin);
		name[i] = (char *)malloc(0x80*sizeof(char));
		fread(name[i],0x80,1,bin);
		name[i][0x80]=0;
		//printf("%s\n",name[i]);
    }


for (i=0;i<num;i++)
{
fseek(bin,pointer[i],SEEK_SET);
fread(header,4,1,bin);
header[4]=0;
if (strcmp(header,"LZSS") == 0)
{
compflag=1;
fread(&usize,4,1,bin);
size[i]-=4;
fseek(bin,pointer[i]+4,SEEK_SET);
}else{
compflag=0;
fseek(bin,pointer[i],SEEK_SET);
}
dmp=(BYTE *)malloc(size[i]);
fread(dmp,size[i],1,bin);
dirnum=GetDirList(name[i],dirlist, 0x2F);
printf("[%d on %d] ",i+1,num);
for (x=0;x<dirnum-1;x++)
{
	_mkdir(dirlist[x]);
	_chdir(dirlist[x]);
	printf("%s\\",dirlist[x]);
}
printf("%s\n",dirlist[dirnum-1]);
//system("pause");
ext=fopen(dirlist[dirnum-1],"wb");
//compression check
if (compflag==1)
{
	unc=(BYTE *)malloc(usize);
	LzssDecode(unc,dmp,size[i]);
	//unlzss(unc,usize,dmp,size[i]);
	fwrite(unc,usize,1,ext);
	free(dmp);
	free(unc);
}else{
fwrite(dmp,size[i],1,ext);
free(dmp);
}
fclose(ext);

for (x=0;x<dirnum-1;x++)
{
_chdir("..");
}

}

return 1;
}