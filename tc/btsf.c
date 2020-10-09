#include <stdio.h>



int chk_prm(int, char **);
void usage(void);
void sr(int);
void sl(int);

FILE *fpi,*fpo;
int dirc,sn;

void main(int ac,char **av)
{
	if(chk_prm(ac,av)!=0){
		return;
	}

	switch(dirc){
	case 'R':
	case 'r':
		sr(sn);
		break;
	case 'L':
	case 'l':
		sl(sn);
		break;
	default:
		usage();
		break;
	}
	fcloseall();
}

int chk_prm(int ac,char **av)
{
	if(ac<3){
		usage();
		return(-1);
	}



	dirc=av[1][0];
	sn=av[1][1];
	if(sn==0){
		sn=1;
	}
	else{
		sn=sn-'0';
		if(sn<=0||sn>=8){
			usage();
			return(-1);
		}
	}


	if((fpi=fopen(av[2],"rb"))==0){
		printf("input file '%s'open error\n",av[2]);
		return(-1);
	}


	if(ac>=4){
		if((fpo=fopen(av[3],"wb"))==0){
			printf("output file '%s'open error\n",av[3]);
			return(-1);
		}
	}
	else{
		fpo=stdout;
	}
printf("%s %s\n",av[2],av[3]);
	return(0);
}

void usage(void)
{
	printf("usage:\n");
	printf("btsf {r|l}[1-7] input [output]\n");
	printf("output n-bit shift data r or l\n");
	printf("if output is null then stdout\n");
}

void sr(int n)
{
	int c;
	int x,sv;
	int msk,nn;

	nn=8-n;
	msk=(511>>nn);

	if((c=fgetc(fpi))==EOF){
		return;
	}
	x=c & msk;
	c=c>>n;
	sv=x<<nn;
	if(c!=0){
		fputc(c,fpo);
	}

	for(;;){
		if((c=fgetc(fpi))==EOF){
			break;
		}
		x=c & msk;
		c=(c>>n)|sv;
		sv=x<<nn;
		fputc(c,fpo);
	}
	if(sv!=0){
		fputc(sv,fpo);
	}
}

void sl(int n)
{
	int c1,c2;
	int x,sv;
	int msk,nn;

	nn=8-n;
	msk=(511>>n);

printf("%d\n",n);

	if((c1=fgetc(fpi))==EOF){
		return;
	}
	x=c1 & msk;
	c1=c1>>nn;
	sv=x<<n;
	if(c1 !=0){
		fputc(c1,fpo);
	}

	for(;;){
		if((c2=fgetc(fpi))==EOF){
			break;
		}
		x=c2 & msk;
		c1=sv|(c2>>nn);
		sv=x<<n;
		fputc(c1,fpo);
	}
	if(sv!=0){
		fputc(sv,fpo);
	}

printf("sv=%d\n",sv);

}

