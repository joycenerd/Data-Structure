#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef unsigned long int ui;


void printArray(int row,int col,int maze[10][10]){
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if(j==5) printf("%d\n",maze[i][j]);
			else printf("%d ",maze[i][j]);
		}
	}
}

int main()
{
	FILE *file;
	int maze[10][10];
	file = fopen("mymaze.in", "r");
	assert(file != NULL);
	char line[200];
	int i = 0, j = 0, cur;
	while (fgets(line, 200, file) != NULL) {
		ui len = strlen(line) - 1;
		for (cur = 0; cur < len; cur++) {
			if (isdigit(line[cur])) {
				maze[i][j] = line[cur] - '0';
				j++;
			}
		}
		j = 0;
		i++;
	}
	for(i=0;i<9;i++){
		for(j=0;j<6;j++){
			if(j==5) printf("%d\n",maze[i][j]);
			else printf("%d ",maze[i][j]);
		}
	}
	printf("\n");
	printArray(9,6,maze);
}