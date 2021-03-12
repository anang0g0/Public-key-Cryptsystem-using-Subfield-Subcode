#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "global-p.h"
#include "struct.h"
#include "chash-p.c"
#include "debug.c"

#define O 6859 //1331 //2197,4913,6859
#define K 3
#define P 19

//sagemath上での原始多項式
unsigned short pp[4][4]= {{0,0,9,2}, {0,0,11,2}, {0,0,16,3}, {0,0,15,2}};
 // {0,0,9,2}, {1,0,11,2}, {1,0,16,3}, {1,0,15,2};
 //GF(11^3,13^3,17^3,19^3)
unsigned short ff[2][7]={{1,0,0,0,0,2,0,2},{0,0,1,0,0,0,1,2}}; //GF(3^7,5^5)

unsigned int gf[O]={0},fg[O]={0};
//int N =0,M=0;
unsigned short c[K+1]={0};

//OP型からベクトル型への変換
vec
o2v (OP f)
{
  vec a = { 0 };
  int i;

  //#pragma omp parallel for
  for (i = 0; i < DEG; i++)
    {
      if (f.t[i].a > 0 && f.t[i].n < DEG)
	      a.x[f.t[i].n] = f.t[i].a;
    }


  return a;
}


//ベクトル型からOP型への変換
OP
v2o (vec a)
{
  int i, j = 0;
  OP f = { 0 };

  //#pragma omp parallel for
  for (i = 0; i < DEG; i++)
    {
      if (a.x[i] > 0)
	{
	  f.t[j].n = i;
	  f.t[j++].a = a.x[i];
	}
    }


  return f;
}

void
op_print_raw (const OP f)
{
  puts ("op_print_raw:");
  for (int i = 0; i < DEG; i++)
    {
      if (f.t[i].a > 0)
	printf ("[%d] %ux^%u\n", i, f.t[i].a, f.t[i].n);
    }
}

bool
op_verify (const OP f)
{
  bool end = false;
  unsigned short n_max = 0;
  for (int i = 0; i < DEG; i++)
    {
      if (end && (f.t[i].n != 0 || f.t[i].a != 0))
	{
	  op_print_raw (f);
	  printf ("found data after end: i=%d\n", i);
	  print_trace ();
	  fflush (stdout);
	  return false;
	}
      if (f.t[i].a == 0)
	{
	  end = true;
	  continue;
	}
      if (f.t[i].n + 1 <= n_max)
	{
	  op_print_raw (f);
	  printf ("found invalid order: i=%d\n", i);
	  print_trace ();
	  fflush (stdout);
	  return false;
	}
      n_max = f.t[i].n + 1;
    }
  return true;
}


//多項式の次数(default)
int
deg (vec a)
{
  int i, n = 0;

  //#pragma omp parallel for
  for (i = 0; i < DEG; i++)
    {
      if (a.x[i] > 0)
	n = i;
    }


  return n;
}


//配列からベクトル表現の多項式へ変換する
vec
Setvec (int n)
{
  int i;
  vec v = { 0 };


  for (i = 0; i < n; i++)
    {
      v.x[n - 1 - i] = c[i];
    }


  return v;
}



//配列の値を係数として多項式に設定する
OP
setpol (unsigned short f[], int n)
{
  OP g;
  vec a;
  int i;
  
  memset (c, 0, sizeof (c));
  //memcpy (c, f, n);
  for(i=0;i<n;i++)
    c[i]=f[i];
//exit(1);  
  a = Setvec (n);

  g = v2o (a);


  return g;
}


//多項式を表示する(default)
void
printpol (vec a)
{
  int i, n;

  n = deg (a);

  //printf ("baka\n");
  assert (("baka\n", n >= 0));



  for (i = n; i > -1; i--)
    {
      if (a.x[i] > 0)
	{
	  printf ("%u", a.x[i]);
	  //if (i > 0)
	  printf ("x^%d", i);
	  //if (i > 0)
	  printf ("+");
	}
    }
  //  printf("\n");

  return;
}

