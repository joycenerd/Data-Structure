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
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	int arr[N];
	int n=0;
	char *token=strtok(l," \0");
	while(token!=NULL){
		arr[n++]=atoi(token);
		token=strtok(NULL," \0");
	}
	int i,j,k;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(arr[j]>arr[j+1]) swap(&arr[j],&arr[j+1]);
		}
		for(k=0;k<n;k++) printf("%d ",arr[k]);
		printf("\n");
	}
	return 0;
}