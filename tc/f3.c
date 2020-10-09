#include <stdio.h>

#define N 64
/* GF(N)ã‚Å ‹Èüxy^3+x^3+1=0 <=> x^3*z+xy^3+z^4=0 ã‚Ì—L—“_‚ğŒvZ‚·‚éB*/


/* static int gf[4] = {0, 1, 2, 3}; */

/* static int gf[32] = 
  {0, 1, 2, 4, 8, 16, 5, 10, 20, 13, 26, 17, 7, 14, 28, 29, 31, 27, 19, 3, 6, 
   12, 24, 21, 15, 30, 25, 23, 11, 22, 9, 18};
*/

gf[N] = 
  {0, 1, 2, 4, 8, 16, 32, 3, 6, 12, 24, 48, 35, 5, 10, 20, 40, 19, 38, 15, 
   30, 60, 59, 53, 41, 17, 34, 7, 14, 28, 56, 51, 37, 9, 18, 36, 11, 22, 44, 
   27, 54, 47, 29, 58, 55, 45, 25, 50, 39, 13, 26, 52, 43, 21, 42, 23, 46, 
   31, 62, 63, 61, 57, 49, 33};


int bin(),gb[21][113],count;

main(){
int x,y,z;

count=0;
x=0;y=1;z=0;
bin(x,y,z);


z=0;x=1;
for(y=0;y<N;y++)
bin(x,y,z);


z=1;
for(x=0;x<N;x++)
{
  for(y=0;y<N;y++)
	bin(x,y,z);
}

for(x=0;x<21;x++){
for(y=0;y<113;y++)
printf("%d,",gf[gb[x][y]]);
printf("\n");
}

}



bin(int x,int y,int z)
{
int i,j,k,f1,f2,f3,f4,f5,add(),mlt(),div(),c,h;


	 f1=gf[mltn(4,z)];
	 f2=gf[mlt(mltn(3,y),x)];
	 f3=gf[mlt(mltn(3,x),z)];

if((f1^f2^f3)==0){
printf("%d %d %d\n",x,y,z);
base(x,y);
}

}



void base(int x,int y)
{
int i,j;


gb[0][count]=1;
gb[1][count]=x;
gb[2][count]=y;
gb[3][count]=mlt(x,x);
gb[4][count]=mlt(x,y);
gb[5][count]=mlt(y,y);
gb[6][count]=mlt(gb[3][count],x);
gb[7][count]=mlt(gb[3][count],y);
gb[8][count]=mlt(gb[5][count],x);
gb[9][count]=mlt(gb[5][count],y);
gb[10][count]=mlt(gb[3][count],gb[3][count]);
gb[11][count]=mlt(gb[6][count],y);
gb[12][count]=mlt(gb[3][count],gb[5][count]);
gb[13][count]=mlt(gb[5][count],gb[5][count]);
gb[14][count]=mlt(gb[3][count],gb[6][count]);
gb[15][count]=mlt(gb[10][count],i);
gb[16][count]=mlt(gb[6][count],gb[3][count]);
gb[17][count]=mlt(gb[6][count],gb[6][count]);
gb[18][count]=mlt(gb[14][count],y);
gb[19][count]=mlt(gb[10][count],gb[5][count]);
gb[20][count]=mlt(gb[9][count],gb[9][count]);
count++;

/*
gb[21][count]=
gb[22][count]=
gb[23][count]=
gb[24][count]=
gb[25][count]=
gb[26][count]=
gb[27][count]=
gb[28][count]=
gb[29][count]=
gb[30][count]=
gb[31][count]=
*/
}



int add(int x,int y)
{
    int z;
    /* Zech‘Î”•\ */
    static int Zech[16] = {1,0,5,9,15,2,11,14,10,3,8,6,13,12,7,4};

    if(x==0){
        return(y);
    }
    else if(y==0){
        return(x);
    }
    else if(x > y){
        z=(Zech[x-y+1]-1)+(y-1);
        z=(z%15)+1;
    }
    else if(x < y){
        z=(Zech[y-x+1]-1)+x-1;
        z=(z%15)+1;
    }
    else{
        z=0;
    }
    return(z);
}

/* GF(16)ã‚Å‚ÌæZ */
int mlt(int x,int y)
{
    if(x==0||y==0){
        return(0);
    }
    return ((x+y-2)%(N-1))+1;
}

/* GF(16)ã‚Å‚ÌœZ */
int div(int x,int y)
{
    if(y==0){
        printf("***ˆÙí”­¶I ‚O‚ÅœZ***\n");
        exit(1);
    }
    else if(x==0){
        return 0;
    }
    return ((x-y+15)%15)+1;
  }


int mltn(int n,int x)
{
int i,j;

i=x;
for(j=1;j<n;j++)
i=mlt(i,x);

return i;

}

