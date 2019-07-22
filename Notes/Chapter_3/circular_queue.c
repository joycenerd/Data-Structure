#include <stdio.h>
#include <stdlib.h>
#define N 6


int main()
{
	int queue[N];
	int choice;
	int front=0,rear=0;
	while(1){
		printf("add(1),delete(2) or exit(0): ");
		scanf("%d",&choice);
		printf("%d %d\n",front,rear);
		int num;
		if(choice==1){
			if((rear+1)%N==front){
				printf("Queue is full\n");
				continue;
			}
			rear=(rear+1)%N;
			printf("enter your data you want to add: ");
			scanf("%d",&num);
			queue[rear]=num;
		}
		else if(choice==2){
			if(front==rear){
				printf("Queue is empty\n");
				continue;
			}
			front=(front+1)%N;
		}
		else if(choice==0){
			int temp;
			front=(front+1)%N;
			if(rear<front){
				temp=front;
				front=rear;
				rear=temp;
			}
			for(int i=front;i<=rear;i++){
				if(i==front) printf("%d",queue[i]);
				else printf(" %d",queue[i]);
			}
			printf("\n");
			break;
		}
	}
	return 0;
}