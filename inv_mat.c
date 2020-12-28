///////////////////////////////////////////////////////////////////////////
//
// (over finite field) Gauss-Jordan法による逆行列
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAXN 4
//#define N 16 //order of GF(q)
#define F K  //dimension of matrix


unsigned short mat[N][K]={0};
//elements of GF16
//static const unsigned char gf[N]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
//index of GF16
//static const unsigned char fg[N]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};

//static const unsigned char gf[N]={0,1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142};
//static const unsigned char fg[N]={0,1,2,26,3,51,27,199,4,224,52,239,28,105,200,76,5,101,225,15,53,142,240,130,29,194,106,249,201,9,77,114,6,139,102,48,226,37,16,34,54,148,143,219,241,19,131,70,30,182,195,126,107,40,250,186,202,155,10,121,78,229,115,167,7,192,140,99,103,222,49,254,227,153,38,180,17,146,35,137,55,209,149,207,144,151,220,190,242,211,20,93,132,57,71,65,31,67,183,164,196,73,127,111,108,59,41,85,251,134,187,62,203,95,156,160,11,22,122,44,79,213,230,173,116,244,168,88,8,113,193,248,141,129,100,14,104,75,223,238,50,198,255,25,228,166,154,120,39,185,181,125,18,69,147,218,36,33,138,47,56,64,210,92,150,189,208,206,145,136,152,179,221,253,191,98,243,87,212,172,21,43,94,159,133,61,58,84,72,110,66,163,32,46,68,217,184,124,165,119,197,24,74,237,128,13,112,247,109,162,60,83,42,158,86,171,252,97,135,178,188,205,63,91,204,90,96,177,157,170,161,82,12,246,23,236,123,118,45,216,80,175,214,234,231,232,174,233,117,215,245,235,169,81,89,176};

