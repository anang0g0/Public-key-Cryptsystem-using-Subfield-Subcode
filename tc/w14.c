/* ATTACKING PROGRAM of C */


#include <stdio.h>
//#include "code.h"


/* CodeBreaking Test Sample of Parametor */
#define LEN 16 /* 符号長 */
#define DIM 8 /* 次元 */
#define N 256 /* number of error pattarn condition 1 */
#define M 256 /* number of error pattern condition 2 */
#define TESTCODE 16
#define LENGTH 31

int n,k,r[LEN];
unsigned int count,count2;
unsigned int se[N],h[N];

static unsigned int v[32]={ /* The set of unit vector. */
1,2,4,8,16,32,64,128,256,512,
1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,
1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,
268435456,536870912,1073741824,2147483648};

unsigned int model;


/* char *Ht="10001111000010011"; */


/* [24,12,8]-Golay code's H means [A_k|I_k] 
static unsigned int ehc[12]={
"101000111011100000000000",
"110100011101010000000000",
"011010001111001000000000",
"101101000111000100000000",
"110110100011000010000000",
"111011010001000001000000",
"011101101001000000100000",
"001110110101000000010000",
"000111011011000000001000",
"100011101101000000000100",
"010001110111000000000010",
"111111111110000000000001"
};
static unsigned int H[15]={
"0000000000000010001111000010011",
"0000000000000100011110000100110",
"0000000000001000111100001001100",
"0000000000010001111000010011000",
"0000000000100011110000100110000",
"0000000001000111100001001100000",
"0000000010001111000010011000000",
"0000000100011110000100110000000",
"0000001000111100001001100000000",
"0000010001111000010011000000000",
"0000100011110000100110000000000",
"0001000111100001001100000000000",
"0010001111000010011000000000000",
"0100011110000100110000000000000",
"1000111100001001100000000000000"
};
*/


/* [6,3,3] N=8 named H */
/* [16,8,5] N=256 name Gp */
/* [24,,] N=4096 named golay */
/* [31,,] N=2^14 named bch31 */
/* [55,,] N=2^20 named Gp55 */
/* [63,16,23]-BCH N=2^32 named gt63[63] */
/* [127,64,] N= 2^47 named bch127 */
/* [256,,] N=2^64 (nonsense) named Gp256 */


unsigned int s[N],es[N]; /* syndrome-error table [2] [1], diff */


