#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



#define COMPLEX 1

typedef enum {FALSE,TRUE} boolean;
#define odd(n) ((n) & 1)

#define N_LETTER 4

typedef long int cftype;
typedef unsigned short int expotype;
typedef struct node_ {
  expotype expo[N_LETTER];
  cftype real;
#if COMPLEX
  cftype imag;
#endif
  struct node_ *next;
} node;

int table[26];
node *avail;
node *value[26];
char letter[N_LETTER];
unsigned int cells;
unsigned int max_cells;
int ch;
cftype num;



void error(char *message)
{
printf("\n%s \n%u 個のセル使用\n",message,max_cells);
exit(0);
}

void readch(void)
{
boolean comment=FALSE;
do {
if((ch=getchar())==EOF) return;
putchar(ch);
if(ch=='%') comment=FALSE;
} while(comment || isspace(ch));

}

void readnum(void)
{
num = ch-'0';
while(readch(),isdigit(ch))
num=num*10+(ch-'0');
}

node *new_node(void)
{
node *p;

if(avail==NULL){
p=malloc(sizeof(node));
if(p==NULL) error("memoryless\n");
} else {
p=avail; avail= p->next;
}
if(++cells > max_cells) max_cells=cells;


return p;

}


void dispose_node(node *p)
{
  p->next=avail; avail=p; cells--;
}


void dispose(node *p)
{
node *q;

p=q; cells--;
while(q->next != NULL){
q=q->next; cells--;
}
q->next = avail; avail=p;
}


node *constant(cftype re 
#if COMPLEX
	       , cftype im 
#endif
	       )
{
int i;
node *p,*q;

p=new_node();
if(re != 0 
#if COMPLEX
 || im != 0 
#endif
)
  {
q=new_node();
q->real = re;
#if COMPLEX 
q->imag = im; 
#endif
for(i=0;i<N_LETTER;i++) q-> expo[i]=0;
p->next =q; q->next = NULL;
} else p->next = NULL;
return p;
}


node *copy(node *p)
{
int i;
node *q,*r;

q=r=new_node();
while((p=p->next) !=NULL){
r=r->next = new_node();
r->real = p->real;
#if COMPLEX
r->real = p->real;
#endif
for(i=0;i<N_LETTER;i++)
r->expo[i] = p->expo[i];
}
r->next = NULL;
return q;
}


void change_sign(node *p)
{
while((p= p->next) != NULL){
p->real = -(p->real);
#if COMPLEX
p->imag = -(p->imag);
#endif
}

}


void dff(node *p)
{
int j;
expotype e;
node *p1;


if(! isalpha(ch)) error("no char\n");
j=table[toupper(ch)-'A'];
if(j<0) error("can't bibun!");
p1=p; p=p->next;
while(p != NULL){
if((e= p->expo[j]) != 0){
p->expo[j] = e-1;
p->real *= e;
#if COMPLEX
p->imag *= e;
#endif
p1=p; p=p->next;
} else {
p=p->next; dispose_node(p1->next);
p1->next = p;
}
}
}

#if COMPLEX
void complex_conjugate(node *p)
{
while((p=p->next) != NULL)
p->imag = -(p->imag);
}
#endif


void add(node *p,node *q)
{
int i;
expotype ep,eq;
node *p1,*q1;

p1=p; p=p->next;
q1=q; q=q->next; dispose_node(q1);
while(q != NULL){
while(p != NULL){
for(i=0;i<N_LETTER;i++){
ep=p->expo[i]; eq=q->expo[i];
if(ep <= eq) break;
p1=p; p= p->next;
}
if(p==NULL || ep<eq){
p1->next = q; p1=q; q=q->next;
p1->next = p;
} else {
p->real += q->real;
#if COMPLEX
p->imag += q->imag;
#endif
if(p->real != 0 
#if COMPLEX
 || p->imag != 0 
#endif
 )
{
p1=p; p=p->next;
} else {
p=p->next;
dispose_node(p1->next);
p1->next = p;
}
q1=q; q=q->next; dispose_node(q1);
}
}
}
}



