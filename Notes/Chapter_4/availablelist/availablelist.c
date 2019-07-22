#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 100


typedef struct listnode *listptr;
typedef struct listnode{
	int data;
	listptr link;
}List;

int count;

listptr usingAvail(listptr avail){
	FILE *file;
	file=fopen("test2.txt","r");
	assert(file!=NULL);
	listptr newptr=NULL,head=NULL;
	listptr node;
	int num;
	while(!feof(file)){
		fscanf(file,"%d",&num);
		if(avail){
			node=avail;
			node->data=num;
			avail=avail->link;
		}
		else{
			node=malloc(sizeof(List));
			node->data=num;
		}
		if(!newptr){
			newptr=node;
			head=newptr;
			newptr->link=head;
		}
		else{
			newptr->link=node;
			node->link=head;
			newptr=node;
		}
	}
	fclose(file);
	return head;
}

listptr recycleNode(listptr ptr, listptr avail){
	listptr temp=ptr->link;
	ptr->link=avail;
	avail=temp;
	ptr=NULL;
	return avail;
}

listptr linklist(int *arr){
	listptr head=malloc(sizeof(List));
	head->link=head;
	listptr ptr=head;
	int i;
	for(i=0;i<count;i++){
		listptr node=malloc(sizeof(List));
		node->data=*(arr+i);
		ptr->link=node;
		node->link=head;
		ptr=node;
	}
	return head;
}

int *readFile(){
	FILE *file;
	file=fopen("test1.txt","r");
	assert(file!=NULL);
	count=0;
	static int arr[N];
	while(!feof(file)) fscanf(file,"%d",&arr[count++]);
	fclose(file);
	return arr;
}

int main()
{
	int *arr;
	arr=readFile();
	listptr ptr=linklist(arr);
	listptr head=ptr;
	do{
		printf("%d ",ptr->data);
		ptr=ptr->link;
	}while(ptr!=head);
	printf("\n");
	listptr avail=malloc(sizeof(List));
	avail->link=NULL;
	avail=recycleNode(head,avail);
	listptr newlist=usingAvail(avail);
	head=newlist;
	do{
		printf("%d\n",newlist->data);
		newlist=newlist->link;
	}while(newlist!=head);
}