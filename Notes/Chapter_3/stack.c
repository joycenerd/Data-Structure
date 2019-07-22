#include <stdio.h>
#define N 200


int stackFull(int top) {
	if (top == N - 1) return 1;
	else return 0;
}

int stackEmpty(int top) {
	if (top == -1) return 1;
	else return 0;
}

int Pop(int top,int stack[]){
	top--;
	return *stack;
}

int Push(int top, int stack[], int item) {
	top++;
	stack[top] = item;
	return *stack;
}

int main()
{
	int *stack;
	int top = -1;
	int choice;
	int item;
	int check;
	while (1) {
		printf("push(1) or pop(2)? or exit(0): ");
		scanf("%d", &choice);
		if (choice == 1) {
			check=stackFull(top);
			if(check){
				printf("The stack is full, you can't add any item now\n");
				continue;
			}
			printf("enter pushing item: ");
			scanf("%d", &item);
			*stack = Push(top, stack, item);
			top++;
		}
		else if(choice==2){
			check=stackEmpty(top);
			if(check){
				printf("The stack is empty, there is no data to delete\n");
				continue;
			}
			*stack=Pop(top,stack);
			top--;
		}
		else if (choice == 0) {
			printf("stack elements: ");
			int i;
			for (i = 0; i <= top; i++) {
				if (i == 0) printf("%d", *(stack + i));
				else printf(" %d", *(stack + i));
			}
			printf("\n");
			break;
		}
	}
	return 0;
}