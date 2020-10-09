#include <stdio.h>


main(){
  int i,j,t,d,a;


  for(t=0;t> -200;t--){
    for(d=0;d<1000000;d++){
      if((d*5+10836*t)==1)
	printf("%d,%d\n",d,t);
    }
  }  
}


