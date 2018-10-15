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

// the rat will follow specific direction finding method in this function
int *Order(int cur,int who) {
    Direction direc[2][4];
    // direc[0][] is for rat A, and direc[1][] is for rat B
    direc[0][0].vert = direc[1][3].vert = 0;
    direc[0][0].horiz = direc[1][3].horiz = 1;
    direc[0][1].vert = direc[1][2].vert = 1;
    direc[0][1].horiz = direc[1][2].horiz = 0;
    direc[0][2].vert = direc[1][1].vert = -1;
    direc[0][2].horiz = direc[1][1].horiz = 0;
    direc[0][3].vert = direc[1][0].vert = 0;
    direc[0][3].horiz = direc[1][0].horiz = -1;
    // according to current direction to find the next direction
    cur++;
    static int next[3];
    next[0] = direc[who][cur].vert;
    next[1] = direc[who][cur].horiz;
    next[2] = cur;
    return next;
}

// finding the next step for the rat
int *nextStep(int *current, int maze[MAX_DATA][MAX_DATA],int who) {
    int *next;
    int currentdir = current[2];
    while (currentdir < 4) {
        // the possible move of the next step
        next = Order(currentdir,who);
        int nextrow = current[0] + next[0];
        int nextcol = current[1] + next[1];
        currentdir = next[2];
        // identify if it's a feasible move and return the value
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

// This is like the function in C++ stack.top(), read the top value of the stack
int *readStack(int top, Stack stack[]) {
    static int front[3];
    front[0] = stack[top].row;
    front[1] = stack[top].col;
    front[2] = stack[top].prevdir;
    return front;
}

// recording and maintaing the whole stack of the two rats, rat A and rat B
void stackRecord(int maze[MAX_DATA][MAX_DATA]) {
    // write the result to the result.txt file
    FILE *fout;
    fout=fopen("result.txt","w");
    // copy the maze into two maze one for rat A and another for rat B
    int maze_a[MAX_DATA][MAX_DATA],maze_b[MAX_DATA][MAX_DATA];
    int i,j;
    for(i=0;i<MAX_DATA;i++){
        for(j=0;j<MAX_DATA;j++){
            maze_a[i][j]=maze_b[i][j]=maze[i][j];
        }
    }
    // frontvalue is the top value of the stack <row, column, previous direction>
    int *frontvalue_a,*frontvalue_b;
    // position is the next step of the rats
    int *position_a,*position_b;
    // two stack for two rats
    Stack stack_a[MAX_DATA * MAX_DATA],stack_b[MAX_DATA * MAX_DATA];
    // initialize the rat A in the (0,0) and rat B in the (14,14)
    int top_a = 0,top_b=0;
    stack_a[top_a].row = 0;
    stack_a[top_a].col = 0;
    stack_a[top_a].prevdir = -1;
    stack_b[top_b].row = MAX_DATA-1;
    stack_b[top_b].col = MAX_DATA-1;
    stack_b[top_b].prevdir = -1;
    // check if the rat find their way out
    int find_a = 1,find_b=1;
    // the two rats take turns to walk, first A then B, then A, then B... until one of the rats walk out the maze
    int round=0;
    while (1) {
        // rat A stack record
        if(round%2==0 && find_a!=0){
            frontvalue_a = readStack(top_a, stack_a);
            position_a = nextStep(frontvalue_a,maze_a,0);
            // add the previous direction to the stack, so the rat won;t walk again the same road next time finding
            stack_a[top_a].prevdir = position_a[2];
            // if the rat have passed by before than mark it to 1 so the next time won't walk again
            maze_a[position_a[0]][position_a[1]] = 1;
            // if the rat have tried the four direction of this situation, but still not find the way out, than pop this element try other route
            if (stack_a[top_a].prevdir == 4) top_a--;
            // if this is a possible choice than push it to stack
            else {
                top_a++;
                stack_a[top_a].row = position_a[0];
                stack_a[top_a].col = position_a[1];
                stack_a[top_a].prevdir = -1;
            }
            // if the stack is empty then this represent that there is no possible route for the rat to walk out the maze, and set the find to 0
            if (top_a == -1) {
                fprintf(fout,"Stack is empty! Mouse A has no way to go out of the maze\n");
                find_a = 0;
            }
            // if the rat has walk out the maze than brea the loop to finish the program
            if (stack_a[top_a].row == MAX_DATA-1 && stack_a[top_a].col == MAX_DATA-1){
                fprintf(fout,"ratA: (%d,%d)\n",stack_a[top_a].row,stack_a[top_a].col);
                break;
            }
            // if the rat still got the chance to walk out the maze(stack isn't empty), print the path
            if(find_a) fprintf(fout,"ratA: (%d,%d)\n",stack_a[top_a].row,stack_a[top_a].col);
        }
        // rat B stack record
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
    // read the maze from the file and make it to a maze matrix
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
    // do the rest of work in the function stackRecord
    stackRecord(maze);
    return 0;
}
