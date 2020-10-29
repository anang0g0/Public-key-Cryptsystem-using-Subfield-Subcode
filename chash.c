#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "gf.h"




unsigned char aa[64]; //={ 148, 246, 52, 251, 16, 194, 72, 150, 249, 23, 90, 107, 151, 42, 154, 124, 48, 58, 30, 24, 42, 33, 38, 10, 115, 41, 164, 16, 33, 32, 252, 143, 86, 175, 8, 132, 103, 231, 95, 190, 61, 29, 215, 75, 251, 248, 72, 48, 224, 200, 147, 93, 112, 25, 227, 223, 206, 137, 51, 88, 109, 214, 17, 172};



#define str_length 128
#define password_length 256

char password[password_length + 1];



unsigned long xor128(void)
{
  unsigned int a=0;

  static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned long t;

    a=rand();
    t=x^(a<<11);a=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}


void seed(void){
    /*
    * 変数宣言
    */
    char str[str_length + 1];
    time_t t;
    int i, j, k, rnd;
    
    
    /*
    * 乱数の初期化
    */
    srand(clock()+time(&t));

    /*
    * 乱数生成とパスワードの生成
    */
    for(i = 0; i < str_length; i++) {
        for(j = 0; j < 2; j++) {
            k = i * 2 + j;
            do {
                rnd = rand();
                password[k] = str[i] + rnd;
            }while(!isalnum(password[k]));
        }
    }
    
    /*
    * NULL文字の挿入
    */
    password[password_length] = '\0';
    
    /*
    * パスワードの出力
    */
//    printf("生成パスワード：%s",password);
    
return;
  
}



int mlt(int x, int y){

    if(x==0||y==0)
        return 0;
  
  return ((x+y-2)%(M-1))+1;
}


int mltn(int n,int x){
  int i,j;

if(n==0)
return 1;
  i=x;
    for(j=0;j<n-1;j++)
      i=mlt(i,x);

  return i;
}


void pMAT(MAT A,int k,int n,int a){
  int i,j;

  if(a==0){
  if(k>n){
    for(i=0;i<n;i++){
      for(j=0;j<k;j++)
	printf("%2d,",A.x[j][i]);
      printf("\n");
    }
    printf("\n");
  }
  if(n==k || k<n){
    for(i=0;i<k;i++){
      for(j=0;j<n;j++)
	printf("%2d,",A.x[i][j]);
      printf("\n");
    }
    printf("\n");
  }
  }
  if(a==1){
    if(k>n){
      for(i=0;i<n;i++){
	for(j=0;j<k;j++)
	  printf("%2d,",A.y[j][i]);
	printf("\n");
      }
      printf("\n");
    }
    if(n==k || k<n){
      for(i=0;i<k;i++){
	for(j=0;j<n;j++)
	  printf("%2d,",A.y[i][j]);
	printf("\n");
      }
      printf("\n");
    }
  }

}

MAT n2k(MAT Z){
  MAT Q;
  int i,j;

  for(i=0;i<K;i++){
    for(j=0;j<N;j++)
      Q.x[i][j]=Z.x[j][i];
  }

  return Q;
}

MAT N2K(unsigned short A[N][K]){
  MAT B={0};
  int i,j;

  for(i=0;i<K;i++){
    for(j=0;j<N;j++){
      B.x[i][j]=A[j][i];
      printf("%2d,",B.x[i][j]);
    }
    printf("\n");
      }
    printf("\n");
    
  return B;
}


MAT Y2X(MAT Q,int k,int n){
  int i,j;
  MAT SGP={0};

  if(k>n){
    for(j=0;j<n;j++){
      for(i=0;i<k;i++){
	SGP.x[i][j]=Q.y[i][j];
      }
    }
  }
  if(k<=n){
    for(i=0;i<k;i++){
      for(j=0;j<n;j++)
	SGP.x[i][j]=Q.y[i][j];
    } 
  }

  
  return SGP;
}
//
MAT K2N(unsigned short A[K][N]){
  int i,j;
  MAT G={0};
  
  for(i=0;i<K;i++){
    for(j=0;j<N;j++)
      G.x[j][i]=A[i][j];
  }
  //pMAT(G,N,K,0);
  //exit(1);
  
  return G;
}

MAT N2M(MAT A,int k){
  int i,j;
  MAT G={0};
  

  for(i=0;i<k;i++){
    for(j=0;j<k;j++)
      G.x[i][j]=A.x[i][j];
  }

  return G;
}

MAT M2N(MAT A,int n){
  int i,j;
  MAT G={0};
  

  for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      G.x[i][j]=A.x[i][j];
  }

  return G;
}

