#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010


int Swap(int arr[],int a,int b){
	int tmp=arr[a];
	arr[a]=arr[b];
	arr[b]=tmp;
	return *arr;
}

void quicksort(int arr[],int n,int l,int r){
	if(l<r){
		int i=l,j=r+1,piv=l,k;
		do{
			do i++; while(arr[i]<arr[piv]);
			do j--; while(arr[j]>arr[piv]);
			if(i<j){
				*arr=Swap(arr,i,j);
				for(k=0;k<n;k++) printf("%d ",arr[k]);
				printf("\n");
			}
		}while(i<j);
		if(piv!=j){
			*arr=Swap(arr,piv,j);
			for(k=0;k<n;k++) printf("%d ",arr[k]);
			printf("\n");
		}
		quicksort(arr,n,l,j-1);
		quicksort(arr,n,j+1,r);
	}
}

int main()
{
	FILE *fin=fopen("4input_3.txt","r");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	char *token=strtok(l," \0");
	int arr[N];
	int n=0;
	while(token!=NULL){
		arr[n++]=atoi(token);
		token=strtok(NULL," \0");
	}
	quicksort(arr,n,0,n-1);
	return 0;
}