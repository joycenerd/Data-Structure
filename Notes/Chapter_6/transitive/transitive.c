#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 10

int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	int n;
	fscanf(file,"%d",&n);
	int i,j,k;
	int cost[N][N],dist[N][N];
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			fscanf(file,"%d",&cost[i][j]);
			dist[i][j]=cost[i][j];
		}
	}
	for(k=0;k<=n;k++){
		for(i=0;i<=n;i++){
			for(j=0;j<=n;j++){
				dist[i][j]=dist[i][j] || (dist[i][k] && dist[k][j]); 
			}
		}
	}
	printf("transitive closure matrix:\n");
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			if(j==n)printf("%d\n",dist[i][j]);
			else printf("%d ",dist[i][j]);
		}
	}
	printf("reflexive transitive closure matrix:\n");
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			if(i==j && j==n) printf("1\n");
			else if(i==j) printf("1 ");
			else if(j==n) printf("%d\n",dist[i][j]);
			else printf("%d ",dist[i][j]);
		}
	}
	return 0;
}