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

listptr invertList(listptr ptr){
	listptr current=NULL,trail;
	while(ptr){
		trail=current;
		current=ptr;
		ptr=ptr->link;
		current->link=trail;
	}
	return current;
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

Arr *readFile(){
	FILE *file;
	file=fopen("test1.txt","r");
	assert(file!=NULL);
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
	Arr *arr=readFile();
	listptr ptr=constructList(arr);
	ptr=invertList(ptr);
	while(ptr){
		printf("%d\n",ptr->data);
		listptr temp=ptr;
		ptr=ptr->link;
		free(temp);
	}
	return 0;
}