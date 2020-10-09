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
      a=b2pl(strtoul(f4[i],(char **)NULL,2),j); /* $B<0$NCM(B from key */
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



/* k$BHVL\$N%S%C%H<h$j=P$7(B */
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


/* $B%P%$%J%jI=8=(B */
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


/* $B%S%C%HNs$+$iB?9`<0$N7W;;(B */
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


/* $BG$0U$N<!?t$r$b$DB?9`<0(B (0<i<n $B<!?t$N9`$r%i%s%@%`$KA*$V(B) */
int mpl(int n,int x)
{
  unsigned int l=0;
  int i,j;
  
  
  /* $B$I$&$d$C$F(Bn$B8D7h$a$k$+!)(B */
  for(i=n;i>-1;i--){
	 l=add(l,mltn(i,x)); 
       }
  if(l!=0){
    L[count]=x;
    count++;
  }
  return l;
  
}


/* $B78?t$NA*Br(B (monic) [256,128,*]-Goppa
if 128-bit key size then 16-bit poly over GF(2), 
and 14 cofficients over GF(2^8) */




/* $B%Q%i%a!<%?$N7hDj(B (k=n-mt) */





/* $B2?%S%C%H@0?t$+JV$9(B */
int cb(unsigned int x)
{
  int i,j;
  
  i=0;
  while(x>0){
    x=(x>>1); i++;
  }
  return i;
  
}


/* $BM-8BBN>e$G$N3]$1;;(B */
int mlt(int x,int y)
{
  if(x==0||y==0){
    return(0);
  }
  return ((x+y-2)%(N-1))+1;
}


/* $BM-8BBN>e$G$NN_>h(B */
int mltn(int n,int x)
{
  int i,j;
  
  
  if(n==0) return 1;
  
  i=x;
  for(j=1;j<n;j++)
    i=mlt(i,x);
  
  return i;
  
}


/* $BM-8BBN>e$G$NB-$7;;(B */
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


/* $BM-8BBN>e$G$N3d$j;;(B */
int div(int x,int y)
{
  if(y==0){
    /* printf("y$B$,(B0\n"); */
    /* exit(1); */
  }
  else if(x==0){
    return 0;
  }
  return ((x-y+(N-1))%(N-1))+1;
}


/* $BB?9`<0$N5U?t(B */
int inv(int l)
{
  int i,j;
  
  
  if(l==0)
    printf("$BJ,Jl$,#0$G$9!#(B\n");
  
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

