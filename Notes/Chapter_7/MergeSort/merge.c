#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 20


int main()
{
	FILE *file=fopen("test.txt","r");
	assert(file!=NULL);
	int list[N];
	int n=0;
	while(!feof(file)) fscanf(file,"%d",&list[n++]);
	int i,j,k;
	int count=1;
	while(count<n){
		int section;
		if(n%count!=0) section=n/count+1;
		else section=n/count;
		int index=0;
		while(section>0){
			int sub1[N],sub2[N];
			for(j=0;j<count;j++){
				if(index>=n) break; 
				sub1[j]=list[index++];
			}
			int bp1=j;
			section--;
			if(section>0){
				for(j=0;j<count;j++){
					if(index>=n) break; 
					sub2[j]=list[index++];
				}
				int bp2=j;
				j=0;k=0;i=index-bp1-bp2;
				while(j<bp1 && k<bp2){
					if(sub1[j]==sub2[k]){
						list[i++]=sub1[j++];
						list[i++]=sub2[k++];
					}
					else if(sub1[j]<sub2[k]) list[i++]=sub1[j++];
					else if(sub1[j]>sub2[k]) list[i++]=sub2[k++];
				}
				while(j<bp1) list[i++]=sub1[j++];
				while(k<bp2) list[i++]=sub2[k++];
			}
			else{
				i=index-bp1; j=0;
				while(j<bp1) list[i++]=sub1[j++];
			}
			section--;
		}
		count*=2;
	}
	for(i=0;i<n;i++) printf("%d ",list[i]);
	printf("\n");
}