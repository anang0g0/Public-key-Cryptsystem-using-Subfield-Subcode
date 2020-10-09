#include <stdio.h>


main(){
int i,j,c;
FILE *f,*p;
char s;


/* 256進表示だといい */
f=fopen("G:\wt22.a02","r");
while((c=fgetc(f)) !=EOF){
printf("%d ",c);
putchar(*c);
}


rdimg(char *fn,unsigned char *Img,int n)
{
FILE *fopen,*fp;
int i;


fp=fopen(fn,"rb");
if(fp==NULL)
{
printf("file open error\n");
exit();
}
for(i=0;i<n;i++)
{
*Img=(unsigned char)getc(fp);
Img++;
}
fclose(fp);


dspimg(unsigned *Img,int n)
{
int i;


for(i=0;i<n;i++)
{
putchar(*Img);
Img++;
}
return(1);
}


}