//static const unsigned short gf[N]={0,1,2,4,8,16,32,64,128,256,305,339,407,31,62,124,248,496,209,418,117,234,468,153,306,341,411,7,14,28,56,112,224,448,177,354,501,219,438,93,186,372,473,131,262,317,331,423,127,254,508,201,402,21,42,84,168,336,401,19,38,76,152,304,337,403,23,46,92,184,368,465,147,294,381,459,167,334,429,107,214,428,105,210,420,121,242,484,249,498,213,426,101,202,404,25,50,100,200,400,17,34,68,136,272,273,275,279,287,271,303,367,495,239,478,141,282,261,315,327,447,79,158,316,329,419,119,238,476,137,274,277,283,263,319,335,431,111,222,444,73,146,292,377,451,183,366,493,235,470,157,314,325,443,71,142,284,265,291,375,479,143,286,269,299,359,511,207,414,13,26,52,104,208,416,113,226,452,185,370,469,155,310,349,395,39,78,156,312,321,435,87,174,348,393,35,70,140,280,257,307,343,415,15,30,60,120,240,480,241,482,245,490,229,458,165,330,421,123,246,492,233,466,149,298,357,507,199,398,45,90,180,360,481,243,486,253,506,197,394,37,74,148,296,353,499,215,430,109,218,436,89,178,356,505,195,390,61,122,244,488,225,450,181,362,485,251,502,221,442,69,138,276,281,259,311,351,399,47,94,188,376,449,179,358,509,203,406,29,58,116,232,464,145,290,373,475,135,270,301,363,487,255,510,205,410,5,10,20,40,80,160,320,433,83,166,332,425,99,198,396,41,82,164,328,417,115,230,460,169,338,405,27,54,108,216,432,81,162,324,441,67,134,268,297,355,503,223,446,77,154,308,345,387,55,110,220,440,65,130,260,313,323,439,95,190,380,457,163,326,445,75,150,300,361,483,247,494,237,474,133,266,293,379,455,191,382,461,171,342,413,11,22,44,88,176,352,497,211,422,125,250,500,217,434,85,170,340,409,3,6,12,24,48,96,192,384,49,98,196,392,33,66,132,264,289,371,471,159,318,333,427,103,206,412,9,18,36,72,144,288,369,467,151,302,365,491,231,462,173,346,389,59,118,236,472,129,258,309,347,391,63,126,252,504,193,386,53,106,212,424,97,194,388,57,114,228,456,161,322,437,91,182,364,489,227,454,189,378,453,187,374,477,139,278,285,267,295,383,463,175,350,397,43,86,172,344,385,51,102,204,408,};
//static const unsigned short fg[N]={0,1,2,409,3,306,410,27,4,435,307,391,411,169,28,203,5,100,436,59,308,53,392,66,412,95,170,332,29,288,204,13,6,421,101,195,437,240,60,185,309,321,54,503,393,229,67,278,413,417,96,508,171,467,333,354,30,474,289,452,205,257,14,461,7,358,422,341,102,270,196,154,438,140,241,371,61,349,186,121,310,337,322,314,55,405,504,191,394,251,230,481,68,39,279,364,414,471,418,318,97,92,509,432,172,82,468,79,334,248,355,137,31,175,475,326,290,20,453,126,206,85,258,218,15,400,462,48,8,456,359,43,423,380,342,297,103,129,271,493,197,115,155,161,439,293,141,72,242,223,372,443,62,23,350,181,187,150,122,428,311,478,338,368,323,215,315,76,56,329,406,388,505,449,192,500,395,34,252,283,231,263,482,145,69,178,40,490,280,487,365,385,415,465,472,255,419,238,319,227,98,51,93,286,510,304,433,167,173,18,83,398,469,90,80,246,335,403,249,37,356,268,138,347,32,261,176,485,476,213,327,447,291,221,21,148,454,378,127,113,207,209,86,234,259,211,219,376,16,88,401,266,463,236,49,302,9,199,457,274,360,117,44,133,424,157,381,496,343,163,298,109,104,105,130,106,272,131,494,107,198,273,116,132,156,495,162,108,440,425,294,158,142,382,73,497,243,344,224,164,373,299,444,110,63,10,24,200,351,458,182,275,188,361,151,118,123,45,429,134,312,189,479,362,339,152,369,119,324,124,216,46,316,430,77,135,57,64,330,11,407,25,389,201,506,352,450,459,193,183,501,276,396,244,35,345,253,225,284,165,232,374,264,300,483,445,146,111,70,441,179,426,41,295,491,159,281,143,488,383,366,74,386,498,416,507,466,353,473,451,256,460,420,194,239,184,320,502,228,277,99,58,52,65,94,331,287,12,511,408,305,26,434,390,168,202,174,325,19,125,84,217,399,47,470,317,91,431,81,78,247,136,336,313,404,190,250,480,38,363,357,340,269,153,139,370,348,120,33,282,262,144,177,489,486,384,477,367,214,75,328,387,448,499,292,71,222,442,22,180,149,427,455,42,379,296,128,492,114,160,208,233,210,375,87,265,235,301,260,484,212,446,220,147,377,112,17,397,89,245,402,36,267,346,464,254,237,226,50,285,303,166,};

//停止コマンド
void
wait (void)
{
  int n;                        // 読み込む変数はローカルに取るべし
  printf (" (enter number and hit return) ");   // 何か表示させたほうが良いだろう
  fflush (stdout);              // just in case
  scanf ("%d", &n);             // fgets(line, LINESIZE, stdin); という手も
}


 void rp(unsigned short* a) {
        int i, j, x;
        time_t t;

	//srand(clock()+time(&t));


        for (i = 0; i < N; i++) {
            a[i] = i;
        }
        for (i = 0; i < N - 2; i++) {
            // rand from i+1 to F-1
            j = (rand() % (N - 1 - i)) + i + 1;

            // swap a[i] and a[j]
            x = a[j];
            a[j] = a[i];
            a[i] = x;
        }
        if (a[N - 1] == N - 1) {
            a[N - 1] = a[N - 2];
            a[N - 2] = N - 1;
        }


 }


