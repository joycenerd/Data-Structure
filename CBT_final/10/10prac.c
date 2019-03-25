#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010
#define MAX 100000


typedef struct graphnode *graphptr;
typedef struct graphnode{
	int v;
	graphptr link;
}Node;
graphptr head[N];

int dfn[N],low[N],anti[N]={0};
int num=0;

int mini(int a,int b){
	if(a<=b) return a;
	else return b;
}

void dfnlow(int child,int parent){
	dfn[child]=low[child]=num++;
	graphptr ptr;
	for(ptr=head[child];ptr;ptr=ptr->link){
		int u=ptr->v;
		if(dfn[u]<0){
			dfnlow(u,child);
			low[child]=mini(low[child],low[u]);
			if(low[u]>=dfn[child]) anti[child]=1;
		}
		else if(u!=parent) low[child]=mini(low[u],dfn[child]);
	}
}

void init(){
	int i;
	for(i=0;i<N;i++){
		dfn[i]=-1;
		low[i]=-1;
	}
}

int main()
{
	FILE *fin=fopen("10input.txt","r");
	assert(fin!=NULL);
	int root,n;
	fscanf(fin,"%d",&root);
	fscanf(fin,"%d",&n);
	int i,j,p;
	graphptr ptr[N];
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(fin,"%d",&p);
			if(p!=0){
				graphptr node=malloc(sizeof(Node));
				node->v=j; node->link=NULL;
				if(!head[i]) head[i]=node;
				else ptr[i]->link=node;
				ptr[i]=node;
			}
		}
	}
	init();
	dfnlow(root,-1);
	for(i=1;i<=n;i++) printf("%d ",dfn[i]);
	printf("\n");
	for(i=1;i<=n;i++) printf("%d ",low[i]);
	printf("\n");
	for(i=1;i<=n;i++){
		if(anti[i]==1) printf("%d ",i);
	}
	printf("\n");
	return 0;
}