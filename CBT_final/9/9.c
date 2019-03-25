#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010
#define MAX 100000

void swap(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

int main()
{
	FILE *fin=fopen("9input_3.txt","r");
	FILE *fout=fopen("9output.txt","w");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	char *token=strtok(l," \0");
	int n=0;
	int arr[N];
	while(token!=NULL){
		arr[n++]=atoi(token);
		token=strtok(NULL," \0");
	}
	int i,j,k;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]) swap(&arr[j],&arr[j+1]);
		}
		for(k=0;k<n;k++) fprintf(fout,"%d ",arr[k]);
		fprintf(fout,"\n");
	}
	fclose(fin);fclose(fout);
	return 0;
}