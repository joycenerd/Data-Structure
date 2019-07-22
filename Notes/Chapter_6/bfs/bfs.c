#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 10


typedef struct graphnode *graphptr;
typedef struct graphnode{
	int vertex;
	graphptr link;
}Node;

void bfs(int start,graphptr adjlist[],int n){
	int queue[N*N];
	int front=-1,rear=-1;
	int visit[N]={0};
	queue[++rear]=start;
	visit[start]=1;
	while(front!=rear){
		int pop=queue[++front];
		printf("%d ",pop);
		graphptr v;
		for(v=adjlist[pop];v;v=v->link){
			if(!visit[v->vertex]){
				queue[++rear]=v->vertex;
				visit[v->vertex]=1;
			}
		}
	}
	printf("\n");
}

int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	graphptr adjlist[N],head[N]={NULL};
	while(!feof(file)){
		int v,w;
		fscanf(file,"%d %d",&v,&w);
		graphptr nodev=malloc(sizeof(Node));
		graphptr nodew=malloc(sizeof(Node));
		nodev->vertex=v; nodev->link=NULL;
		nodew->vertex=w; nodew->link=NULL;
		if(!head[v]) head[v]=nodew;
		else adjlist[v]->link=nodew;
		if(!head[w]) head[w]=nodev;
		else adjlist[w]->link=nodev;
		adjlist[v]=nodew;
		adjlist[w]=nodev;
	}
	bfs(0,head,10);
	return 0;
}