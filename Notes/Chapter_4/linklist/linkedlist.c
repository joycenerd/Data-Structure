#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 200


typedef struct listnode *listpointer;
typedef struct listnode {
	char data[N];
	listpointer link;
} ListNode;

// delete node in the list
listpointer delete(listpointer ptr, listpointer node){
	// if the delete node is the head node
	// set the head node to the second element
	if(ptr==node){
		listpointer temp=ptr;
		ptr=ptr->link;
		free(temp);
	}
	// if the delete node isn't head node, link the node before the delete node
	// to the next node of the delete node
	else{
		listpointer temp=node;
		ptr->link=node->link;
		free(temp);
	}
	return ptr;
}

// list insertion
listpointer insert(listpointer ptr, listpointer node){
	listpointer temp=malloc(sizeof(ListNode));  // create a new node
	strcpy(temp->data,"50");
	// if head node exist than insert behind node
	if(ptr){
		temp->link=node->link;
		node->link=temp;
	}
	// or else temp as head node
	else{
		temp->link=NULL;
		ptr=temp;
	}
	return ptr;
}


int main()
{

	FILE *file;
	file = fopen("linklist.txt", "r");
	assert(file != NULL);
	char line[N];
	listpointer ptr = NULL, head = NULL;
	while (fgets(line, N, file) != NULL) {
		int len = strlen(line) - 1;
		if (!ptr) {  // if the list is empty
			ptr = (listpointer)malloc(sizeof(ListNode));
			strncpy(ptr->data, line, len);
			ptr->link = NULL;
			head = ptr;
		}
		else { // if the list isn't empty
			listpointer temp = malloc(sizeof(ListNode));
			strncpy(temp->data, line, len);
			ptr->link = temp;
			temp->link = NULL;
			ptr = ptr->link;
		}
	}
	listpointer node=head->link;
	ptr=insert(head,node);
	head=delete(head,head);
	ptr=head->link;
	head=delete(head,ptr);
	// print my list
	while (head) {
		printf("%s\n", head->data);
		listpointer temp = head;
		head = head->link;
		free(temp);
	}
	return 0;
}