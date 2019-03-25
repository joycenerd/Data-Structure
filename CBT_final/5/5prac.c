#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200


typedef struct {
	int v1;
	int v2;
	int w;
} Graph;

int adjust(int sub[],int n,int a,int b){
	int i;
	if(sub[a]<0 && sub[b]<0) sub[b]=a;
	else if(sub[a]<0 && sub[b]>0){
		for(i=1;i<=n;i++){
			if(sub[i]==b) sub[i]=a;
		}
		sub[b]=a;
	}
	else if(sub[b]<0 && sub[a]>0){
		for(i=1;i<=n;i++){
			if(sub[i]==a) sub[i]=b;
		}
		sub[a]=b;
	}
	else{
		for(i=1;i<=n;i++){
			if(sub[i]==sub[b]) sub[i]=sub[a];
		}
		sub[b]=sub[a];
	}
	return *sub;
}

int check(int a,int b,int sub[]){
	if(sub[a]>0 || sub[b]>0){
		if(sub[a]==b || sub[b]==a || sub[a]==sub[b]) return -1;
	}
	return 1;
}

int cmp(const void *a, const void *b) {
	int l = ((Graph *)a)->w;
	int r = ((Graph *)b)->w;
	return l - r;
}

int main()
{
	FILE *fin = fopen("5input_3.txt", "r");
	assert(fin != NULL);
	int n, i, j, v;
	Graph g[N];
	int cnt = 0;
	fscanf(fin, "%d", &n);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			fscanf(fin, "%d", &v);
			if (v != 0 && i < j) {
				g[cnt].v1 = i;
				g[cnt].v2 = j;
				g[cnt++].w = v;
			}
		}
	}
	qsort(g, cnt, sizeof(Graph), cmp);
	int e = 0, cur = 0;
	int sub[N];
	for(i=0;i<N;i++) sub[i]=-1;
	while (e < n - 1) {
		int from=g[cur].v1;
		int to=g[cur].v2;
		int cost=g[cur++].w;
		int yn=check(from,to,sub);
		if(yn==1){
			printf("%d %d %d\n",from,to,cost);
			e++;
			*sub=adjust(sub,n,from,to);
		}
	}
	return 0;
}
