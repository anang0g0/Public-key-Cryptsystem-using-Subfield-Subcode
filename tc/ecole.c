/* generate GF(2^n) using irreducible polynomial */


#include <stdio.h>


/* generate Galois Field over GF(2^?) */
static char *normal[13]={
  "11001", /* GF(16) */
  "110111",
  "1100001",
  "11000001",
  "110101001",
  "1100110001",
  "11000010011",
  "110000001101",
  "1100101000001", /* 4096 */
  "11011000000001", /* 8192 */
  "110000100010001",
  "1100000000000001",
  "11010000000010001"};

unsigned int GF[65536];

void makegf(int n)
{
  int i,j,bit,count=0;
  unsigned int pol,N,M,L;


  for(i=0;i<13;i++)
    pol=strtoul(normal[i],(char **)NULL,2);


  /* define pol */
  switch(n){
  case 16:
    pol=strtoul(normal[0],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  case 32:
    pol=strtoul(normal[1],(char **)NULL,2);
printf("%d\n",n);
    break;
    
  case 64:
    pol=strtoul(normal[2],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  case 128:
   pol=strtoul(normal[3],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  case 256:
    pol=strtoul(normal[4],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  case 512:
    pol=strtoul(normal[5],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  case 1024:
    pol=strtoul(normal[6],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  case 2048:
    pol=strtoul(normal[7],(char **)NULL,2);
    printf("%d\n",n);
    break;
   
  case 4096:
    pol=strtoul(normal[8],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  case 8192:
   pol=strtoul(normal[9],(char **)NULL,2);
    printf("%d\n",n);
    break;
    
  default : /* 16384 */
    pol=strtoul(normal[10],(char **)NULL,2);
    printf("%d\n",n);
    break;
  }
  
  
  L=1;
  while(pol>L){
    L=(L<<1);
    count++;
  }
  L=(L>>1);
  N=pol^L;
  M=pol;
  printf("%u %u %u\n",N,L,M);
  
  GF[0]=0;
  bit=1;
  for(i=1;i<L;i++){
    if(bit>L-1){
      bit=bit-L;
      bit=bit^N;
    }
    GF[i]=bit;
    bit=(bit<<1);
  }
  for(i=0;i<L;i++){
    printf("%u,",GF[i]);
    if(i % 10==0 && i>0)
      printf("\n");
  }
  printf("};\n");  

}
