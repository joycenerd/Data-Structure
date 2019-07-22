#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 50

int cmp(const void *a,const void *b){
	return (*(int *)a - *(int *)b);
}

int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	int n;
	while(!feof(file)){
		fscanf(file,"%d",&n);
		int i,j;
		int list1[N]={0},list2[N]={0};
		for(i=0;i<n;i++) fscanf(file,"%d",&list1[i]);
		for(i=0;i<n;i++) fscanf(file,"%d",&list2[i]);
		qsort(list1,n,sizeof(int),cmp);
		qsort(list2,n,sizeof(int),cmp);
		int verify=1;
		i=0;j=0;
		while(i<n && j<n){
			if(list1[i]<list2[j]){
				verify=0;
				printf("list1 number %d isn't in list2\n",list1[i++]);
			}
			else if(list2[j]<list1[i]){
				verify=0;
				printf("list2 number %d isn't in list1\n",list2[j++]);
			}
			else{
				i++;j++;
			}
		}
		while(i<n) printf("list1 number %d isn't in list2\n",list1[i++]);
		while(j<n) printf("list2 number %d isn't in list1\n",list2[j++]);
		if(verify) printf("list1 and list2 are identical\n");
	}
	return 0;
}