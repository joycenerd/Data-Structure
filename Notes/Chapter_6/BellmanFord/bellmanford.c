#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 10
#define MAX_NUM 1000000

int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	int n;
	fscanf(file,"%d",&n);
	int i,j;
	int cost[N][N];
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			fscanf(file,"%d",&cost[i][j]);
			if(cost[i][j]==0 && i!=j) cost[i][j]=MAX_NUM;
		}
	}
	int start;
	fscanf(file,"%d",&start);
	int dist[N]={0};
	for(i=0;i<=n;i++) dist[i]=cost[start][i];
	int k,u;
	for(k=2;k<=n-1;k++){
		for(u=0;u<=n;u++){
			for(i=0;i<=n;i++){
				if(dist[u]>dist[i]+cost[i][u]) dist[u]=dist[i]+cost[i][u];
			}
		}	
	}
	for(i=0;i<=n;i++) printf("%d ",dist[i]);
	printf("\n");
	return 0;
}