//
//  main.c
//  Mazing-Assignment_2
//
//  Created by Joyce Chin on 2018/10/10.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define LINE_SIZE 200
#define MAX_DATA 15


typedef struct {
    int row;
    int col;
    int prevdir;
} Stack;


typedef struct {
    int vert;
    int horiz;
} Direction;

int *Order(int cur,int who) {
    Direction direc[2][4];
    direc[0][0].vert = direc[1][3].vert = 0;
    direc[0][0].horiz = direc[1][3].horiz = 1;
    direc[0][1].vert = direc[1][2].vert = 1;
    direc[0][1].horiz = direc[1][2].horiz = 0;
    direc[0][2].vert = direc[1][1].vert = -1;
    direc[0][2].horiz = direc[1][1].horiz = 0;
    direc[0][3].vert = direc[1][0].vert = 0;
    direc[0][3].horiz = direc[1][0].horiz = -1;
    cur++;
    static int next[3];
    next[0] = direc[who][cur].vert;
    next[1] = direc[who][cur].horiz;
    next[2] = cur;
    return next;
}

int *nextStep(int *current, int maze[MAX_DATA][MAX_DATA],int who) {
    int *next;
    int currentdir = current[2];
    while (currentdir < 4) {
        next = Order(currentdir,who);
        int nextrow = current[0] + next[0];
        int nextcol = current[1] + next[1];
        currentdir = next[2];
        if (nextrow == -1 || nextcol == -1 || nextrow >= MAX_DATA || nextcol >= MAX_DATA) continue;
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
    static int front[3];
    front[0] = stack[top].row;
    front[1] = stack[top].col;
    front[2] = stack[top].prevdir;
    return front;
}

void stackRecord(int maze[MAX_DATA][MAX_DATA]) {
    FILE *fout;
    fout=fopen("result.txt","w");
    int maze_a[MAX_DATA][MAX_DATA],maze_b[MAX_DATA][MAX_DATA];
    int i,j;
    for(i=0;i<MAX_DATA;i++){
        for(j=0;j<MAX_DATA;j++){
            maze_a[i][j]=maze_b[i][j]=maze[i][j];
        }
    }
    int *frontvalue_a,*frontvalue_b, *position_a,*position_b;
    Stack stack_a[MAX_DATA * MAX_DATA],stack_b[MAX_DATA * MAX_DATA];
    int top_a = 0,top_b=0;
    stack_a[top_a].row = 0;
    stack_a[top_a].col = 0;
    stack_a[top_a].prevdir = -1;
    stack_b[top_b].row = MAX_DATA-1;
    stack_b[top_b].col = MAX_DATA-1;
    stack_b[top_b].prevdir = -1;
    int find_a = 1,find_b=1;
    int round=0;
    while (1) {
        if(round%2==0 && find_a!=0){
            frontvalue_a = readStack(top_a, stack_a);
            position_a = nextStep(frontvalue_a,maze_a,0);
            stack_a[top_a].prevdir = position_a[2];
            maze_a[position_a[0]][position_a[1]] = 1;
            if (stack_a[top_a].prevdir == 4) top_a--;
            else {
                top_a++;
                stack_a[top_a].row = position_a[0];
                stack_a[top_a].col = position_a[1];
                stack_a[top_a].prevdir = -1;
            }
            if (top_a == -1) {
                fprintf(fout,"Stack is empty! Mouse A has no way to go out of the maze\n");
                find_a = 0;
            }
            if (stack_a[top_a].row == MAX_DATA-1 && stack_a[top_a].col == MAX_DATA-1){
                fprintf(fout,"ratA: (%d,%d)\n",stack_a[top_a].row,stack_a[top_a].col);
                break;
            }
            if(find_a) fprintf(fout,"ratA: (%d,%d)\n",stack_a[top_a].row,stack_a[top_a].col);
        }
        else if(round%2==1 && find_b!=0){
            frontvalue_b = readStack(top_b, stack_b);
            position_b = nextStep(frontvalue_b,maze_b,1);
            stack_b[top_b].prevdir = position_b[2];
            maze_b[position_b[0]][position_b[1]] = 1;
            if (stack_b[top_b].prevdir == 4) top_b--;
            else {
                top_b++;
                stack_b[top_b].row = position_b[0];
                stack_b[top_b].col = position_b[1];
                stack_b[top_b].prevdir = -1;
            }
            if (top_b == -1) {
                fprintf(fout,"Stack is empty! Mouse A has no way to go out of the maze\n");
                find_b = 0;
            }
            if (stack_b[top_b].row == 0 && stack_b[top_b].col == 0){
                fprintf(fout,"ratB: (%d,%d)\n",stack_b[top_b].row,stack_b[top_b].col);
                break;
            }
            if(find_b) fprintf(fout,"ratB: (%d,%d)\n",stack_b[top_b].row,stack_b[top_b].col);
        }
        round++;
    }
    fclose(fout);
}


int main()
{
    FILE *file;
    file=fopen("maze.txt","r");
    assert(file!=NULL);
    char line[LINE_SIZE];
    int maze[MAX_DATA][MAX_DATA];
    int row=0,col;
    while(fgets(line,LINE_SIZE,file)!=NULL){
        for(col=0;col<MAX_DATA;col++) maze[row][col]=line[col]-'0';
        row++;
    }
    fclose(file);
    stackRecord(maze);
    return 0;
}
