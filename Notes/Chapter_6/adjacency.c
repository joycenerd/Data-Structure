#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define  MAX_V 10


typedef struct graphnode *graphptr;
typedef struct graphnode{
	int vertex;
	graphptr link;
}Node;

void adjList(FILE *fin){
	graphptr graph[MAX_V]={NULL};
	graphptr head[MAX_V]={NULL};
	int v,w;
	while(!feof(fin)){
		fscanf(fin,"%d %d",&v,&w);
		graphptr node1=malloc(sizeof(Node));
		graphptr node2=malloc(sizeof(Node));
		node1->vertex=w; 
		node2->vertex=v;
		node1->link=node2->link=NULL;
		if(!graph[v]) graph[v]=head[v]=node1;
		else{
			graph[v]->link=node1;
			graph[v]=graph[v]->link;
		}
		if(!graph[w]) graph[w]=head[w]=node2;
		else{
			graph[w]->link=node2;
			graph[w]=graph[w]->link;
		}
		//printf("%d %d\n",graph[v]->vertex,graph[w]->vertex);
	}
	int i;
	for(i=0;i<MAX_V;i++){
		while(head[i]){
			printf("%d ",head[i]->vertex);
			head[i]=head[i]->link;
		}
		printf("\n");
	}
}

void adjMatrix(FILE *fin){
	int matrix[MAX_V][MAX_V]={0};
	int v,w;
	while(!feof(fin)){
		fscanf(fin,"%d %d",&v,&w);
		matrix[v][w]=matrix[w][v]=1;
	}
	int i,j;
	for(i=0;i<MAX_V;i++){
		for(j=0;j<MAX_V;j++){
			if(j==MAX_V-1) printf("%d\n",matrix[i][j]);
			else printf("%d ",matrix[i][j]);
		}
	}
}

int main()
{
	FILE *fin=fopen("graphs.txt","r");
	assert(fin!=NULL);
	printf("(1)adjacency matrix\n");
	printf("(2)adjacency list\n");
	int choice;
	scanf("%d",&choice);
	if(choice==1) adjMatrix(fin);
	else if(choice==2) adjList(fin);
}