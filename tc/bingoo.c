
かつてのループ部分
/*
     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[0]==(h[i]^m[j]))
	     printf("(%d %d) %u =? %u %d\n",i,j,h[i]^m[j],c[0],k);
	 }
       }
     }

     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[1]==(h[i]^m[j]))
	     printf("(%d %d) %u=?%u %d\n",i,j,h[i]^m[j],c[1],k);
	 }
       }
     }

     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[2]==(h[i]^m[j]))
	     printf("(%d %d) %u=?%u %d\n",i,j,h[i]^m[j],c[2],k);
	 }
       }
     }

     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[3]==(h[i]^m[j]))
	     printf("(%d %d) %u=?%u %d\n",i,j,h[i]^m[j],c[3],k);
	 }
       }
     }

     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[4]==(h[i]^m[j]))
	     printf("(%d %d) %u=?%u %d\n",i,j,h[i]^m[j],c[4],k);
	 }
       }
     }

     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[5]==(h[i]^m[j]))
	     printf("(%d %d) %u=?%u %d\n",i,j,h[i]^m[j],c[5],k);
	 }
       }
     }

     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[6]==(h[i]^m[j]))
	     printf("(%d %d) %u=?%u %d\n",i,j,h[i]^m[j],c[6],k);
	 }
       }
     }

     for(k=0;k<8;k++){ 
       for(i=0;i<N;i++)
	 h[i]=mm[k][i];
       for(j=0;j<N;j++){
	 for(i=0;i<N;i++){
	   if(c[7]==(h[i]^m[j]))
	     printf("(%d %d) %u=?%u %d\n",i,j,h[i]^m[j],c[7],k);
	 }
       }
     }
*/



/* 多倍長かけ算のつもり
int mm(int a[][],int b[][])
{
  int i,j,k,c[][]
    
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
	for(k=0;k<N;k++)
	  c[i][j]+=a[i][k]*b[k][j];
      }
    }
  
}
*/


/*
mgr() の残り

  for(i=0;i<4;i++){
    for(j=0;j<8;j++){
      for(k=0;k<8;k++)
	cout << itob(e[i][j]^e[i][k],t);
      cout << "\n";
    }
    cout << "\n";
  }
*/
/* the key */
// 001010
// 100100
// 111001
// 101110

// 100111
// 101010
// 000001
// 001101


/* show key 
  for(i=0;i<8;i++){
    e[0][i]=Z[i]^strtol("101101",(char *)NULL,2);
    e[1][i]=z2[i]^strtol("001110",(char *)NULL,2);
    e[2][i]=z3[i]^strtol("111000",(char *)NULL,2);
    e[3][i]=z4[i]^strtol("100011",(char *)NULL,2);
  }
  cout << (e[0][0]^e[1][0]);
  cout << (e[0][0]^e[2][0]);
  cout << (e[0][0]^e[3][0]);
*/
