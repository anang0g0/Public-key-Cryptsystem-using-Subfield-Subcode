//sagemath上での原始多項式
unsigned char pp[4][4]={{1,0,9,2},{1,0,11,2},{1,0,16,3},{1,0,15,2}}; //GF(11^3,13^3,17^3,19^3)
unsigned char ff[2][7]={1,0,0,0,0,2,0,2},{0,0,1,0,0,0,1,2}}; //GF(3^7,5^5)

unsigned int gf[O],fg[O];


void makefg(int n){
int i,j;

for(i=0;i<n;i++){
  for(j=0;j<n;j++){
    if(gf[i]==j)
      fg[j]=i;
  }
}
  printf("unsigned short fg[%d]={",O);
  for(i=0;i<O;i++)
  printf("%d,",fg[i]);
printf("};\n");

 
return;
}


void mkgf(int n)
{
  int i,j,bit,count=0;
  unsigned int pol,N,M,L;


  for(i=0;i<13;i++)
    pol=normal[i];//strtoul(normal[i],(char **)NULL,2);


  /* define pol */
  switch(n){

  case 8:
    pol=normal[0];
    printf("%d\n",n);
    break;

  case 16:
    pol=normal[1];
    printf("%d\n",n);
    break;

  case 32:
    pol=normal[2];
printf("%d\n",n);
    break;

  case 64:
    pol=normal[3];
    printf("%d\n",n);
    break;

  case 128:
    pol=normal[4];
    printf("%d\n",n);
    break;

  case 256:
    pol=normal[5];
    printf("%d\n",n);
    break;

  case 512:
    pol=normal[6];
    printf("%d\n",n);
    break;

  case 1024:
    pol=normal[7];
    printf("%d\n",n);
    break;

  case 2048:
    pol=normal[8];
    printf("%d\n",n);
    break;

  case 4096:
    pol=normal[9];
    printf("%d\n",n);
    break;

  case 8192:
    pol=normal[10];
    printf("%d\n",n);
    break;

  default : /* 16384 */
    pol=normal[11];
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
  //  printf("%u %u %u\n",N,L,M);

  gf[0]=0;
  bit=1;
  for(i=1;i<L;i++){
    if(bit>L-1){
      bit=bit-L;
      bit=bit^N;
    }
    gf[i]=bit;
    bit=(bit<<1);
  }
  printf("unsigned short gf[%d]={",O);
  for(i=0;i<L;i++)
    printf("%u,",gf[i]);
  
  printf("};\n");

}


int main(){
  int i,j,k;

  mkgf(O);
  makefg(O);


return 0;
}

