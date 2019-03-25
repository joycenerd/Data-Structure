#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200
#define MAX 100000

int cpList(int from[],int to[],int tail,int end){
	int i;
	for(i=0;i<=tail;i++) to[i]=from[i];
	to[++tail]=end;
	return *to;
}


int choose(int dist[],int n,int vis[]){
	int mini=MAX;
	int idx,i;
	for(i=1;i<=n;i++){
		if(!vis[i] && dist[i]<mini){
			mini=dist[i];
			idx=i;
		}
	}
	return idx;
}

int main()
{
	FILE *fin=fopen("7input_3.txt","r");
	assert(fin!=NULL);
	int n;
	int cost[N][N];
	int dist[N],vis[N]={0};
	int i,j;
	fscanf(fin,"%d",&n);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(fin,"%d",&cost[i][j]);
			if(cost[i][j]==0) cost[i][j]=MAX;
		}
	}
	int start,end;
	fscanf(fin,"%d %d",&start,&end);
	int path[N][N],tail[N];
	for(i=0;i<N;i++) tail[i]=-1;
	for(i=1;i<=n;i++){
		dist[i]=cost[start][i];
		if(cost[start][i]<MAX){
			path[i][0]=start;
			path[i][1]=i;
			tail[i]=1;
		}
	}
	vis[start]=1;
	int u;
	for(i=0;i<n-2;i++){
		int idx=choose(dist,n,vis);
		vis[idx]=1;
		for(u=1;u<=n;u++){
			if(dist[idx]+cost[idx][u]<dist[u]){
				dist[u]=dist[idx]+cost[idx][u];
				memset(path[u],0,sizeof(path[u]));
				*path[u]=cpList(path[idx],path[u],tail[idx],u);
				tail[u]=tail[idx]+1;
			}
		}
	}
	if(tail[end]==-1) printf("-1\n");
	else{
		for(i=0;i<=tail[end];i++) printf("%d ",path[end][i]);
		printf("\n");
	}
	return 0;
}