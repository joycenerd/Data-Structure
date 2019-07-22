#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 200
typedef unsigned long int ui;


typedef struct listnode *listptr;
typedef struct listnode {
	char key[N];
	listptr link;
} Node;

int main()
{
	FILE *file = fopen("test.txt", "r");
	assert(file != NULL);
	char l[N];
	listptr ptr, head = NULL;
	fgets(l, N, file);
	char *token = strtok(l, " \0");
	while (token != NULL) {
		listptr node = malloc(sizeof(Node));
		strcpy(node->key, token);
		node->link = NULL;
		if (!head) head = node;
		else ptr->link = node;
		ptr = node;
		token = strtok(NULL, " \0");
	}
	ui len = strlen(head->key);
	listptr buff[N][10], hdbuff[N][10] = {NULL};
	while (len > 0) {
		len--;
		while (head) {
			int num = head->key[len] - '0';
			listptr tmp=head;
			head = head->link;
			tmp->link=NULL;
			if (!hdbuff[len][num]) hdbuff[len][num] = tmp;
			else buff[len][num]->link = tmp;
			buff[len][num] = tmp;
		}
		int i, j;
		for (i = 0; i < 10; i++) {
			if (hdbuff[len][i] != NULL) {
				head = hdbuff[len][i];
				ptr = buff[len][i];
				break;
			}
		}
		for (j = i + 1; j < 10; j++) {
			if (hdbuff[len][j] != NULL) {
				ptr->link = hdbuff[len][j];
				ptr = buff[len][j];
			}
		}
		listptr tmp=head;
		while(tmp){
			printf("%s ",tmp->key);
			tmp=tmp->link;
		}
		printf("\n");
	}
	return 0;
}