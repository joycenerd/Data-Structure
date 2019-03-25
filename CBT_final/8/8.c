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
	int cost;
	int vis;
}Graph;

int find(Graph graph[],int cnt,int rec[]){
	int i;
	int mini=MAX;
	int index;
	for(i=0;i<cnt;i++){
		if(!graph[i].vis){
			int v=graph[i].v1;
			int w=graph[i].v2;
			int dist=graph[i].cost;
			if(rec[v]==1 && rec[w]==0 && dist<mini){
				mini=dist; index=i;
			}
			else if(rec[v]==0 && rec[w]==1 && dist<mini){
				mini=dist; index=i;
			}
		}
	}
	return index;
}

int cmp(const void *a,const void *b){
	int l=((Graph *)a)->cost;
	int r=((Graph *)b)->cost;
	return l-r;
}

int main()
{
	FILE *fin=fopen("8input_3.txt","r");
	FILE *fout=fopen("8output.txt","w");
	assert(fin!=NULL);
	int n;
	fscanf(fin,"%d",&n);
	int i,j;
	Graph graph[N];
	int cnt=0;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			int v;
			fscanf(fin,"%d",&v);
			if(v!=0 && i<j){
				graph[cnt].v1=i;
				graph[cnt].v2=j;
				graph[cnt].cost=v;
				graph[cnt++].vis=0;
			}
		}
	}
	qsort(graph,cnt,sizeof(Graph),cmp);
	int rec[N]={0};
	int edge=1;
	fprintf(fout,"%d %d %d %d\n",edge++,graph[0].v1,graph[0].v2,graph[0].cost);
	rec[graph[0].v1]=1;rec[graph[0].v2]=1;
	graph[0].vis=1;
	while(edge<n){
		int index=find(graph,cnt,rec);
		fprintf(fout,"%d %d %d %d\n",edge++,graph[index].v1,graph[index].v2,graph[index].cost);
		rec[graph[index].v1]=1;rec[graph[index].v2]=1;
		graph[index].vis=1;
	}
}