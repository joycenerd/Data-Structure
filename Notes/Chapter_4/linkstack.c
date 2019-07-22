#include <stdio.h>
#include <stdlib.h>


typedef struct listnode *stackptr;
typedef struct listnode {
	int element;
	stackptr link;
} Stack;

stackptr printStack(stackptr top){
	while(top){
		printf("%d\n",top->element);
		stackptr temp=top;
		top=top->link;
		free(temp);
	}
	return top;
}

stackptr pop(stackptr top){
	stackptr temp=top;
	top=top->link;
	free(temp);
	return top;
}

stackptr push(stackptr top, int num) {
	stackptr temp = malloc(sizeof(Stack));
	temp->element = num;
	temp->link = top;
	top = temp;
	return top;
}

int menu() {
	printf("(1) push\n");
	printf("(2) pop\n");
	printf("(3) output\n");
	printf("What's your choice? ");
	int choice;
	scanf("%d", &choice);
	return choice;
}

int main()
{
	stackptr top = NULL, head = NULL;
	int num;
	while (1) {
		int choice = menu();
		if (choice == 1) {
			printf("Enter a number you want to push into the stack: ");
			scanf("%d", &num);
			top = push(top, num);
			//printf("%d\n",top->element);
		}
		else if(choice==2){
			top=pop(top);
		}
		else if (choice == 3) {
			top=printStack(top);
			break;
		}
	}
	return 0;
}