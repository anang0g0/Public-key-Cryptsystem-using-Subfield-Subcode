#include <stdio.h>
#include "gfall.c"

#define N 32 /* #GF(2^x) */
#define M 4 /* key size */


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
static char *ff[10]={
"11010000000000001","10000000000000010",
"11010101010101011","10100000000000111",
"11000000000001011","10000001000100011",
"10101010000010001","10000100010100011",
"10000100010101011","10100001001001001"
};

/* static char f32[31] */

int count,L[N],G[N],g[N][N];


main(){

  ben();

}


ben(){
  int i,j,a,k;
  
  
  for(i=0;i<8;i++){
    printf("%u\n",strtoul(f4[i],(char **)NULL,2));
    count=0;
    for(j=0;j<N;j++){
      a=b2pl(strtoul(f4[i],(char **)NULL,2),j); /* 式の値 from key */
      /* printf("%d %d\n",a,count); */
      if(a>0){
	G[count-1]=a;
	/* printf("%d ",a); */
      }
    }
    printf("%d\n",count);
    
    for(k=0;k<count;k++)
      printf("%d ",G[k]);
printf("\n");
    if(count==31){
      vandermonde(); 
      /* q2(count,G); */
      printf("\n");
      vin();
    }
  } 

}



/* k番目のビット取り出し */
int bit(int n,int k)
{
  int i,j;
  char s[9];
  
  
  for(i=M,j=0;i>=0;i--,j++){
    s[j]=((n>>i) & 0x00001) + '0';
  }
  return s[k+1]-48;
  
}


vandermonde()
{
  int i,j;
  
  
  for(i=0;i<count;i++){
    g[0][i]=GF32[div(1,G[i])]; 
    printf("%d ",g[0][i]); 
  }
  printf("\n");
  for(i=0;i<count;i++){
    g[1][i]=GF32[div(L[i],G[i])]; 
    printf("%d ",g[1][i]); 
  }
  printf("\n");
  for(j=2;j<M;j++){
    for(i=0;i<count;i++){
      g[j][i]=GF32[div(mltn(j,L[i]),G[i])]; 
      printf("%d ",g[j][i]); 
    }
    printf("\n");
  }
  
}


/* バイナリ表現 */
vin(){
  int i,j,k;
  
  
  printf("vin\n");
  for(i=0;i<M;i++){
    for(k=0;k<M;k++){
      /* printf("bin"); */
      for(j=0;j<count;j++) 
	printf("%d",bit(g[i][j],k));
      printf(",\n");
    }
  }
  
}


/* ビット列から多項式の計算 */
int b2pl(int n,int x)
{
  unsigned int l=0;
  int i,j;
  
  
  /* printf("%b\n",n); */
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


/* 任意の次数をもつ多項式 (0<i<n 次数の項をランダムに選ぶ) */
int mpl(int n,int x)
{
  unsigned int l=0;
  int i,j;
  
  
  /* どうやってn個決めるか？ */
  for(i=n;i>-1;i--){
	 l=add(l,mltn(i,x)); 
       }
  if(l!=0){
    L[count]=x;
    count++;
  }
  return l;
  
}


/* 係数の選択 (monic) [256,128,*]-Goppa
if 128-bit key size then 16-bit poly over GF(2), 
and 14 cofficients over GF(2^8) */




/* パラメータの決定 (k=n-mt) */





/* 何ビット整数か返す */
int cb(unsigned int x)
{
  int i,j;
  
  i=0;
  while(x>0){
    x=(x>>1); i++;
  }
  return i;
  
}


/* 有限体上での掛け算 */
int mlt(int x,int y)
{
  if(x==0||y==0){
    return(0);
  }
  return ((x+y-2)%(N-1))+1;
}


/* 有限体上での累乗 */
int mltn(int n,int x)
{
  int i,j;
  
  
  if(n==0) return 1;
  
  i=x;
  for(j=1;j<n;j++)
    i=mlt(i,x);
  
  return i;
  
}


/* 有限体上での足し算 */
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
    z=(GF64[x-y+1]-1)+(y-1);
    z=(z%(N-1))+1;
  }
  else if(x < y){
    z=(GF64[y-x+1]-1)+x-1;
    z=(z%(N-1))+1;
  }
  else{
    z=0;
  }
  return(z);
}


/* 有限体上での割り算 */
int div(int x,int y)
{
  if(y==0){
    /* printf("yが0\n"); */
    /* exit(1); */
  }
  else if(x==0){
    return 0;
  }
  return ((x-y+(N-1))%(N-1))+1;
}


/* 多項式の逆数 */
int inv(int l)
{
  int i,j;
  
  
  if(l==0)
    printf("分母が０です。\n");
  
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

