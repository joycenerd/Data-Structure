 #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 20


typedef struct graphnode *graphptr;
typedef struct graphnode{
	int vertex;
	graphptr link;
}Node;


int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	int count[N]={0};
	int num=-1;
	graphptr head[N]={NULL},ptr[N];
	while(!feof(file)){
		int v,w;
		fscanf(file,"%d %d",&v,&w);
		if(v>num) num=v;
		if(w>num) num=w;
		count[w]++;
		graphptr node=malloc(sizeof(Node));
		node->vertex=w;
		node->link=NULL;
		if(!head[v]) head[v]=node;
		else ptr[v]->link=node;
		ptr[v]=node;
	}
	int i;
	int stack[N];
	int top=-1;
	for(i=0;i<=num;i++){
		if(count[i]==0) stack[++top]=i;
	}
	while(top!=-1){
		int pop=stack[top--];
		printf("%d ",pop);
		while(head[pop]){
			int conn=head[pop]->vertex;
			head[pop]=head[pop]->link;
			count[conn]--;
			if(count[conn]==0) stack[++top]=conn;
		}
	}
	printf("\n");
	return 0;
}