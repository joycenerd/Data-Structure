#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 10


int main()
{
	int adjmat[N][N];
	int nodes;
	int space[N]={0};
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	fscanf(file,"%d",&nodes);
	int i,j;
	int seqarr[N*N];
	int cur=nodes+2;
	for(i=0;i<=nodes;i++){
		for(j=0;j<=nodes;j++){
			fscanf(file,"%d",&adjmat[i][j]);
			if(j==0) seqarr[i]=cur;
			if(adjmat[i][j]) seqarr[cur++]=j;
		}
	}
	seqarr[nodes+1]=cur;
	for(i=0;i<cur;i++) printf("%d ",seqarr[i]);
	printf("\n");
	return 0;
}