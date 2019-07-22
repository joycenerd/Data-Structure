#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 30


void swap(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	while(!feof(file)){
		int n,i,j;
		int data[N];
		fscanf(file,"%d",&n);
		for(i=0;i<n;i++) fscanf(file,"%d",&data[i]);
		for(i=0;i<n-1;i++){
			int mini=i;
			for(j=i+1;j<n;j++){
				if(data[j]<data[mini]) mini=j;
			}
			swap(&data[i],&data[mini]);
		}
		for(i=0;i<n;i++) printf("%d ",data[i]);
		printf("\n");
	}
	return 0;
}
