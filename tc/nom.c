#include <stdio.h>


main(){
  int i,bit,k[4096];
  unsigned int N,L;

printf("%u\n",strtoul("100101000001",(char **)NULL,2));
printf("%u\n",strtoul("1100101000001",(char **)NULL,2));
printf("%u\n",strtoul("1000000000000",(char **)NULL,2));

N=strtoul("100101000001",(char **)NULL,2);
L=strtoul("1000000000000",(char **)NULL,2);


k[0]=0;
bit=1;
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