main(){
  int i,j,kkk=0,h,l;
  unsigned int em=0;
  char t[LEN];
  
  /* init table */
  count=0;count2=0;
  for(i=0;i<N;i++)
    s[i]=0;
  
/* if one choose a vector model 
   model=strtoul("1001001001001001",(char **)NULL,2);
*/

  printf("-----test condition 1-----\n");
  printf("[16,8,5]-Goppa Code\n");

/* printf(" [31,16,7]-BCH Code\n"); */

  for(i=0;i<DIM;i++)
    printf("%u\n",h2[i]);
/* printf("%u\n",h31[i]); */
  printf("\n");

  printf("----Testing Parametors----\n");
  printf("The number of error pattern N=%d \n",N);
  printf("If you Choose error-vector's pattern randomely then\n");
  printf("O(knN^2logN)=%u\n",DIM*LEN*N*N*DIM);

  printf(" error-vector's weight fixed for example w=10 \n");
  printf("O(k^2nN)= %u\n",16*16*31*N);
/* If you need to use the (adaptive) error pattern. */
/* printf("%u\n",model); */
  printf("\noutput:\n\n");


/* generate error pattern randomely [1] (define CODE) */
  nanka();


/* [2] の値が入らないのは何故？ */
 /* comb(1); */ /* or rP */
  if(count<N-1)
    printf("Can't fill the table! %u < %u\n",count,count2);



  srand((unsigned int)time(NULL)); /* timing function */
printf("Print the error-syndrome table condition [1] \n");
printf("is error vector as es[%u] and [2] is s[%u]\n",N,M);
  printf("Aut=1\n");
  for(i=0;i<N;i++){
    printf("%x,\n",es[i]);
  }

printf("--------------- analisys first diff graph  ----------------\n");
   /*
     printf("Aut>1\n");
     for(i=0;i<N;i++)
     printf("%u,\n",s[i]);
   */  

  printf("------sort array of N vectors----- \n");
  q2(N,es);printf("\n");
  
  printf("w>0\n\n print graph condition1\n"); 
/*
  printf("{\n");
  for(i=0;i<M;i++){
    printf("{");
    for(j=0;j<M;j++)
      printf("%x,",(es[i]^es[j])); 
*/
/* print diff of err ptn of [1] 
    printf("},\n");
  }
  printf("}\n\n");
*/
  
  k=10; printf("---weight of vector---\n");
  printf("w=%d\n",k);

/* make graph condition2 
  printf("{\n");
  for(i=0;i<M;i++){
    printf("\n");
    for(j=0;j<M;j++)
*/
/* printf("%d,",(s[i]^s[j])); */ /* print differential error patterns of [2].*/

/*
    printf("},\n");
  }
  printf("}\n\n");
*/


printf("------------------ make all graph for unit vector ----------------\n");
  /* construct differential graph Gamma_i for unit vector m_i={v_i}^k */
  printf("We needs %d differential graph for k=%d.\n",LEN);

  for(i=0;i<LEN;i++){
    for(j=0;j<LEN;j++) /* generate differential text */
      em=(em<<1)+ itob(v[i]&h2[j],t)%2; /* golay[24],bch31[31],h2[8] */

    printf("v_%d m_%d= %u\n",i+1,v[i],em);
    gi(em);
    em=0;
  }

printf("----------- made diff graph and find the key! -----------\n");
bingo(es,se);



/*
  printf("------- condition 2 -------");
  for(i=0;i<LEN;i++){
    printf("%u\n",v[i]);
    for(j=i;j<LEN;j++)
      printf("%d,",(v[i]^v[j]));
    printf("\n");
  }
*/

/* collect N patterns and define G' */


/* choose vector atrandom, check whether m'=w  */


/* solve liner system c=m_iG'+z */
/* solve() */


}


/* 重み一定のベクトル生成 */
comb(int m)
{
  int i;


/* これがうまく動かない！ */
  if(m>k)
    action();
  else
    for (i=r[m-1]+1;i<=n-k+m;i++){
      r[m]=i;comb(m+1);
      if(count==(N-1)) break; 
    }


}


/* 符号を変えるところ */
action(void)
{
  int i,j;
  char t[LEN];
  unsigned int b,l;


  b=0; /* make constant weight vector */
  for(i=1;i<=k;i++)
    b=b+v[r[i]]; 

  j=itob(model^b,t); /* mask vector */
  if(j>0){ /* not equal to "model" */
    if(itob(b,t)==k){ /* equal to distance k */
       printf("b= %u,j=%d\n",b,j); 



      l=0;
      for(i=0;i<DIM;i++)
	l=(l<<1)+(itob(h2[i]&b,t)%2); /* ehc[12],h31[15],h2[8] */
printf("h2= %u\n",l);
      if(l<N){
	if(s[l]==0){
	  if(b>0){
	    s[l]=b;
	    printf("s= %u\n",count);
	    count++; /* counting roop for teble */
	  }
	  /* print graph */
	  if(count==N)
	    {
	      for(i=0;i<N;i++)
		printf("%d %u %d\n",i,s[i],itob(s[i],t));
	    }  
	}
      }
      count2++; /* 衝突を含めた探索回数 */
    }
  }
}



/* 置換関数 */
unsigned int rP(unsigned int A)
{
  int i,j,c;
  unsigned int P[LENGTH],X,W;
  
  
  //make random permtation matrix and permute binary vector A
    for(i=0;i<LEN+1;i++){
      X=1;
      P[i]=(X<<(rand()%LEN));
      W=P[i];
      c=0;
      for(i=0;i<cb( A&W );i++){
	if(tstbit( A&W,i)==1)
	  c++;
      }
      X= X+((c%2)<<1);
    }
  
  return X;
}



int itob(int n,char s[])
{
  int i,j,k=0;
  
  for(i=LEN-1,j=0;i>=0;i--,j++){
    s[j]=((n>>i) & 0x00001) + '0';
  }
  
  for(j=0;j<LEN;j++){
    if(s[j]-48==1)
      k++;
  }
  return k;
}


