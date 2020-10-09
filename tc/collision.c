/* testing collision */

#include <stdio.h>
#include "code.h"

#define N 31 /* code length */



main(){
int i,j,count;
unsigned int u,v,w;
/* w=10 */
u=strtoul("1",(char *)NULL,2);

count=0;
for(;;){
count++;
v=code(u,bch31t);
w=code(u,goppa31t);
printf("%u %u %u\n",u,v,w);

if(v==w){
printf("collision=%u then %d times\n",u,count);
count=0;
}
u=rP(u);
}

}


unsigned int code(unsigned int a,unsigned int b[])
{
int i,j;
unsigned int k=0;
char t[31];


for(i=0;i<16;i++){
k=(k<<1)+(itob(a&b[i],t)%2);
}
return k;
}



unsigned int rP(unsigned int A)
{
  int i,j,c=0;
  unsigned int X=0,W,P[N];
  char t[31];
  

  P[0]=1;
  for(i=1;i<N-1;i++)
    P[i]= (P[0]<<i);
  P[N-1]=(P[0]<< N-1);
  
  
  //srand(0);
  /* permute binary vector A */
  while(c<N){
    j=rand()% N;
    W=P[j];P[j]=0;
    if(W>0){
      if(tstbit(A,t,j)==1)
	X=X+1;
      if(c<N-1)
	X= (X<<1);
      c=c+1;
    }
  } 
  return X;
}



int cb(unsigned int x)
{
int i,j;

i=0;
while(x>0){
x=(x>>1); i++;
}
return i;

}


int tstbit(unsigned int n,char s[],int d)
{
int i,j,k=0;


for(i=30,j=0;i>=0;i--,j++){
s[j]=((n>>i) & 0x000001) + '0';
}


return (s[d]-48);
}


int itob(unsigned int n,char s[])
{
int i,j,k=0;


for(i=30,j=0;i>=0;i--,j++){
s[j]=((n>>i) & 0x000001) + '0';
}

for(j=0;j<31;j++){
if(s[j]-48==1)
printf("%d",s[j]-48);
k++;
}
return k;

}

