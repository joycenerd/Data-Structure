#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define N 20


typedef struct listnode *listptr;
typedef struct listnode{
	int data;
	listptr link;
}List;

typedef struct{
	int key;
	int count;
}Arr;

listptr concatenation(listptr ptr1,listptr ptr2){
	listptr head=ptr1;
	while(ptr1->link) ptr1=ptr1->link;
	ptr1->link=ptr2;
	return head;
}

listptr constructList(Arr a[]){
	int count=a[0].count;
	int i;
	listptr ptr=NULL,head;
	for(i=0;i<count;i++){
		listptr node=malloc(sizeof(List));
		node->data=a[i].key;
		node->link=NULL;
		if(!ptr){
			ptr=node;
			head=node;
		}
		else{
			ptr->link=node;
			ptr=node;
		}
	}
	return head;
}

Arr *readFile(FILE *file){
	int count=0;
	static Arr arr[N];
	int num;
	while(!feof(file)){
		fscanf(file,"%d",&num);
		arr[count++].key=num;
	}
	fclose(file);
	arr[0].count=count;
	return arr;
}

int main()
{
	FILE *file1=fopen("test1.txt","r");
	assert(file1!=NULL);
	Arr *arr=readFile(file1);
	fclose(file1);
	listptr ptr1=constructList(arr);
	FILE *file2=fopen("test2.txt","r");
	assert(file2!=NULL);
	arr=readFile(file2);
	fclose(file2);
	listptr ptr2=constructList(arr);
	listptr newptr=concatenation(ptr1,ptr2);
	while(newptr){
		printf("%d ",newptr->data);
		listptr temp=newptr;
		newptr=newptr->link;
		free(temp);
	}
	printf("\n");
	return 0;
}