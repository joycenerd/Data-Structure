#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 110


int main()
{
	FILE *fin=fopen("3input_3.txt","r");
	FILE *fout=fopen("3output.txt","w");
	int n;
	fscanf(fin,"%d",&n);
	int i,j,k;
	int dist[N][N];
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
			if(j==n-1) fprintf(fout,"%d\n",dist[i][j]);
			else fprintf(fout,"%d ",dist[i][j]);
		}
	}
	return 0;
}