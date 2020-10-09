#include <stdio.h>

#define M32(x) (((1UL << 32)-1)&(x))

static int jrnd;
static unsigned int x[521];

/* 線形合同法 


main(){
  unsigned int seed;
  int i;


  scanf("%u",&seed);
  init_rnd(seed);
  for(;;)
    printf("%u\n",irnd());
*/
/*
for(i=0;i<521;i++)
printf("%b",x[i]^rand());
572945278039

}
*/


static void rnd521(void)
{
  int i;
  
  for(i=0;i<32;i++) x[i]^=x[i+489];
  for(i=32;i<521;i++) x[i]^=x[i-32];
}


void init_rnd(unsigned int seed)
{
  int i,j;
  unsigned int u;
  
  u=0;
  for(i=0;i<=16;i++){
    for(j=0;j<32;j++){
      seed=seed*1566083941UL+1;
      u=(u>>1) | (seed & (1UL << 31));
    }
    x[i]=u;
  }
  x[16]=M32(x[16]<<23)^(x[0]>>9)^x[15];
  for(i=17;i<=520;i++)
    x[i]=M32(x[i-17]<<23)^(x[i-16]>>9)^x[i-1];
  rnd521(); rnd521(); rnd521();
  jrnd=520;
}


unsigned int irnd(void)
{
  if(++jrnd>=521){ /* init_rnd(x[jrnd]); */ rnd521(); jrnd=0; }
  return x[jrnd];
}


double rnd(void)
{
  return (1.0 / (((1UL << 32)-1)+1.0)) * irnd();
}


