#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200


typedef struct {
	int v1;
	int v2;
	int weight;
} Graph;

int subset[N];

void adjust(int a, int b, int n) {
	int i;
	if(subset[a]<0 && subset[b]<0) subset[b]=a;
	else if(subset[a]<0 && subset[b]>0){
		for(i=1;i<=n;i++){
			if(subset[i]==b) subset[i]=a;
		}
		subset[b]=a;
	}
	else if(subset[a]>0 && subset[b]<0){
		for(i=1;i<=n;i++){
			if(subset[i]==a) subset[i]=b;
		}
		subset[a]=b;
	}
	else if(subset[a]>0 && subset[b]>0){
		int p=subset[a];
		for(i=1;i<=n;i++){
			if(subset[i]==b) subset[i]=p;
		}
		subset[b]=p;
	}
}

int check(int a, int b) {
	if (subset[a] > 0 || subset[b] > 0) {
		if (subset[a] == b || subset[b] == a || subset[a]==subset[b]) return -1;
	}
	return 1;
}

int cmp(const void *a, const void *b) {
	int l = ((Graph *)a)->weight;
	int r = ((Graph *)b)->weight;
	return l - r;
}

int main()
{
	FILE *fin = fopen("5input_3.txt", "r");
	FILE *fout = fopen("5output.txt", "w");
	assert(fin != NULL);
	int n;
	fscanf(fin, "%d", &n);
	int i, j;
	Graph graph[N];
	int count = 0;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			int w;
			fscanf(fin, "%d", &w);
			if (i <= j && w != 0) {
				graph[count].v1 = i;
				graph[count].v2 = j;
				graph[count++].weight = w;
			}
		}
	}
	qsort(graph, count, sizeof(Graph), cmp);
	for (i = 0; i <= n; i++) subset[i] = -1;
	int e = 0, cur = 0;
	while (e < n-1) {
		int from = graph[cur].v1;
		int to = graph[cur].v2;
		int w = graph[cur++].weight;
		int yn = check(from, to);
		if (yn == 1) {
			fprintf(fout,"%d %d %d\n", from, to, w);
			adjust(from, to, n);
			e++;
		}
		else {
			if (cur == n + 1) {
				fprintf(fout,"No spanning tree!\n");
				break;
			}
		}
	}
	fclose(fin);fclose(fout);
	return 0;
}