int Inv(unsigned short b){
  int i;

      for(i=0;i<N;i++){
        if(gf[mlt(i,b)]==1)
          return i;
      }

}
/*
//detarminant
int det(){
  //double a[N][N]={{2,-2,4,2},{2,-1,6,3},{3,-2,12,12},{-1,3,-4,4}};
double det=1.0,buf;

int n=N;  //配列の次数
int i,j,k;
unsigned short c[N][N]={0};

unsigned short a[N][N]={0};//{{0,3,0,0,},{0,0,4,0},{0,0,0,5},{6,0,0,0}};
//{{0,1,0,0},{0,0,1,0},{0,0,0,1},{1,0,0,0}};
unsigned short inv_a[N][N]={0};
  //{{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,0,1,0}};
//={{1,2,0,1},{1,1,2,0},{2,0,1,1},{1,2,1,1}}; //入力用の配列
unsigned short cc[N][N]={0};

// lab:
//三角行列を作成
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
  if(i<j){
    //    if(a[i][i]==0)
    //   goto lab;
   buf=a[j][i]/a[i][i];
   for(k=0;k<n;k++){
   a[j][k]-=a[i][k]*buf;
   }
  }
 }
}
 
//対角部分の積
for(i=0;i<n;i++){
 det*=a[i][i];
}
 
printf("%f\n",det); // -> 120.000000
 if(det==0.0){
   printf("baka\n");
   exit(1);
 }
 if(det==1.0)
 return 0;
 if(det!=1.0)
   return -1;
}
*/


//なんなのかしらぁ〜
void g3(){
  int i,j,k;
unsigned short bb[F][F]={0};
unsigned short c[N][N]={0};

unsigned short a[N][N]={0};//{{0,3,0,0,},{0,0,4,0},{0,0,0,5},{6,0,0,0}};
//{{0,1,0,0},{0,0,1,0},{0,0,0,1},{1,0,0,0}};
unsigned short inv_a[N][N]={0};

unsigned short cc[N][N]={0};

#pragma omp parallel for    
  for(i=0;i<F;i++){
    a[i][i]=rand()%N;
    bb[i][i]=1;
  }
  for(i=0;i<F;i++){
    //#pragma omp parallel for  
    for(j=i+1;j<F;j++){
      a[i][j]=rand()%256;
      // printf("%d,",a[i][j]);
    }
    //printf("\n");
  }
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",a[i][j]);
    printf("\n");
  }

  for(i=0;i<F;i++){
    //#pragma omp parallel for  
    for(j=i+1;j<F;j++){
      bb[j][i]=rand()%N;      
    }

  }
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",bb[i][j]);
    printf("\n");
  }
  //exit(1);
  for(i=0;i<F;i++){
    for(j=0;j<F;j++){
      //#pragma omp parallel for  
      for(k=0;k<F;k++){
	cc[i][j]^=bb[i][k]&a[k][j];
      }
    }
  }
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",cc[i][j]);
    printf("\n");
  }
  //exit(1); 
}




//正方行列の逆行列
MAT invMAT(MAT a,int n){
  int i,j,k;
  MAT invM={0},dd={0};
  unsigned short buf; //一時的なデータを蓄える
  MAT inv_a={0};
  //n=F;
  unsigned short b[N][N]={0};
  printf("a's copy\n");
  memcpy(invM.x,a.x,sizeof(invM.x));
  pMAT(invM,n,n,0);
  wait();
  
  //単位行列を作る
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
 inv_a.x[i][j]=(i==j)?1:0;
 }
}
 int ii,jj;
 printf("inv_a's 単位行列\n");
 pMAT(inv_a,n,n,0);
 wait();
