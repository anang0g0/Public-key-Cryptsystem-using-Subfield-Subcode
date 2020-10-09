/* q-array Goppa code useing for crypt analysis */
/* it found out g(z)=z^3+z+1 and g(z)=z^6+z^2+1 over GF(16) */


/* message treat as 4-bit blok isas element of GF(16) */
static short G1[3][16]={
{8, 8, 5, 8,5,3,10,7,10, 9,11,10, 5,1,0,0},
{1,11,10, 5,3,9,15,7, 1,14, 9,14, 4,0,1,0},
{2, 4, 3,11,2,6, 9,7,11, 2,13,12,11,0,0,1}
};
static short G2[6][16]={
{ 8,14, 7,5, 3,11,11, 4, 9,13,1,0,0,0,0,0},
{ 6,14,13,1, 9,14, 6, 9, 6, 3,0,1,0,0,0,0},
{14,13,13,2,13, 2, 8, 4, 3,14,0,0,1,0,0,0},
{12,13, 2,4, 6,11,13, 1,14, 8,0,0,0,1,0,0},
{ 3,12, 8,5, 4, 6,14, 2,12,14,0,0,0,0,1,0},
{11, 8, 3,3, 6,12, 6,14,13,14,0,0,0,0,0,1}
};

static char kl[8][16]={
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,11,10, 8,15, 3, 5,11,10,11,10, 4, 9,14, 2},
{0,0, 1, 1, 2, 4, 9,14,13, 7,12, 6, 7,12, 6,13},
{0,0,10,11,15, 3, 5, 8,10,11,10,11, 9,14, 2, 4},
{0,1,10,11,12, 6,13, 7, 4, 9,14, 2, 3, 5, 8,15},
{0,0,11,10, 9,14, 2, 4, 2, 4, 9,14, 5, 8,15, 3},
{0,0, 1, 1, 5, 8,15, 3, 1, 1, 1, 1,15, 3, 5, 8},
{0,0, 1, 1, 4, 9,14, 2, 7,12, 6,13,12, 6,13, 7}
};

/* getc() to 1byte message treat as element of GF(256) */
static int E[168][288]={};


/*
Comment of atomic test
"the atmic test" is burst error collecting test use q-array error
 collecting codes. the coded plaintext m is consist of k partitions.
For arbitary number 1 < i < k, m_i is ground zero.

(OPEN PROBLEM)
$B2.7&$HJFED$O$I$C$A$,0N$$?M!)(B

$B$b$&2.7&$J$s$FNr;KD9$$$7$H$C$/$K>C$($F$$$k?M4V$b$$$kCf$G:#$@$K(B
$BO":\$,@Z$l$J$$$J$s$F?.$8$i$l$J$$!<!*8D?ME*$K$O%$%s%?!<%U%'!<%9$K(B
$B$N$C$F$k?M$,9%$_$@$J$"$C$F2?$+5;=QE*$JOCBj$KJP$j$,$A$J5;=Q4XO"$N(B
$B%3%i%`$KJ87OE*$J65M\$r$&$^$/;}$A9~$s$G$$$k$C$F46$8!*(BLI$B$s(BUX$B$N5-;v(B
$B$C$F=i?4<T$r%?%307$$$9$k?M4V$K$OI>H=$$$$$1$I$"$"$$$&=q$+$lJ}$C$F(B
$B$$$&$N$b2?G/$bA0$+$iJQ$o$i$J$/$F$=$l$r=q$/B&$,3Z$7$s$G$$$k8B$j(B
$BB>$N8@MU$J$s$F=q$+$J$$$N$@$m$&!*AjJQ$o$i$:8*?H:\$;$^$$;W$$$r$9$k(B
$B$O$a$K$J$k$H8@$&$+=i?4<T$rM}2r$7$J$$%?%3$J3+H/$N=j0Y$G;H$&?M4V$,(B
$B6lO+$7$J$1$l$P$J$i$J$$$N$@!*3'2?$+$r;H$&;v$GJXMx$5$rDI5a$7$?$$$H(B
$B;W$&$h$&$K$J$k!*=j$,JQ$J3+H/$O1}!9$K=i?4<T$r=i?4<T$N$^$^$K$7$F$*(B
$B$/;v$r9%$`798~$K$"$k!*$=$7$F$=$&$$$&5-;v$O2<$i$J$$$b$N$H$7$F8<?M(B
$B$K$O7I1s$5$l$k!*$^$"%A%g!<=i?4@lLg%7$_$?$$$K%R%M%b%9%$%s%9%H!<%k(B
$BFC=8$7$F$k=j$b$"$k0L$@$+$i!*$b$7M>M5$,$"$C$?$i(BALPHA$B$h$j(BK6/2-400$B$+(B
$B$J!<$H$+;W$&!*(BODP$B$b$d$C$H=P$?$1$I9b$$$7!*A}$d$9M}M3$OJ,;6=hM}$K$"(B
$B$k!*F0$+$9$@$1!*$@$+$i%O%3$b$$$i$J$$$7%`%-%@%7$N4pHW$_$?$$$J$N$G$b(B
$BF0$1$P$$$$!*$=$l$K$7$F$bA0$N;E;v$O5"$k;~M+]5$@$C$?$1$I:#2s$N$O:#F|(B
$B$b=*$o$C$?!<!*$H$$$&2rJ|46$,$"$C$FHs>o$K$h$$!*%W%m%0%i%^!<$J$s$F(B
$BFCJL%+%C%3$$$$;E;v$G$b$J$+$C$?!*$G$b<qL#$OFq$7$$J}$,3Z$7$$!*<qL#(B
$B$5$($"$l$P;E;v$J$s$F4v$iB`6~$G$b2?$H$+$J$k$N$@!*%7%9%F%`$N2~B$$K$O(B
$B$^$@;~4V$,$+$+$k$7!"5u?t>hK!2?$+$3$l$+$i3P$($k$N$,3Z$7$_$@!*Mp?t(B
$B@8@.$b<+A0$G:n$C$?J}$,$$$$$N$@$m$&$+!)(B


*/


main(){
int i,j;

/* 1 message divide to 4-bit block and characters */
for(i=0;i<6;i++){
  for(j=0;j<16;j++)
    printf("%d ",G2[i][j]);
  printf("\n");
}



}