int tstbit(unsigned int A,int p)
{
int i,j;

 for(i=LEN-1,j=0;i>=0;i--,j++){
    s[j]=((n>>i) & 0x00001) + '0';
  }
  

if(s[p]-48==1)
  return 1;

}


/* 乱数によるエラーテーブル */
void nanka()
{
  int n,l,b,i,j;
  char t[LEN];
  

  for(i=0;i<N;i++)
    es[i]=0;
  srand(n=(unsigned int)time(NULL)); /* timing function */

/*
   scanf("%d",&n);
   srand(n);
*/

  printf("selected rand seed %d\n",n);
  count=0;count2=0;

  for(;;){
    b=rand();
    l=0;
    for(i=0;i<8;i++)
      l=(l<<1)+(itob(h2[i]&b,t)%2); /* ehc[12],h31[15],h2[8](Goppa) */
    
    /* printf("%u %b %d\n",l,b,j); */
    
    if(l<(N-1)){   /* syndrome vector space */
      if(es[l]==0){
	if(itob(b,t)>0){   /* vector weight condition 1 */
	  es[l]=b;
	  printf("%u %d %u %d\n",count,itob(b,t),b,l); 
	  count++;
	  /* (print graph) 
	     if(count==(N-1)){
	     printg();
	     }
	  */
	}
      }
    }
    count2++;
    if(count==N-1)
      break;
  }	/* end of for(;;) */

}



void printg()
{
  int i,j;
  char t[32];
  
  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%d,",itob(es[i]^es[j],t));
    printf("\n");
  }
  
}



/* using table for making i_th diff graph */
void gi(int m)
{
  int i,j,h,kkk=0,l;
  unsigned int n;
  
  
  srand(m);
  for(i=0;i<N;i++)
    se[i]=0;	/* 全て初期化 */
  
  for(i=0;;i++){
    h=0;l= rand()%N;
    for(j=0;j<kkk+1;j++){ 
      /* printf("%u ",se[j]); */
      if(se[j]==es[l]) /* 同一のエラーを選ばない */
	{ h=1; /* printf("%u=se[%d] %u=es[%d]\n",se[j],j,es[l],l); */ }
      if(h==1)
	break;
    }
    if(h==0){
      /* printf("%d %d\n",kkk,l); */
      printf("%u,\n",m^es[l]); /* m_i に対する暗号文 */
      se[kkk]=es[l]; /* (es: Aut=1) 選んだエラーを記録 */
      kkk++;
      if(kkk==N-1){ /* もしテーブルが埋まったら */
	se[N-1]=es[0]; 
	printf("%d %d\n",kkk,es[0]);
	printf("%d times\n",i);/* i 回目で完成 */
	break;
	/*
	   for(j=0;j<i;j++)
	   printf("%u %u\n",se[j],s[j]);
	   */
      }
    }
    
  }
  printf("end of %d seed= %u\n",m,m);
}





/* breaking if condition is [1] */
void bingo(unsigned int m[],unsigned int mm[]) 
/* cyphertext and it's difference */
{
  int i,j,count=0,flg[2][N];
  unsigned int d,e,f,em[N];
  
  /*
     for(i=0;i<2;i++){
     for(j=0;j<N;j++)
     flg[i][j]=0;
     }
     */
  
  /* for(i=0;i<N;i++) */
  while(i<N){
    d=m[i]^mm[j];
    
    /* q2(N,em);  差分の一致する要素が存在するか */
    printf("\n");
    for(j=0;j<N;j++){
      e=m[i]^mm[j];
      if(e==d){
	printf("(%d,%d) equal\n",i,j);
	break;
      }
    }
    i++;
  }
}


/*
   for(i=0;i<N;i++){
   if(flg[0][i]!=1){
   d=m[i]^mm[j];
   
   for(j=0;j<N;j++){
   if(flg[1][j]!=1)
   e=m[i+1]^mm[j];
   if(e==d){
   printf("bingo! %u %d times\n",e,j);
   count++; flg[0][i]=1; flg[1][j]=1;
   }
   }
   
   if(count>0){
   printf("same pattern exsists %d at %d\n",count,i);
   count=0;
   }
   }
*/


