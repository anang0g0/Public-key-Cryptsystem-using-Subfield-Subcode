/* ATTACKING PROGRAM of C */


#include <stdio.h>
/* #include <stdlib.h> */

/* 組合せの生成: レジスタを使った高速版。 */

#define N 64 /* N < 65536 */
#define K 8 /* K=16,24,31.63,127 */



typedef unsigned int set;
#define first(n) ((set) ((1ULL << (n)) - 1ULL))

 unsigned int u[32],ss[256]; 

unsigned int count,count2; 

/* テーブルの中から距離の等しいベクトルの組合せを探索する */
static char *sss[64]={
  "0","1110","010101","10011","01111","101101","110110","111000",
  "1","01111","10100","100010","011010","101100","110111","111001",
  "10","1100","10111","100001","011001","101111","110100","111010",
  "100","001010","010001","100111","11111","101001","110010","111100",
  "1000","000110","11101","101011","10011","100101","111110","110000",
  "10000","011110","000101","110011","001011","111101","100110","101000",
  "100000","101110","110101","000011","111011","001101","010110","011000",
  "1001","111","11100","101010","010010","100100","111111","110001"};

// でシンドロームが異なるかどうか確認する！



set nextset(set x)
{
  set smallest,ripple,n_small,ones;
  
  smallest=x& -x;
  ripple=x+smallest;
  n_small=ripple & -ripple;
  ones=((n_small/smallest)>>1)-1;
  return ripple|ones;
}

unsigned int ccitt=0;
unsigned int printest(set s)
{
  int i,cnt=0,jj,k;
  unsigned int b[K],c[K];
  unsigned int test[K];

for(i=0;i<K;i++)
c[i]=0;

ccitt++;

  for(i=1;i<=N;i++){
    if(s&1){
      /* printf("%s %d",sss[i],i); */
      b[cnt++]=strtol(sss[i-1],(char **)NULL,2); 
       if(cnt>8) 
       printf("%d %d %d %d\n",i,cnt,count,ccitt); 
    }
    s >>= 1;
  }

if(cnt>8)
printf("%d\n",cnt);
  for(jj=0;jj<cnt;jj++){
    for(k=0;k<cnt;k++){
      c[jj]=c[jj]+(b[k]^b[jj]); /* error */
     /* printf("%u ",b[k]^b[jj]); */
    }
/* printf("\n"); */

  }

/* 同型群を構成するようなエラーの候補 */
if(c[0]>0 && c[0]==c[1] && c[1]==c[2] && c[2]==c[3] && c[3]==c[4]&& c[4]==c[5] && c[5]==c[6] && c[6]==c[7] && c[7]==c[0]){


printf("%u\n",count++);
/*
printf("%u %u %u %u %u %u %u %u\n",b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);
printf("-%u %u %u %u %u %u %u %u-\n",c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7]);
*/

for(jj=0;jj<cnt;jj++){
  for(k=0;k<cnt;k++)
    test[k]= b[k]^b[jj]; 
/* q2(K,test); */
}


/*
for(i=0;i<K;i++){
for(j=0;j<K;j++)
q2(K,test[i][]);
}
*/

}

/* printf("\n"); */
  
}


/*
001110
010101
001111
101101
110110
010100
101100
110111

0 27 1 35 56 26 34 57 
27 0 26 56 35 1 57 34 
1 26 0 34 57 27 35 56 
35 56 34 0 27 57 1 26 
56 35 57 27 0 34 26 1 
26 1 27 57 34 0 56 35 
34 57 35 1 26 56 0 27 
57 34 56 26 1 35 27 0 
*/
int main(){
  int i,j;
  set x;
  static int o[8]={14,21,15,45,54,20,44,55};
  char t[16];


for(i=0;i<K;i++){
for(j=0;j<K;j++)
printf("%d ",o[i]^o[j]);
printf("\n");
}
for(i=0;i<8;i++)
itob(o[i],t);

  i=1; x=first(K);
  while(! (x & ~first(N))){
   /* printf("%4d:\n",i); */
    printest(x);
    x=nextset(x); i++;
  }

printf("%u\n",count);
  return -1;

}


/* 安定なソート */
void q2(int n,unsigned int a[])
{
  int i,j,p;
  int lstack[N],rstack[N];
  unsigned int x,t,l,r;
  
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


void inssort(int n,unsigned int a[])
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


void itob(int n,char s[])
{
  int i,j;
  
  for(i=5,j=0;i>=0;i--,j++){
    s[j]=((n>>i) & 0x0001) + '0';
  }
  
  for(j=0;j<6;j++)
    printf("%d",s[j]-48);
printf("\n");

/*
    if(s[j]-48==1)
      k++;
  }
  return k;
*/
}


/* 組合せを使って全てのラベルが一致するベクトルの組を探索する */
/* 攻撃[2] は線形解読法 行列Gを未知の定数として解読 */
void et()
{
  int i,j;

  

for(i=0;i<8;i++){
  for(j=0;j<8;j++)
    printf("%u\n",strtol(sss[i][j],(char **)NULL,2));
}

}








/* in header : unsigned int model; */

/*
static unsigned short h2[8]={32884,16562,8424,4235,2135,1054,717,303};
0b1000000001110100,
0b0100000010110010,
0b0010000011101000,
0b0001000010001011,
0b0000100001010111,
0b0000010000011110,
0b0000001011001101,
0b0000000100101111
*/



/* シンドロームの計算 */
unsigned int syn()
{
int b,t,l,i;
unsigned int j,h2,model;

  j=itob(model^b,t);
  if(j==5){
    count2++;
    l=0;
    for(i=0;i<8;i++)
      l=(l<<1)+(itob(h2[i]&b,t)%2);

     printf("%u %b %d\n",l,b,j);

    if(ss[l]==0){
      ss[l]=b;
      count++;
      if(count==256)
	printf("%d\n",count2);

       printf("%u %u\n",l,b); 
    } 
    
       count++;
       printf("%u\n",count);
 }
   return j;
}


  
/* in main
  model==strtoul("1001001001001000",(char **)NULL,2);
  scanf("%u",&N);
  scanf("%u",&K);
  for(i=0;i<N;i++)
    u[i]=(1<<i);
  for(i=0;i<256;i++)
    ss[i]=0;

 printf("%u %s\n",model,itoa(model,2));

 count=0;count2=0; 

  printf("%d\n",count);
  for(i=0;i<256;i++)
    printf("%d %u\n",i,ss[i]);
  printf("%d\n",count2);
*/
