#include <stdio.h>


#define N 5633
#define M 6913
#define L 8192

main(){
  int i,j,bit,k[L];


printf("%u\n",strtoul("1011000000001",(char **)NULL,2));
printf("%u\n",strtoul("11011000000001",(char **)NULL,2));
printf("%u\n",strtoul("10000000000000",(char **)NULL,2));


k[0]=0;
bit=1;
j=10;
for(i=1;i<L;i++){
if(bit>L-1){
bit=bit-L;
bit=bit^N;
}
/* printf("%d\n",bit); */
k[i]=bit;
bit=(bit<<1);
}

for(i=0;i<L;i++){
printf("%d ",k[i]);
if(i % 10==0 && i>0)
printf(",\n");
}


}

