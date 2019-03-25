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
graphptr head[N]={NULL};

int dfn[N],low[N],vis[N]={0},anti[N]={0};
int num=0;

int mini(int a,int b){
	if(a<=b) return a;
	return b;
}

void dfnlow(int child,int parent){
	graphptr ptr;
	int w;
	dfn[child]=low[child]=num++;
	for(ptr=head[child];ptr;ptr=ptr->link){
		w=ptr->v;
		if(dfn[w]<0){
			dfnlow(w,child);
			low[child]=mini(low[child],low[w]);
			if(low[w]>=dfn[child]) anti[child]=1;
		}
		else if(w!=parent) low[child]=mini(low[child],dfn[w]);
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
	FILE *fout=fopen("output.txt","w");
	assert(fin!=NULL);
	int root;
	fscanf(fin,"%d",&root);
	int n;
	fscanf(fin,"%d",&n);
	int i,j;
	graphptr ptr[N];
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			int p;
			fscanf(fin,"%d",&p);
			if(p==1 && i<j){
				graphptr node1=malloc(sizeof(Node));
				node1->v=i;node1->link=NULL;
				if(!head[j]) head[j]=node1;
				else ptr[j]->link=node1;
				ptr[j]=node1;
				graphptr node2=malloc(sizeof(Node));
				node2->v=j;node2->link=NULL;
				if(!head[i]) head[i]=node2;
				else ptr[i]->link=node2;
				ptr[i]=node2; 
			}
		}
	}
	init();
	dfnlow(root,-1);
	for(i=1;i<=n;i++) fprintf(fout,"%d ",dfn[i]);
	fprintf(fout,"\n");
	for(i=1;i<=n;i++) fprintf(fout,"%d ",low[i]);
	fprintf(fout,"\n");
	for(i=1;i<=n;i++){
		if(anti[i]==1) fprintf(fout,"%d ",i);
	}
	fprintf(fout,"\n");
	fclose(fin);fclose(fout);
	return 0;
}