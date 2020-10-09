#define NULL 0


main(){
int x;
struct node{
int num; struct node *next;
} *start, *p;
char *malloc(),*q;
start=NULL;
printf("integer input next #\n");
while(scanf("%d",&x)>0){
p=start;
start=(struct node *)malloc(sizeof(struct node));
if(start==NULL){
printf("not enough memory\n");
exit(1);
}
start->num = x;
start->next=p;
}
printf("aaa\n");
*q = (char *)p;
printf("%c\n",q);
for(p=start;p!=NULL;p=p->next)
printf("%d\n",p->num);
}

