#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200
#define MAX 100000



int cpList(int from[], int to[], int tail, int add) {
	int i;
	for (i = 0; i <= tail; i++) to[i] = from[i];
	to[++tail] = add;
	return *to;
}

int choose(int dist[], int vis[], int n) {
	int mini = MAX;
	int index, i;
	for (i = 1; i <= n; i++) {
		if (dist[i] < mini && !vis[i]) {
			mini = dist[i];
			index = i;
		}
	}
	return index;
}

int main()
{
	FILE *fin = fopen("7input_3.txt", "r");
	FILE *fout = fopen("7output.txt", "w");
	assert(fin != NULL);
	int n;
	fscanf(fin, "%d", &n);
	int i, j;
	int cost[N][N];
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			fscanf(fin, "%d", &cost[i][j]);
			if (cost[i][j] == 0) cost[i][j] = MAX;
		}
	}
	int start, end;
	fscanf(fin, "%d %d", &start, &end);
	int vis[N] = {0}, dist[N];
	int path[N][N], tail[N];
	for (i = 1; i <= n; i++) tail[i] = -1;
	for (i = 1; i <= n; i++) {
		dist[i] = cost[start][i];
		if (dist[i] < MAX) {
			path[i][0] = start;
			path[i][1] = i;
			tail[i] = 1;
		}
	}
	vis[start] = 1;
	for (i = 0; i < n - 2; i++) {
		int next = choose(dist, vis, n);
		vis[next] = 1;
		int u;
		for (u = 1; u <= n; u++) {
			if (!vis[u] && dist[next] + cost[next][u] < dist[u]) {
				dist[u] = dist[next] + cost[next][u];
				memset(path[u], 0, sizeof(path[u]));
				*path[u] = cpList(path[next], path[u], tail[next], u);
				tail[u] = tail[next] + 1
			}
		}
	}
	if (tail[end] == -1) fprintf(fout,"-1\n");
	else {
		for (i = 0; i <= tail[end]; i++) fprintf(fout,"%d ", path[end][i]);
		fprintf(fout,"\n");
	}
	fclose(fin);fclose(fout);
	return 0;
}
