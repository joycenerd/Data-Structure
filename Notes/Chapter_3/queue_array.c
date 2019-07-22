#include <stdio.h>
#define N 3


int addQ(int queue[],int rear,int num){
	rear++;
	queue[rear]=num;
	return *queue;
}

int dataMove(int queue[],int front, int rear,int move){
	int i;
	for(i=front;i<=rear;i++) queue[i-move]=queue[i];
	return *queue;
}

int main()
{
	int *queue;
	int front=-1,rear=-1;
	while (1) {
		printf("add(1),delete(2) or exit(0): ");
		int choice;
		scanf("%d", &choice);
		int move;
		int num;
		if(choice==1){
			if(rear==N-1){
				if(front==-1){
					printf("Queue is full,you can't add any data\n");
					continue;
				}
				else{
					move=front+1;
					*queue=dataMove(queue,front,rear,move);
					front-=move; rear-=move;
				}
			}
			printf("enter the number you want to add: ");
			scanf("%d",&num);
			*queue=addQ(queue,rear,num);
			rear++;
		}
		else if(choice==2){
			if(front==rear){
				printf("Queue is empty, you can't delete any data\n");
				continue;
			}
			front++;
		}
		else if(choice==0){
			printf("Element in queue: ");
			for(int i=front+1;i<=rear;i++){
				if(i==front+1) printf("%d",*(queue+i));
				else printf(" %d",*(queue+i));
			}
			printf("\n");
			break; 
		}
	}
	return 0;
}