#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200


int main()
{
	FILE *fin=fopen("3input_3.txt","r");
	assert(fin!=NULL);
	int n,i,j,k;
	int dist[N][N];
	fscanf(fin,"%d",&n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++) fscanf(fin,"%d",&dist[i][j]);
	}
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++) dist[i][j]=dist[i][j] || (dist[i][k] && dist[k][j]);
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