node *multi(node *x,node *y)
{
  int i;
  expotype ep,eq;
  node *p,*p1,*q,*r,*z;
  
  
  r=new_node(); r->next = NULL; q=NULL;
  while((y=y->next) != NULL){
    p1=r;p=p1->next; z=x;
    while((z=z->next)!= NULL){
	if(q==NULL) q=new_node();
#if COMPLEX
	q->real = y->real * z->real - y->imag * z->imag;
	q->imag = y->real * z->real + y->imag * z->real;
#else
	q->real = y->real * z->real;
#endif
	for(i=0;i<N_LETTER;i++)
	  q->expo[i]= y->expo[i] + z->expo[i];
	while(p !=NULL){
	  for(i=0;i<N_LETTER;i++){
	    ep=p->expo[i]; eq=q->expo[i];
	    if(ep != eq) break;
	  }
	  if(ep <= eq) break;
	  p1=p; p=p->next;
	}
	if(p==NULL || ep<eq){
	  p1->next = q; p1=q; p1->next=p;
	  q=NULL;
	} else {
	  p->real += q->real;
#if CMPLEX
	  p->imag += q->imag;
#endif
	  if(p->real != 0 
#if COMPLEX
	     || p->imag !=0 
#endif
	     )
	    {
	      p1=p; p= p->next;
	  } else {
	    p=p->next;
	    dispose_node(p1->next);
	    p1->next=p;
	  }
	}
      }
    }
    if(q !=NULL) dispose_node(q);
    return r;
}
  

node *power(node *x,expotype n)
{
node *p,*q;

if(n==1) return x;
if(n==0) {
#if COMPLEX
p=constant(1,0);
#else
p=constant(1);
#endif
} else {
p=multi(x,x); n -= 2;
if(n>0){
q=p;
if(odd(n)) p=multi(q,x);
else p=copy(q);
dispose(x); x=q; n /= 2;
if(odd(n)){
q=multi(p,x); dispose(p); p=q;
}
while((n/2) != 0){
q=multi(x,x); dispose(x); x=q;
if(odd(n)){
q=multi(p,x); dispose(p); p=q;
}
}
}
}
dispose(x);
return p;

}


void sincos(node *x)
{
int i;
node *p,*q,*p1,*q1,*r,*s,*t;


do{
i=0;
p1=x; p=p1->next;
q=r=new_node();
s=t=new_node();
while(p!= NULL){
if(p->expo[1] >= 2){
r=r->next = new_node();
r->real = -(p->real);
#if COMPLEX
r->imag = -(p->imag);
#endif
r->expo[0] = p->expo[0] + 2;
r->expo[1] = p->expo[1] -= 2;
for(i=2;i<N_LETTER;i++)
r->expo[i]=p->expo[i];

t=t->next = p;
p1->next = p = p->next;
} else {
p1=p; p=p->next;
}
}

if(i!=0){
r->next = t->next = NULL;
add(x,q); add(x,s);
} else {
dispose_node(q); dispose_node(s);
}
} while(i);
}


node *expression(void);

node *variable(void)
{
int i,j;
node *p;


i=toupper(ch)-'A'; j=table[i];
if(j>=0){
#if COMPLEX
p=constant(1,0);
#else
p=constant(1);
#endif
readch();
if(ch=='-'){
readch();
if(! isdigit(ch)) error("not num");
readnum();
} else num=1;
(p->next)->expo[j] = (expotype) num;
} else {
if(value[i]==NULL) error("undefined");
p=copy(value[i]);
readch();
}

return p;
}


