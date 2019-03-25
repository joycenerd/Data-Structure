#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010


int main()
{
	FILE *fin=fopen("2input_3.txt","r");
	assert(fin!=NULL);
	int n,v,i,j;
	int in[N]={0},out[N]={0};
	fscanf(fin,"%d",&n);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(fin,"%d",&v);
			if(v!=0){
				in[j]++;out[i]++;
			}
		}
	}
	for(i=1;i<=n;i++) printf("%d %d %d\n",i,in[i],out[i]);
	return 0;
}