/* when are two goppa codes equal? */
/* �v���O�������� 400k byte�������ł����H */
#include <stdio.h>
#include "gfall.c"
#define X 8
#define N 256 /* #GF(2^x) */
#define M 16 /* key size */
/* t=16? */

static char *f4[8]={
"1000","1100",
"1001","1101",
"1010","1110",
"1011","1111"
};
static char *f7[8]={
"1001011","1001001",
"1101011","1010001",
"1010001","1010011",
"1011011","1000001"
};
static char *f[8]={
"10001011","10001001",
"10101011","10100001",
"10101001","10100011",
"10101011","10000011"
};
 static char *f16[10]={/* [256,128]-Goppa Code */
"11010000010000001","10001000000000010",
"11010101011101011","10101000000000111",
"11000000001001011","10001001000100011",
"10101010001010001","10001100010100011",
"10000100011101011","10101001001001001"
};

static char *f32[10]={/* [512,288] */
"11000100000000010000111001010111",
"10000001011001000000010001010001",
"11001111011001110000010010110011",
"11001110011011101101111110100111",
"11000100000010001000111011001011",
"11100111110010101100101011101001",
"10000110101010010100101110010111",
"11110010111011111111111110010111",
"10101101111011011110111111010101",
"10101101111011011111000001000111"
};
/*
10000000000000000001000001111111
10000000000000000001000010000011
10000000000000000001000010110101
10000000000000000001000011010011
10000000000000000001000011110111
10000000000000000001000011111101
10000000000000000001000100000011
10000000000000000001000100010111
10000000000000000001000100011101
10000000000000000001000101100011
10000000000000000001000101111101
10000000000000000001000110001101
10000000000000000001000111111111
};
*/


int count,L[N],G[N],g[N][N];

main(){
  int i,j,k;
  unsigned int a;

  
  for(i=0;i<10;i++){
    printf("%u\n",strtoul(f32[i],(char **)NULL,2));
    count=0;
    for(j=0;j<N;j++){
      a=b2pl(strtoul(f16[i],(char **)NULL,2),j); /* ���̒l from key */
/* printf("%u %u\n",a,count); */
      if(a>0){
	G[count-1]=a;
      }
    }

    if(count==N-1){
printf("%d\n",i);
      vandermonde(); 
      /* q2(count,G); */
      printf("\n");
    vin(); 
    }
  }

}


/* �o�C�i���\�� */
vin(){
  int i,j,k;
  
  
  printf("in vin\n");
  for(i=0;i<M;i++){
    for(k=0;k<X;k++){
      printf("@"); 
      for(j=0;j<count;j++)
	printf("%d",bit(g[i][j],k));
      printf("@,\n");
    }
  }

}


/* k�Ԗڂ̃r�b�g���o�� */
int bit(int n,int k)
{
  int i,j;
  char s[10];


  for(i=X,j=0;i>=0;i--,j++){
    s[j]=((n>>i) & 0x0001) + '0';
  }
  return s[k+1]-48;

}

/* print code word over GF(2^x) */
vandermonde()
{
  int i,j;


printf("in vandermonde\n");
  for(i=0;i<count;i++){
    g[0][i]=GF256[div(1,G[i])]; 
    printf("%d ",g[0][i]); 
  }
  printf("\n");
  for(i=0;i<count;i++){
    g[1][i]=GF256[div(L[i],G[i])]; 
    printf("%d ",g[1][i]); 
  }
  printf("\n");
  for(j=2;j<M;j++){
    for(i=0;i<count;i++){
      g[j][i]=GF256[div(mltn(j,L[i]),G[i])]; 
      printf("%d ",g[j][i]); 
    }
    printf("\n");
  }
  
}