int an(int c)
{
  int i,j,m=0;
  char t[16];
  
  
  hind(c);
  for(i=0;i<16;i++)
    m=(m<<1)+itob(c&bch31[i],t); /* golay[24],bch31[31] */
  printf("%u\n",m); /* binary trans..? */
  
  return m;
  
}


unsigned char dc(unsigned short w)
{
  int i,j;
  unsigned char a;
  
  /* printf("%b ",w); */
  a=(w>>8); hind(a);
  /* printf("%b\n",a); */
  
  return a;
  
}


void hind(unsigned short m)
{
/* 統計をとる */
  h[m]++;

}


int seki()
{
  unsigned int a,b,c;
  
  c=0;
  while(a!=0){
    if (a & 1) c^=b;
    b<<=1; a>>=1;
  }
  return c;
}


/* parity check */
void pc()
{
  int i,j,c,k,l,syn[N];
  char t[16];
  

  for(i=0;i<8;i++){
  for(j=0;j<8;j++)
    printf("%d",itob(Gp[i]&h2[j],t)); /* 8-bit */
  printf("\n");
}
  
  for(i=0;i<N;i++){
    l=0;
    for(j=0;j<16;j++)
      l=(l<<1)+itob(Gt[j]&i,t); /* 7-bit */
    syn[i]=l;
  }
  
  
  /*
     for(i=0;i<16;i++){
     for(k=0;k<4;k++){ 
     printf("%b ",GH[k][i]);
     
     c=0; 
     for(j=0;j<16;j++){
     if(bit(Gp[i],j)==1){
     c=GH[k][j];
     printf("%d ",c); 
     }
     }
     printf("\n");
     
     printf("%d\n",c);
     printf("%d ",c); 
     }
     printf("\n");
     }
*/
}


/* 復号関数2 */
void decode(unsigned int r)
{
  unsigned int c,e,m;
  
  
  m=syn(r);
  e=es[m];
  c=r^e;
  printf("%d %d %d\n",c,e,r);
  
}


/* 差分に基づくグラフの生成 */
unsigned int gii(unsigned int m,int i)
{
  
  /* printf("%b %b\n",m,i); */  

  return m^(1<<i); /* 1-bit差分 */
  
}



/* 受信語に対するシンドローム計算 */
unsigned int syn(unsigned int x)
{
  int i,j,c;
  char t[32];


  c=0;
  for(j=0;j<15;j++)
    c=(c<<1)+itob(x&h31[j],t); /* h31[] */
  /* printf("%d_%b\n",c,i); */
  
  return c;
  
}


/* F_2 上の多項式の割り算 */
void pd(unsigned int p,unsigned int d)
{
  unsigned int x,y,r,q,i,j;
  
  q=p; y=d;
  r=0;
  i=cb(q)-cb(y);
  y=(y<<i);
  
  while(y > 0){
    if(cb(q)==cb(y)){
      r=r + (1<<i);
      printf("fi%u %u\n",q,y); /* needs binary representation */
      q=(q^y);
      printf("if%u %u\n",q,y); /* needs binary representation */
    }
    y=d;
    i=cb(q)-cb(y);
    y=(y<<i);
  }
  printf("%u %u\n",r,q); /* needs binary representation */
  
}


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


/* 安定なソート */
void q2(int n,int a[])
{
  int i,j,l,r,p;
  int lstack[N],rstack[N];
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


/* 配列を文字列に変換して比較 */
int l2s(char s[])
{
  char *p,*q;
  int count=0,i,j;
  
  for(i=0;i<N;i++){
    if(strcmp(p,q)== -1){
      count++;
      printf("%d,",count);
    }
  }
  printf("\n");
  
  return count;
}


/* 自己同型群の位数の概算 */
void ord_aut(int color)
{
  int i,j,rel[N];
  unsigned int o=1;
  char s[N];
  

  /* Call : RPG(N); */
  for(i=0;i<N;i++)
    rel[N]=l2s(s[i]);
  
  for(i=0;i<N;i++)
    o=o*rel[j];

  printf("%u\n",o);

}