//掃き出し法

 for(i=0;i<n;i++){
   k=i;
  if(a.x[i][i]==0){
    printf("だめぇ〜！\n");
    //exit(1);
    wait();

    int tmp=0,row=0;
    tmp=a.x[i][i];
    for(ii=i;ii<K;ii++){
      if(a.x[ii][i]>tmp){
	tmp=a.x[ii][i];
	row=ii;
      }
    }
    printf("max=%d\n",row);
    //exit(1);
    wait();

    while(a.x[k][i]==0){
      k++;
      if(k>n){
	printf("この兄ちゃん飼っちゃおうぜ\n");
	//wait();

	//a.o = -1;
	//return a;
	exit(1);
      }
    } 
    for(ii=0;ii<K;ii++)
    dd.x[0][ii]=a.x[i][ii];
    for(ii=0;ii<K;ii++)
      a.x[i][ii]=a.x[row][ii];
    for(ii=0;ii<K;ii++)
      a.x[row][ii]=dd.x[0][ii];
    for(ii=0;ii<K;ii++)
      dd.x[1][ii]=inv_a.x[i][ii];
    for(ii=0;ii<K;ii++)
      inv_a.x[i][ii]=inv_a.x[row][ii];
    for(ii=0;ii<K;ii++)
      inv_a.x[row][ii]=dd.x[1][ii];
    
  }
 
  buf=gf[Inv(fg[a.x[i][i]])];
  for(j=0;j<n;j++){
    a.x[i][j]=gf[mlt(fg[buf],fg[a.x[i][j]])];
    inv_a.x[i][j]=gf[mlt(fg[buf],fg[inv_a.x[i][j]])];
  }
  pMAT(a,n,n,0); 
  //exit(1);
  /*
  for(j=i;j<n;j++){
    a.x[i][j]^=gf[mlt(fg[buf],fg[a.x[i][j]])];
    inv_a.x[i][j]^=gf[mlt(fg[buf],fg[inv_a.x[i][j]])];
  }
  pMAT(a,n,n,0);
  exit(1);
  */

 for(j=0;j<n;j++){
   if(i!=j){
     buf=a.x[j][i];
     for(k=0;k<n;k++){
       a.x[j][k]^=gf[mlt(fg[a.x[i][k]],fg[buf])];
   inv_a.x[j][k]^=gf[mlt(fg[inv_a.x[i][k]],fg[buf])];
     }
   }
 }
 pMAT(a,n,n,0);
 }
 //exit(1);
 
 /*
 for(j=i;j<n;j++){
   if(i!=j){
     buf=a.x[j][i];
     for(k=i;k<n;k++){
       a.x[j][k]^=gf[mlt(fg[a.x[i][k]],fg[buf])];
       inv_a.x[j][k]^=gf[mlt(fg[inv_a.x[i][k]],fg[buf])];
     }
   }
 }
 */

 
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     invM.y[i][j]=inv_a.x[i][j];
 }
 printf("inv_a\n");
 pMAT(inv_a,n,n,0);
 wait();
 
    //wait();
 //memcpy(invM.y,inv_a.x,sizeof(invM.y));

  return invM;
}




