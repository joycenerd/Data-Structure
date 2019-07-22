#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 10

typedef struct graphnode *graphptr;
typedef struct graphnode {
	int vertex;
	graphptr link;
} Node;

void dfs(int start, graphptr adjlist[],int visit[], int n) {
	printf("%d ",start);
	visit[start]=1;
	graphptr v;
	for(v=adjlist[start];v;v=v->link){
		if(!visit[v->vertex]) dfs(v->vertex,adjlist,visit,n);
	}
}

int main()
{
	FILE *file = fopen("test.txt", "r");
	assert(file != NULL);
	graphptr adjlist[N] = {NULL}, head[N] = {NULL}, ptr[N];
	int count = -1;
	while (!feof(file)) {
		int v, w;
		fscanf(file, "%d %d", &v, &w);
		if (v > count) count = v;
		if (w > count) count = w;
		graphptr nodev = malloc(sizeof(Node));
		nodev->vertex = v; nodev->link = NULL;
		graphptr nodew = malloc(sizeof(Node));
		nodew->vertex = w; nodew->link = NULL;
		if (!head[v]) head[v] = nodew;
		else adjlist[v]->link = nodew;
		if (!head[w]) head[w] = nodev;
		else adjlist[w]->link = nodev;
		adjlist[v] = nodew;
		adjlist[w] = nodev;
	}
	int visit[N]={0};
	dfs(0, head,visit,10);
	printf("\n");
	return 0;
}