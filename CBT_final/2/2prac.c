#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010


int main()
{
	FILE *fin=fopen("2input_3.txt","r");
	FILE *fout=fopen("2output.txt","w");
	assert(fin!=NULL);
	int n;
	fscanf(fin,"%d",&n);
	int in[N]={0},out[N]={0};
	int i,j,p;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(fin,"%d",&p);
			if(p!=0){
				out[i]++;in[j]++;
			}
		}
	}
	for(i=1;i<=n;i++) printf("%d %d %d\n",i,in[i],out[i]);
	return 0;
}