#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 20


typedef struct graphnode *graphptr;
typedef struct graphnode {
	int vertex;
	graphptr link;
} Node;
graphptr head[N] = {NULL};

int dfn[N], low[N], visit = {0};
int num = 0;

int mini(int a, int b) {
	if (a <= b) return a;
	else return b;
}

void dfnlow(int child, int parent) {
	graphptr ptr;
	int v;
	dfn[child] = low[child] = num++;
	for (ptr = head[child]; ptr; ptr = ptr->link) {
		v = ptr->vertex;
		if (dfn[v] < 0) {
			dfnlow(v, child);
			low[child] = mini(low[child], low[v]);
		}
		else if (v != parent) low[child] = mini(low[child], dfn[v]);
	}
}

void init() {
	int i;
	for (i = 0; i < N; i++) {
		dfn[i] = -1;
		low[i] = -1;
	}
}

int main()
{
	FILE *file = fopen("test.txt", "r");
	assert(file != NULL);
	graphptr adjlist[N];
	while (!feof(file)) {
		int v, w;
		fscanf(file, "%d %d", &v, &w);
		graphptr nodev = malloc(sizeof(Node));
		graphptr nodew = malloc(sizeof(Node));
		nodev->vertex = v; nodev->link = NULL;
		nodew->vertex = w; nodew->link = NULL;
		if (!head[v]) head[v] = nodew;
		else adjlist[v]->link = nodew;
		if (!head[w]) head[w] = nodev;
		else adjlist[w]->link = nodev;
		adjlist[v] = nodew;
		adjlist[w] = nodev;
	}
	init();
	dfnlow(3, -1);
	int i;
	for (i = 0; i < 10; i++) printf("%d ", dfn[i]);
	printf("\n");
	for (i = 0; i < 10; i++) printf("%d ", low[i]);
	printf("\n");
	return 0;
}
