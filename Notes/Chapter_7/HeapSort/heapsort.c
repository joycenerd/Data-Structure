#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 100


int Swap(int arr[],int a,int b){
	int tmp=arr[a];
	arr[a]=arr[b];
	arr[b]=tmp;
	return *arr;
}

int main()
{
	FILE *file = fopen("test.txt", "r");
	assert(file != NULL);
	int list[N];
	int count = 1;
	int i;
	while (!feof(file)) {
		int num;
		fscanf(file, "%d", &num);
		i = count;
		while (i >= 1) {
			if((i/2)>=1 && list[i/2]<num){
				list[i]=list[i/2];
				i/=2;
			}
			else{
				list[i]=num;
				break;
			}
		}
		count++;
	}
	count--;
	int n=count;
	while(count>=1){
		//printf("[%d %d]",list[1],list[count]);
		*list=Swap(list,1,count);
		count--;
		int i=1;
		while(i<count){
			if(i*2<=count && list[i*2]>list[i*2+1]){
				if(list[i*2]>list[i]){
					*list=Swap(list,i,i*2);
					i*=2;
				}
				else break;
			}
			else if(i*2+1<=count && list[i*2+1]>list[i*2]){
				if(list[i*2+1]>list[i]){
					*list=Swap(list,i,i*2+1);
					i=i*2+1;
				}
				else break;
			}
			else break;
		}
		//printf("[%d] ",count);
		for(i=1;i<=n;i++) printf("%d ",list[i]);
		printf("\n");
	}
	for(i=1;i<=n;i++) printf("%d ",list[i]);
	printf("\n");
}