#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define N 10
typedef unsigned long int ui;

int maze[N][N];


typedef struct {
	int row;
	int col;
	int prevdir;
} Stack;

typedef struct {
	int vert;
	int horiz;
} Dir;

int *dirOrder(int cur) {
	Dir dir[8];
	dir[0].vert = -1; dir[0].horiz = 0;
	dir[1].vert = -1; dir[1].horiz = 1;
	dir[2].vert = 0; dir[2].horiz = 1;
	dir[3].vert = 1; dir[3].horiz = 1;
	dir[4].vert = 1; dir[4].horiz = 0;
	dir[5].vert = 1; dir[5].horiz = -1;
	dir[6].vert = 0; dir[6].horiz = -1;
	dir[7].vert = -1; dir[7].horiz = -1;
	cur++;
	static int next[3];
	next[0] = dir[cur].vert;
	next[1] = dir[cur].horiz;
	next[2] = cur;
	return next;
}

int *nextStep(int *current) {
	int *next;
	int currentdir = current[2];
	while (currentdir < 8) {
		next = dirOrder(currentdir);
		int nextrow = current[0] + next[0];
		int nextcol = current[1] + next[1];
		currentdir = next[2];
		if (nextrow == -1 || nextcol == -1 || nextrow >= 9 || nextcol >= 6) continue;
		else if (maze[nextrow][nextcol] == 0) {
			current[0] = nextrow;
			current[1] = nextcol;
			current[2] = currentdir;
			return current;
		}
	}
	current[2] = currentdir;
	return current;
}

int *readStack(int top, Stack stack[]) {
	int i;
	static int values[3];
	values[0] = stack[top].row;
	values[1] = stack[top].col;
	values[2] = stack[top].prevdir;
	return values;
}

void stackRec() {
	int i, j;
	int *stackvalue, *position;
	Stack stack[N * N];
	int top = 0;
	stack[top].row = 0;
	stack[top].col = 0;
	stack[top].prevdir = -1;
	int find = 1;
	int count = 10;
	while (1) {
		stackvalue = readStack(top, stack);
		position = nextStep(stackvalue);
		stack[top].prevdir = position[2];
		maze[position[0]][position[1]] = 1;
		if (stack[top].prevdir == 8) {
			top--;
			//maze[position[0]][position[1]]=1;
		}
		else {
			top++;
			stack[top].row = position[0];
			stack[top].col = position[1];
			stack[top].prevdir = -1;
		}
		//printf("%d\n", maze[1][5]);
		//printf("\n");
		if (top == -1) {
			printf("Stack is empty! There is no way to go out of the maze\n");
			find = 0;
			break;
		}
		if (stack[top].row==8 && stack[top].col==5) break;
	}
	if (find) {
		for (int i = 0; i <= top; i++) printf("%d %d %d\n", stack[i].row, stack[i].col, stack[i].prevdir);
		}
}

int main()
{
	FILE *file;
	file = fopen("maze.txt", "r");
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
	//printf("%d\n", maze[1][5]);
	stackRec();
	return 0;
}