/* �r�b�g�񂩂瑽�����̌v�Z */
unsigned int b2pl(unsigned int n,int x)
{
  unsigned int l=0;
  int i,j;


  for(i=0;i<cb(n);i++){
    /* printf("%d ",bit(n,i)); */
    if(bit(n,i)==1){
      /* printf("%d ",cb(n)-i-1); */
      l=add(l,mltn(cb(n)-i-1,x)); 
    }
  }
  if(l!=0){
    L[count]=x;
    count++;
  }
  return l;
  
}


/* �C�ӂ̎������������� (0<i<n �����̍��������_���ɑI��) */
int mpl(int n,int x)
{
  unsigned int l=0;
  int i,j;
  
  
  /* �ǂ������n���߂邩�H */
  for(i=n;i>-1;i--){
	 l=add(l,mltn(i,x)); 
       }
  if(l!=0){
    L[count]=x;
    count++;
  }
  return l;
  
}


/* �W���̑I�� (monic) [256,128,*]-Goppa
if 128-bit key size then 16-bit poly over GF(2), 
and 14 cofficients over GF(2^8)
 */




/* �p�����[�^�̌��� (k=n-mt) */





/* ���r�b�g�������Ԃ� */
int cb(unsigned int x)
{
  int i,j;
  
  i=0;
  while(x>0){
    x=(x>>1); i++;
  }

  return i;
  
}


/* �L���̏�ł̊|���Z */
int mlt(int x,int y)
{
  if(x==0||y==0){
    return(0);
  }
  return ((x+y-2)%(N-1))+1;
}


/* �L���̏�ł̗ݏ� */
int mltn(int n,int x)
{
  int i,j;
  
  
  if(n==0) return 1;
  
  i=x;
  for(j=1;j<n;j++)
    i=mlt(i,x);
  
  return i;
  
}


/* �L���̏�ł̑����Z */
int add(int x,int y)
{
  int z;
  
  if(x==0){
    return(y);
  }
  else if(y==0){
    return(x);
  }
  else if(x > y){
    z=(GF256[x-y+1]-1)+(y-1);
    z=(z%(N-1))+1;
  }
  else if(x < y){
    z=(GF256[y-x+1]-1)+x-1;
    z=(z%(N-1))+1;
  }
  else{
    z=0;
  }
  return(z);
}


/* �L���̏�ł̊���Z */
int div(int x,int y)
{
  if(y==0){
    /* printf("y��0\n"); */
    /* exit(1); */
  }
  else if(x==0){
    return 0;
  }
  return ((x-y+(N-1))%(N-1))+1;
}


/* �������̋t�� */
int inv(int l)
{
  int i,j;
  
  
  if(l==0)
    printf("���ꂪ�O�ł��B\n");
  
  return div(1,l);
  
}


void q2(int n,int a[])
{
  int i,j,l,r,p;
  int lstack[32],rstack[32];
  int x,t;
  
  l=0; r=n-1; p=0;
  for(;;){
    if(r-l<= 10){
      if(p==0) break;
      p--;
      l=lstack[p];
      r=rstack[p];
    }
    x=a[(l+r)/2];
    i=l; j=r;
    for(;;){
      while(a[i]<x) i++;
      while(x<a[j]) j--;
      if(i>=j) break;
      t=a[i]; a[i]=a[j]; a[j]=t;
      i++; j--;
    }
    if(i-l>r-j){
      if(i-l> 10){
	lstack[p]=l;
	rstack[p]=i-1;
	p++;
      }
      l=j+1;
    }else{
      if(r-j>10){
	lstack[p]=j+1;
	rstack[p]=r;
	p++;
      }
      r=i-1;
    }
  }
  inssort(n,a);
  
}


void inssort(int n,int a[])
{
  int i,j;
  int x;
  
  
  for(i=1;i<n;i++){
    x=a[i];
    for(j=i-1;j>=0 && a[j]>x;j--)
      a[j+1]=a[j];
    a[j+1]=x;
  }
  for(i=0;i<n;i++)
    printf("%d ",a[i]);
  printf("\n");

}

