v#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200


int n, start, end, dist[N], vis[N];

typedef struct {
    int now;
    int step;
} Node;

int bfs() {
    int i;
    Node que[N];
    int front = -1, rear = -1;
    vis[start] = 1;
    Node v, next;
    v.now = start;
    v.step = 0;
    que[++rear] = v;
    while (front != rear) {
        Node pop = que[++front];
        if (pop.now == end)
            return pop.step;
        for (i = 0; i < 2; i++) {
            if (i == 0)
                next.now = pop.now + dist[pop.now];
            else
                next.now = pop.now - dist[pop.now];
            if (!vis[next.now] && next.now >= 1 && next.now <= n){
                if (next.now == end)
                    return pop.step + 1;
                vis[next.now] = 1;
                next.step = pop.step + 1;
                que[++rear] = next;
            }
        }
    }
    return -1;
}

int main(void)
{
    int i;
    FILE *fin = fopen("6input_3.txt", "r");
    FILE *fout = fopen("6output.txt", "w");
    fscanf(fin,"%d %d %d", &n, &start, &end);
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= n; i++) fscanf(fin,"%d", &dist[i]);
    int mini=bfs();
    fprintf(fout,"%d\n", mini);
    fclose(fin);fclose(fout);
    return 0;
}