#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define LINE_SIZE 200
#define MAX_DATA 15


void constructmaze(FILE *file){
	char line[LINE_SIZE];
	int maze[MAX_DATA][MAX_DATA];
	int row=0,col;
	while(fgets(line,LINE_SIZE,file)!=NULL){
		for(col=0;col<MAX_DATA;col++) maze[row][col]=line[col]-'0';
		row++;
	}
	for(row=0;row<MAX_DATA;row++){
		for(col=0;col<MAX_DATA;col++){
			if(col==MAX_DATA-1) printf("%d\n",maze[row][col]);
			else printf("%d ",maze[row][col]);
		}
	}
}

int main()
{
	FILE *file;
	file=fopen("maze.txt","r");
	assert(file!=NULL);
	constructmaze(file);
	return 0;
}