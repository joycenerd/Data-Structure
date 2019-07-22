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
		int n;
		fscanf(file,"%d",&n);
		int i,j;
		int data[N];
		for(i=0;i<n;i++) fscanf(file,"%d",&data[i]);
		for(i=0;i<n-1;i++){
			for(j=0;j<n-i-1;j++){
				if(data[j]>data[j+1]) swap(&data[j],&data[j+1]);
			}
		}
		for(i=0;i<n;i++) printf("%d ",data[i]);
		printf("\n");
	}
	return 0;
}