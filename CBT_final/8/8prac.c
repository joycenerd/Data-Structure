#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200
#define MAX 100000


typedef struct{
	int v1;
	int v2;
	int w;
}Graph;

int find(Graph g[],int sub[],int n){
	int i;
	for(i=0;i<n;i++){
		int a=g[i].v1;
		int b=g[i].v2;
		if(sub[a]==0 && sub[b]==1) return i;
		else if(sub[a]==1 && sub[b]==0) return i;
	}
	return -1;
}

int cmp(const void *a,const void *b){
	int l=((Graph *)a)->w;
	int r=((Graph *)b)->w;
	return l-r;
}

int main()
{
	FILE *fin=fopen("8input_3.txt","r");
	assert(fin!=NULL);
	int n,v,i,j,cnt=0;
	int sub[N]={0};
	Graph g[N];
	fscanf(fin,"%d",&n);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(fin,"%d",&v);
			if(v!=0 && i<j){
				g[cnt].v1=i;
				g[cnt].v2=j;
				g[cnt++].w=v;
			}
		}
	}
	qsort(g,cnt,sizeof(Graph),cmp);
	printf("%d %d %d %d\n",1,g[0].v1,g[0].v2,g[0].w);
	sub[g[0].v1]=1;sub[g[0].v2]=1;
	int e=1;
	while(e<n-1){
		int idx=find(g,sub,cnt);
		printf("%d %d %d %d\n",++e,g[idx].v1,g[idx].v2,g[idx].w);
		sub[g[idx].v1]=1;sub[g[idx].v2]=1;
	}
	return 0;
}