//inverse matrix (生成行列を返す)
MAT matinv(){ 
  MAT a={0}; //={{1,2,0,1},{1,1,2,0},{2,0,1,1},{1,2,1,1}}; //入力用の配列
  MAT inv_a={0}; //ここに逆行列が入る
unsigned short buf; //一時的なデータを蓄える
 unsigned short b[N][N]={0},dd[N][N]={0};
 int i,j,k,count; //カウンタ
 int n=F;
 MAT c={0};
 MAT c2={0};
 MAT A={0},C={0};
 unsigned short cc[N][N]={0};
 MAT code={0};
 MAT GG={0};
 //GG.col=K;
 //GG.low=N;

 
 lab:
 
 for(i=0;i<K;i++){
   for(j=0;j<N;j++)
     printf("%2d,",mat[j][i]);
   printf("\n");
 }
    printf("\n");
 
 
 //転置
    code= N2K(mat);
    printf("code=\n");
    pMAT(code,K,N,0);
    wait();
    //codeの後半部分をaにコピー
    for(i=0;i<F;i++){
      for(j=0;j<F;j++){
	a.x[i][j]=code.x[i][K+j]; //rand()%N;
	printf("a%d,",a.x[i][j]);
      }
      printf("\n");
    }
     wait();
    
    
    //aをcにコピー
    for(i=0;i<F;i++){
      for(j=0;j<F;j++){
	c.x[i][j]=a.x[i][j];
	A.x[i][j]=a.x[i][j];
      }
    }

    //K次元正方行列aの逆行列をA.yに代入A.xにはaが入る
    A=invMAT(a,K);
    if(A.o== -1)
      return A;
    printf("mat A.x\n");
    pMAT(A,K,K,0);
    printf("mat A.y\n");
    pMAT(A,K,K,1);
    wait();
     printf("検算\n");
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
	for(k=0;k<n;k++)
	  b[i][j]^=gf[mlt(fg[A.x[i][k]],fg[A.y[k][j]])];
	
	printf("%2d,",b[i][j]);
	// if(j==i && b[i][j]!=1 && j!=i && b[i][j]>0)
	//goto lab;
	
      }
      printf("\n");
    }
    wait();
    
    //exit(1);
    /*
    //単位行列を作る
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
	inv_a.x[i][j]=(i==j)?1:0;
      }
    }
    //掃き出し法
    for(i=0;i<n;i++){
      buf=gf[Inv(fg[a.x[i][i]])];
      for(j=0;j<n;j++){
	a.x[i][j]=gf[mlt(fg[buf],fg[a.x[i][j]])];
	inv_a.x[i][j]=gf[mlt(fg[buf],fg[inv_a.x[i][j]])];
      }
      for(j=0;j<n;j++){
	if(i!=j){
	  buf=a.x[j][i];
	  for(k=0;k<n;k++){
	    a.x[j][k]^=gf[mlt(fg[a.x[i][k]],fg[buf])];
	    inv_a.x[j][k]^=gf[mlt(fg[inv_a.x[i][k]],fg[buf])];
	  }
	}
      }
    }
    
    // printf("\n\n逆行列を出力\n");
    for(i=0;i<n;i++){
      count=0;
      for(j=0;j<n;j++){
	A.y[i][j]=inv_a.x[i][j];
	if(inv_a.x[i][j]==0)
	  count++;
	if(count==n){
	  printf("\nbaka\n\n");
	  exit(1);
	  goto lab;
	}
	//printf(" %d",inv_a[i][j]);
      }
      //printf("\n");
    }
    */

printf("行列を出力\n ={\n");
 pMAT(A,F,F,0);
 
 printf("\n逆行列を出力\n ={\n");
 pMAT(A,F,F,1);

 //検算(A.xとA.y(Aの逆行列)をかけて検算。正しければbは単位行列)
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     for(k=0;k<n;k++)
       b[i][j]^=gf[mlt(fg[A.x[i][k]],fg[A.y[k][j]])];

     printf("b%d,",b[i][j]);
     // if(j==i && b[i][j]!=1 && j!=i && b[i][j]>0)
     //goto lab;
     
   }
   printf("\n");
 }

 //検算
 for(i=0;i<n;i++){
   for(j=0;j<N;j++){
     for(k=0;k<n;k++)
       c2.x[i][j]^=gf[mlt(fg[code.x[k][j]],fg[A.y[i][k]])];
   
     printf("c2%2d,",c2.x[i][j]);
     // if(j==i && b[i][j]!=1 && j!=i && b[i][j]>0)
     //goto lab;
       
   }
   //
 }
 //memcpy(GG.x,code.x,sizeof(code.x));
 //
 //printf("\n");
 pMAT(c2,K,N,0);
 wait();
 
 for(i=0;i<N;i++){
   GG.x[i][i]=1;
 }

 for(i=0;i<K;i++){
   for(j=0;j<N;j++)
     GG.x[i+K][j]=c2.x[i][j];
 }
 printf("生成行列GG.x!\n");
 pMAT(GG,N,K,0);
 wait();

 
 MAT tmp={0};
 for(i=0;i<N;i++){
   for(j=0;j<K;j++)
     tmp.x[j][i]=GG.x[i][j];
 }
 pMAT(tmp,K,N,0); 
 wait();
 
 unsigned short ss[N]={0};
 unsigned short s[K]={0};
 /* 
 for(i=0;i<K;i++){
   GG.x[i][i+K]^=1;
 }
 */
 for(i=0;i<N;i++)
   ss[i]=tmp.x[0][i]^GG.x[1][i]^GG.x[2][i]^GG.x[3][i];
  for(i=0;i<3;i++)
    ss[i]^=1;

  for(i=0;i<N;i++)
    printf("%d,",ss[i]);
  printf("\n");
  //exit(1);
  
 for(i=0;i<K;i++){
   for(j=0;j<N;j++)
     s[i]^=gf[mlt(fg[ss[j]],fg[code.x[i][j]])];
 }
 
 printf("パリティチェック行列:code(matのコピーなので)\n");
 pMAT(code,K,N,0);
 
 //シンドローム
 printf("syn=");
 for(i=0;i<K;i++)
   printf("%d,",s[i]);
 printf("\n");
 //exit(1);
 
 
 return tmp;
}