node *factor(void)
{
node *p;

if(ch == '('){
readch(); p=expression();
if(ch !=')') error("')' is lacked");
readch();
} else if(isdigit(ch)){
readnum();
#if COMPLEX
if(toupper(ch) != 'I') p=constant(num,0);
else {
readch(); p=constant(0,num);
}
#else
p=constant(num);
#endif
} else if (isalpha(ch)) p=variable();
else error("unary input");
for(;;){
switch(ch){
 case '^':
readch();
if(! isdigit(ch)) error("no num");
readnum(); p=power(p,(expotype)num);
break;
 case ':':
readch(); dff(p); readch();
break;
 case '!':
readch(); sincos(p);
break;
#if COMPLEX
 case '\'':
readch(); complex_conjugate(p);
break;
#endif
 default:
return p;
}
}
}


node *term(void)
{
node *p,*q,*r;


p=factor();
while(ch=='*'){
readch(); q=p; r=factor();
dispose(q); dispose(r);
}
return p;
}


node *expression(void)
{
node *p,*q;

if(ch == '-'){
readch(); p=term(); change_sign(p);
} else {
if(ch=='+') readch();
p=term();
}
for(;;){
switch(ch){
 case '+':
readch(); q=term(); break;
 case '-':
readch(); q=term(); change_sign(q); break;
 default:
return p;
}
add(p,q);
}
}


void init(void)
{
int i;

avail=NULL; cells=max_cells=0;
for(i=0;i<26;i++){
table[i]= -1; value[i] = NULL;
}
}


void declare(void)
{
int i,j;


for(i=0;i<26;i++){
table[i]= -1;
if(value[i] != NULL){
dispose(value[i]); value[i]=NULL;
}
}
j=0; readch();
while(isalpha(ch)){
i=toupper(ch)-'A';
if(table[i]<0){
if(j >= N_LETTER) error("too many char\n");
table[i]=j; letter[j]=ch; j++;
}
readch();
}
}


void assign(void)
{
int i;
node *p;

i=toupper(ch)-'A';
if(table[i]>=0) error("wrong left");
readch();
if(ch!='=') error("no '='");
readch(); p=expression();
if(value[i] !=NULL) dispose(value[i]);
value[i]=i;
}


#if COMPLEX
void print(void)
{
  int i;
  boolean first,one;
  node *p,*q;
  cftype re,im;
  expotype e;
  
  
  first=TRUE; readch(); p=q=expression();
  printf("\n");
  while((p=p->next) != NULL) {
    one=FALSE;
    re=p->real; im =p->imag;
    if(im==0){
	if(re>=0){
	  if(! first) printf(" + ");
	} else {
	  printf(" - "); im = -im;
	}
	printf("%ld",(long int)im);
      } else {
	if(! first) printf(" + ");
	printf("(%ld%+ldi)",(long int)re,(long int)im);
      }
      first=FALSE;
      for(i=0;i<N_LETTER;i++)
	if((e=p->expo[i]) != 0){
	  if(! one) printf("%c",letter[i]);
	  if(e != 1)
	    printf("^%lu",(unsigned long)e);
	}
      if(one) printf("1");
    }
    if(first) printf("0");
    printf("\n");
    dispose(q);
}
  
#else
  
void print(void)
{
  int i;
  boolean first;
  node *p,*q;
  cftype c;
  expotype e;
  
  
  first=TRUE; readch(); p=q=expression();
  printf("\n");
  while((p=p->next) != NULL){
    if((c=p->real) >= 0){
      if (! first) printf(" + ");
    } else {
      printf(" - "); c = -c;
    }
    first=FALSE;
    if(c != 1) printf("%ld",(long int)c);
    for(i=0;i<N_LETTER;i++)
      if((e=p->expo[i]) != 0){
	if(c != 1) printf(" * ");
	c=0;
	printf("^%lu",(unsigned long int)e);
      }
    if(c==1) printf("1");
  }
  if(first) printf("0");
  printf("\n");
  dispose(q);
}

#endif
     

int main(){
printf("pol - calc\n");
init();
while(readch(),ch != EOF){
if(ch == '@') declare();
else if (ch == '?') print();
else if (isalpha(ch)) assign();
else error("illegal statement");
if(ch != ';') error("';' lacked ");
printf("\n%u cells used (%u using)\n");
max_cells=cells;
}
return -1;
}

