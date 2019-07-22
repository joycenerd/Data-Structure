#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 20
#define MAX 1000

typedef struct graphnode *graphptr;
typedef struct graphnode{
	int vertex;
	int dur;
	graphptr link;
}Node;
graphptr head[N]={NULL},ptr[N];
int order[N];

void printForm(int early[],int last[],int n){
	printf("  event order   early time   late time        slack     critical\n");
	int i;
	for(i=0;i<=n;i++){
		int slack=last[order[i]]-early[order[i]];
		printf("%10d%13d%13d%13d",order[i],early[order[i]],last[order[i]],slack);
		if(slack==0) printf("          Yes\n");
		else printf("           No\n");
	}
}

int *lastTime(int early[],int n){
	static int last[N];
	int i;
	for(i=0;i<=n;i++) last[i]=MAX;
	last[n]=early[n];
	int num=n;
	n--;
	while(n>=0){
		int cur=order[n--];
		while(head[cur]){
			int to=head[cur]->vertex;
			int time=head[cur]->dur;
			head[cur]=head[cur]->link;
			if(last[to]-time<last[cur]) last[cur]=last[to]-time;
		}
	}
	return last;
}

int *earlyTime(int count[],int n){
	int i;
	int stack[N];
	int top=-1;
	for(i=0;i<=n;i++){
		ptr[i]=head[i];
		if(count[i]==0) stack[++top]=i;
	}
	int out=0;
	static int early[N]={0};
	while(top!=-1){
		int pop=stack[top--];
		order[out++]=pop;
		while(ptr[pop]){
			int conn=ptr[pop]->vertex;
			int time=ptr[pop]->dur;
			ptr[pop]=ptr[pop]->link;
			if(early[conn]!=0){
				if(time+early[pop]>early[conn]) early[conn]=time+early[pop];
			}
			else early[conn]=time+early[pop];
			count[conn]--;
			if(count[conn]==0) stack[++top]=conn;
		}
	}
	return early;
}

int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	int count[N]={0};
	int num=-1;
	while(!feof(file)){
		int v,w,e;
		fscanf(file,"%d %d %d",&v,&w,&e);
		if(v>num) num=v;
		if(w>num) num=w;
		graphptr node=malloc(sizeof(Node));
		node->vertex=w;
		node->dur=e;
		node->link=NULL;
		if(!head[v]) head[v]=node;
		else ptr[v]->link=node;
		ptr[v]=node;
		count[w]++;
	}
	int i;
	int *early=earlyTime(count,num);
	int *last=lastTime(early,num);
	printForm(early,last,num);
}