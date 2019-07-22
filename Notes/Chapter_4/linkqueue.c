#include <stdio.h>
#include <stdlib.h>


typedef struct listnode *queueptr;
typedef struct listnode{
	int data;
	queueptr link;
}Queue;

queueptr printQueue(queueptr front){
	while(front){
		printf("%d\n",front->data);
		queueptr temp=front;
		front=front->link;
		free(temp);
	}
	return front;
}

queueptr pop(queueptr front){
	if(front){
		queueptr temp=front;
		front=front->link;
		free(temp);
	}
	return front;
}

queueptr push(queueptr rear, int data){
	queueptr temp=malloc(sizeof(Queue));
	temp->data=data;
	temp->link=NULL;
	if(!rear) rear=temp;
	else{
		rear->link=temp;
		rear=rear->link;
	}
	return rear;
}

int menu(){
	int choice;
	printf("(1) push\n");
	printf("(2) pop\n");
	printf("(3) output\n");
	printf("(4) exit\n");
	printf("What's your choice? ");
	scanf("%d",&choice);
	return choice;
}

int main()
{
	int choice;
	queueptr front=NULL,rear=NULL;
	while(1){
		choice=menu();
		if(choice==1){
			int data;
			printf("Enter your data: ");
			scanf("%d",&data);
			rear=push(rear,data);
			if(!front) front=rear;
		}
		else if(choice==2){
			front=pop(front);
			if(!front) printf("The queue is empty, their is nothing to delete\n");
		}
		else if(choice==3) front=printQueue(front);
		else if(choice==4) break;
	}
	return 0;
}