#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 10
#define MAX_NUM 10000000

int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	int n;
	fscanf(file,"%d",&n);
	int i,j;
	int cost[N][N],dist[N][N];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fscanf(file,"%d",&cost[i][j]);
			if(cost[i][j]==0 && i!=j) cost[i][j]=MAX_NUM;
			dist[i][j]=cost[i][j];
		}
	}
	int k;
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(dist[i][j]>dist[i][k]+dist[k][j]) dist[i][j]=dist[i][k]+dist[k][j];
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(j==n-1) printf("%d\n",dist[i][j]);
			else printf("%d ",dist[i][j]);
		}
	}
	return 0;
}