//Q-matrix(置換行列を返す)
MAT matmul(){
  int i,j,k,tmp[N][N]={0};
unsigned short x0[N];//={1,2,3,4,5,6,7,0};
unsigned short x1[N];//={2,3,1,6,5,7,0,4};
unsigned short x2[N]={0};
unsigned short c[N][N]={0};

unsigned short a[N][N]={0};//{{0,3,0,0,},{0,0,4,0},{0,0,0,5},{6,0,0,0}};
//{{0,1,0,0},{0,0,1,0},{0,0,0,1},{1,0,0,0}};
unsigned short inv_a[N][N]={0};
  //{{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,0,1,0}};
//={{1,2,0,1},{1,1,2,0},{2,0,1,1},{1,2,1,1}}; //入力用の配列
 unsigned short cc[N][N]={0};
 MAT P={0};

  rp(x0);
  printf("置換配列を表示\n");
  for(i=0;i<N;i++){
    a[i][x0[i]]=1; //rand()%N;
    printf("%d,",x0[i]);
  }
  printf("\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      inv_a[i][j]=a[j][i];//gf[Inv(fg[a[j][i]])];//*inv_a[k][j];
      
    }
  }
  
  printf("Q1-置換行列を表示\n ={\n");
  #pragma omp parallel for
  for(i=0;i<N;i++){
    //printf("{");
    for(j=0;j<N;j++){
      // printf("%3d,",a[j][i]);
      P.x[j][i]=a[j][i];
    }
    //printf("},\n");
  }
  printf("};\n");

  printf("逆置換行列\n ={");
  #pragma omp parallel for
  for(i=0;i<N;i++){
    //printf("{");
    for(j=0;j<N;j++){
      //printf("%3d,",inv_a[j][i]);
	P.y[j][i]=inv_a[j][i];
    }
    //printf("},\n");
  }
  printf("謎\n");
#pragma omp parallel for
  for(i=0;i<N;i++){
    printf("粕");
#pragma omp parallel for
    for(j=0;j<N;j++){
      #pragma omp parallel for
      for(k=0;k<N;k++){
	tmp[i][j]^=gf[mlt(fg[a[i][k]],fg[inv_a[k][j]])];
      }
    }
  }
  printf("};\n");
  /*
#pragma omp parallel for
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%d,",tmp[j][i]);
      //printf("%d,",inv_a[i][j]);
    }
    printf("\n");
  }
  */

  
  return P;
}

/*
int main(){
  
    int i,j;
    double b[4],k=0;

    srand(clock());


    //g2();
 lab:
    printf("%d\n",gf[Inv(fg[3])]);
    printf("%d\n",gf[Inv(fg[4])]);
    printf("%d\n",gf[Inv(fg[5])]);
    printf("%d\n",gf[Inv(fg[6])]);
    matmul();
    matinv();
    printf("1=%d\n",gf[mlt(fg[3],fg[244])]);
    //if(det()!=1.0)
    //goto lab;
    
    return 0;
}
*/
