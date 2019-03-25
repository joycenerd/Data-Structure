#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010


typedef struct graphnode *graphptr;
typedef struct graphnode{
	int v;
	graphptr link;
}Node;

int cmp(const void *a,const void *b){
	return *(int *)b-*(int *)a;
}

int main()
{
	FILE *fin=fopen("1input_3.txt","r");
	assert(fin!=NULL);
	int n;
	fscanf(fin,"%d",&n);
	int i,j,num;
	graphptr head[N]={NULL},ptr[N];
	int rec[N]={0};
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(fin,"%d",&num);
			if(num!=0){
				graphptr node=malloc(sizeof(Node));
				node->v=j;node->link=NULL;
				if(!head[i]) head[i]=node;
				else ptr[i]->link=node;
				ptr[i]=node;
				rec[j]++;
			}
		}
	}
	int arr[N];
	int len=-1;
	for(i=1;i<=n;i++){
		if(rec[i]==0) arr[++len]=i; 
	}
	while(len!=-1){
		qsort(arr,len+1,sizeof(int),cmp);
		int pop=arr[len--];
		printf("%d ",pop);
		while(head[pop]){
			rec[head[pop]->v]--;
			if(rec[head[pop]->v]==0) arr[++len]=head[pop]->v;
			head[pop]=head[pop]->link;
		}
	}
	printf("\n");
	return 0;
}