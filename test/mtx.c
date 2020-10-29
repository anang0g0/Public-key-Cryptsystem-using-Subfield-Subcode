#include <stdio.h>
#include <assert.h>

#define N 16
#define K 8
#include "global.h"
#include "chash.c"
#include "inv_mat.c"
#include "zech.c"

typedef struct {
  unsigned short x[N][N];
  int row;
  int col;
} MTX;

MTX mtx_new(int row, int col){
  MTX ret = {0};
  ret.row = row;
  ret.col = col;
  return ret;
}

MTX mtx_copy(unsigned short *mem, int row, int col){
  MTX ret = {0};
  ret.row = row;
  ret.col = col;
  for(int r=0; r<row; r++){
    //memcpy(ret.x + r*N, mem + r*col);
    for(int c=0; c<col; c++){
      ret.x[r][c] = mem[r*col + c];
    }
  }
  return ret;
}

// 単位行列
MTX mtx_id(int n){
  MTX ret = {0};
  ret.row = n;
  ret.col = n;
  for(int i=0; i<n; i++) ret.x[i][i]=1;
  return ret;
}

void mtx_print(char* str, MTX m){
  int r,c;
  puts("-------");
  puts(str);
  for(r=0; r<m.row; r++){
    for(c=0; c<m.col; c++){
	    printf("%2d,",m.x[r][c]);
    }
	  printf("\n");
  }
  puts("-------");
  fflush(stdout);
}

// ret = a*b
MTX mtx_f2mul(MTX a, MTX b){
  assert(a.row==b.col);
  assert(a.col==b.row);
  MTX ret = mtx_new(a.row, b.col);
  for(int r=0; r<a.row; r++){
    for(int c=0; c<b.col; c++){
      for(int i=0; i<a.col; i++)
	      ret.x[r][c] ^= a.x[r][i]&b.x[i][c];
    }
  }
  return ret;
}

// ret = T(a)
MTX mtx_t(MTX a){
  MTX ret = mtx_new(a.col, a.row);
  for(int r=0; r<a.row; r++){
    for(int c=0; c<a.col; c++){
      ret.x[c][r] = a.x[r][c];
    }
  }
  return ret;
}

//掃き出し法
MTX mtx_inv(MTX a_){
  assert(a_.row == a_.col);
  int n = a_.row;
  MTX a = a_; // a_を改変しないためにコピー
  MTX inv_a = mtx_id(n);

  unsigned short buf; //一時データ
  for(int i=0; i<n; i++){
    buf=gf[Inv(fg[a.x[i][i]])];
    for(int j=0; j<n; j++){
      a.x[i][j]=gf[mlt(fg[buf],fg[a.x[i][j]])];
      inv_a.x[i][j]=gf[mlt(fg[buf],fg[inv_a.x[i][j]])];
    }
    for(int j=0; j<n; j++){
      if(i!=j){
        buf=a.x[j][i];
        for(int k=0; k<n; k++){
          a.x[j][k]^=gf[mlt(fg[a.x[i][k]],fg[buf])];
          inv_a.x[j][k]^=gf[mlt(fg[inv_a.x[i][k]],fg[buf])];
        }
      }
    }
  }
  return inv_a;
}
void mtx_test(){
  unsigned short a0[2][3]={
    {1,1,0},
    {0,1,1}
  };
  MTX a = mtx_copy(a0, 2, 3);
  mtx_print("a=", a);

  MTX ta = mtx_t(a);
  mtx_print("ta=", ta);
  
  MTX mul = mtx_f2mul(a, ta);
  mtx_print("a * ta=", mul); 

  MTX mul2 = mtx_f2mul(a, mtx_t(a));
  mtx_print("a * ta=", mul2); 
}

void mtx_test2(){
  unsigned short a0[3][3]={
    {1,1,0},
    {1,0,1},
    {1,1,1},
  };
  MTX a = mtx_copy(a0, 3, 3);
  mtx_print("a=", a);

  MTX inv_a = mtx_inv(a);
  mtx_print("inv_a=", inv_a);

  MTX bb={0};
  bb=mtx_f2mul(a,inv_a);
  mtx_print("E=",bb);
}
int main(void){
  mtx_test2();
}