//多項式の代入値
unsigned short
xtrace (OP f, unsigned short x)
{
  int i, d;
  unsigned short u = 0,v=1;
  

  d = deg (o2v (f));
//printpol(o2v(f));
//printf(" =ff\n");

  for (i = 0; i < d + 1; i++)
    {
      v=0;
      if(f.t[i].a>0){
        v=1;
        for(int j=0;j<f.t[i].n;j++){
          v=(v*x);
        }
          v=(v*f.t[i].a)%O;
        
      //printf("\nv=%d",v);
    }
    u=(u+v);
    }
  //printf("u=%d\n",u%O);

  return u%O;
}


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




//多項式の次数(degのOP型)
int
odeg (OP f)
{
  int i, j = 0, k;


  //k=terms(f);
  for (i = 0; i < 512; i++)
    {
      if (j < f.t[i].n && f.t[i].a > 0)
	j = f.t[i].n;
    }

  return j;
}



//20200816:正規化したいところだがうまく行かない
//多項式の足し算
OP
oadd (OP f, OP g)
{
  vec a = { 0 }
  , b =
  {
  0}
  , c =
  {
  0};
  int i, j, k, l = 0;
  OP h = { 0 },f2={0},g2={0};

  //for(i=0;i<257;i++)
  // printf("%d %d %d %d %d\n",i,f.t[i].a,f.t[i].n,g.t[i].a,g.t[i].n);

   //  exit(1);
  //f=conv(f);
  //g=conv(g);

  a = o2v (f);
  //exit(1);
  b = o2v (g);

  j=odeg(f);
  l=odeg(g);
  //  oprintpol((g));
  //  exit(1);
  if (j >= l)
    {
      k = j + 1;
    }
  else
    {

      k = l + 1;

    }
  //for(i=0;i<k;i++)
  //printf("%d %d\n",i,b.x[i]);
  //  exit(1);
  
  for (i = 0; i < k; i++)
    {
      //if(f.t[i].a>0 || g.t[i].a>0)
      //h.t[i].a=f.t[i].a^g.t[i].a;
      c.x[i] = (a.x[i] + b.x[i])%P;
    }
  // 
  h = v2o (c);

  return h;
}



//多項式を項ずつ掛ける
OP
oterml (OP f, oterm t)
{

  //assert (op_verify (f));
  int i, k,j;
  OP h = { 0 };
  vec test;
  unsigned short n;

  //f=conv(f);
  k = odeg (f);
  j=0;
  for (i = 0; i < k + 1; i++)
    {
      h.t[i].n = f.t[i].n + t.n;
      h.t[i].a = (f.t[i].a * t.a)%P;
    }
  
  //h=conv(h);
  //assert (op_verify (h));
  return h;
}


//多項式の掛け算
OP
omul (OP f, OP g)
{
  //f=conv(f);
  //g=conv(g);

  //assert (op_verify (f));
  //assert (op_verify (g));
  int i, count = 0, k,l,m;
  oterm t = { 0 };
  OP h = { 0 }, e = {
    0
  }, r = {
    0
  };
  vec c = { 0 };


  l=deg(o2v(f));
  m=deg(o2v(g));
  
  if (l >= m)
    {
      k = l;
    }
  else
    {
      k = m;
    }
//printf("l=%d",l);
//printf("m=%d",m);
//printpol(o2v(f));
//printf(" =f\n");
//printpol(o2v(g));
//printf(" =g\n");
//exit(1);

  for (i = 0; i < k + 1; i++)
    {
      t = g.t[i];
      if(t.a>0){
      e = oterml (f, t);
      h = oadd (h, e);
      }
    }
    //printpol(o2v(f));
    //printf(" =f\n");
    //printpol(o2v(g));
    //printf(" =g\n");
    //exit(1);
  //assert (op_verify (h));
  return h;
}


/*
//多項式の掛け算
OP
omul (OP f, OP g)
{
  f = conv (f);
  g = conv (g);
  assert (op_verify (f));
  assert (op_verify (g));
  int i, count = 0, k;
  oterm t = { 0 };
  OP h = { 0 }, e = {
    0
  }, r = {
    0
  };
  vec c = { 0 };
  if (odeg ((f)) > odeg ((g)))
    {
      k = odeg ((f));
    }
  else
    {
      k = odeg ((g));
    }
  for (i = 0; i < k + 1; i++)
    {
      t = g.t[i];
      e = oterml (f, t);
      h = oadd (h, e);
    }
  assert (op_verify (h));
  return h;
}
*/


