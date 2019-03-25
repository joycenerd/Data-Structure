#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010


typedef struct graphnode *graphptr;
typedef struct graphnode{
	int vertex;
	graphptr link;
}Node;

int cmp(const void *a,const void *b){
	return *(int *)b-*(int *)a;
}


int main()
{
	FILE *fin=fopen("1input_3.txt","r");
	FILE *fout=fopen("1output.txt","w");
	assert(fin!=NULL);
	int n;
	fscanf(fin,"%d",&n);
	int i,j;
	graphptr head[N]={NULL},ptr[N];
	int rec[N]={0};
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			int v;
			fscanf(fin,"%d",&v);
			if(v!=0){
				graphptr node=malloc(sizeof(Node));
				node->vertex=j;
				node->link=NULL;
				if(!head[i]) head[i]=node;
				else ptr[i]->link=node;
				ptr[i]=node;
				rec[j]++;
			}
		}
	}
	for(i=1;i<=n;i++){
		if(rec[i]==0) rec[i]=-1;
	}
	int arr[N];
	int len=0;
	for(i=1;i<=n;i++){
		if(rec[i]==0) arr[len++]=i;
	}
	while(len){
		qsort(arr,len,sizeof(int),cmp);
		int pop=arr[--len];
		fprintf(fout,"%d ",pop);
		while(head[pop]){
			int cur=head[pop]->vertex;
			rec[cur]--;
			if(rec[cur]==0) arr[len++]=cur;
			head[pop]=head[pop]->link;
		}
	}
	fprintf(fout,"\n");
	fclose(fin); fclose(fout);
	return 0;
}