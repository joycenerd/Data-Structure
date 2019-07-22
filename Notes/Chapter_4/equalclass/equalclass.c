#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 50


typedef struct listnode *listptr;
typedef struct listnode {
	int key;
	listptr link;
} List;

listptr createNewNode(listptr ptr, int data) {
	listptr node = malloc(sizeof(List));
	node->key = data;
	node->link = NULL;
	if (!ptr) ptr = node;
	else {
		ptr->link = node;
		ptr = node;
	}
	return ptr;
}

void readFile(FILE *fp) {
	int num1, num2;
	listptr seq[N] = {NULL}, ptr[N] = {NULL};
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &num1, &num2);
		if (!ptr[num1]) {
			ptr[num1] = createNewNode(ptr[num1], num2);
			seq[num1] = ptr[num1];
		}
		else if (ptr[num1]) {
			ptr[num1] = createNewNode(ptr[num1], num2);
			listptr temp = seq[num1];
		}
		if (!ptr[num2]) {
			ptr[num2] = createNewNode(ptr[num2], num1);
			seq[num2] = ptr[num2];
		}
		else if (ptr[num2]) {
			ptr[num2] = createNewNode(ptr[num2], num1);
			listptr temp = seq[num2];
		}
	}

}

int main()
{
	FILE *fp;
	fp = fopen("test.txt", "r");
	assert(fp != NULL);
	readFile(fp);
	fclose(fp);
	
}