//リーディグタームを抽出(default)
oterm
LT (OP f)
{
  int i, k;
  oterm t = { 0 };


  k = deg (o2v (f));
  for (i = 0; i < DEG; i++)
    {
      //printf("a=%d %d\n",f.t[i].a,f.t[i].n);
      if (f.t[i].a > 0)
	{
	  t.n = f.t[i].n;
	  t.a = f.t[i].a;
	}
    }

  return t;
}

OP osub(OP f,OP g){
vec a={0},b={0},d={0};
int i,k,l,m;
OP ans={0};

  a=o2v(f);
  b=o2v(g);
  l=deg(a);
  m=deg(b);
  if(l>=m){
    k=l;
  } else{
    k=m;
  }
  for(i=0;i<k+1;i++){
  d.x[i]=(a.x[i]-b.x[i])%P;
  //if(d.x[i]<0)
    //d.x[i]+=P;
  }
  ans=v2o(d);

return ans;
}

OP confer(OP f,int a){
  vec r;
  int n,i;
  OP g;

  r=o2v(f);
  n=deg(r);
  for(i=0;i<n+1;i++)
    r.x[i]=(r.x[i]*a)%P;
  g=v2o(r);

return g;
}


void mkmf(){
  int i,j,k,count=0;
  OP f={0},g={0},h={0},w={0},s={0},u={0};
  vec b={0},a={0},d={0},t={0},v={0};
  oterm o;
  unsigned short ccp[4]={0};

  if(O==1331)
  for(i=0;i<K+1;i++)
  ccp[i]=pp[0][i];
  if(O==2197)
  for(i=0;i<K+1;i++)
  ccp[i]=pp[1][i];
  if(O==4913)
  for(i=0;i<K+1;i++)
  ccp[i]=pp[2][i];
  if(O==6859)
  for(i=0;i<K+1;i++)
  ccp[i]=pp[3][i];

g=setpol(ccp,4);
//b.x[0]=2;
//b.x[1]=9;
a.x[1]=1;
v.x[3]=1;
u=v2o(v);
//d.x[3]=1;
//printpol(o2v(g));
//printf(" =g\n");
//exit(1);

//g=v2o(b);
//s=v2o(a);
s.t[1].a=1;
s.t[1].n=1;
//gf[12]=P;
//gf[13]=P*P;

w=g;
//printpol(o2v(w));
//printf(" =w\n");
//printpol(o2v(g));
//printf(" =g\n");
//printpol(o2v(s));
//printf(" =s\n");

//printf("\n");
for(i=0;i<P;i++)
gf[i]=i;
gf[P]=xtrace(g,P);
//printf("\naa=%d\n",gf[P]);
//exit(1);
//w=omul(w,s);
//gf[12]=1111;
count=P+1;
while(1){
g=omul(g,s);
//printpol(o2v(g));
//printf(" =g\n\n");
//exit(1);

o=LT(g);
memset(d.x,0,sizeof(d));
if(o.n==K){
  d.x[o.n]=o.a;
  h=v2o(d);
  g=osub(g,h);
  f=confer(w,o.a);
  g=oadd(g,f);
  //w=omod(w,u);
  //printpol(o2v(f));
  //printf("\n");
}
if(LT(g).n==0 && LT(g).a==1)
break;


gf[count]=xtrace(g,P);
//printf("count=%d %d ",count,gf[count]);
//printpol(o2v(g));
//printf(" =gg\n\n");
count++;
//exit(1);
}

//exit(1);

//printpol(o2v(f));
//printf(" =f\n");
//printf("gf[%d]={\n",O);
printf("unsigned short gf[%d]={",O);
for(i=0;i<O;i++)
printf("%d,",gf[i]);
printf("};");
printf("\n");

}


int main(){

mkmf();
//exit(1);

  makefg(O);


return 0;
}

