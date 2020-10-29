

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
