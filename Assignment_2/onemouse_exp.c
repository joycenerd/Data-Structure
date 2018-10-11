#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define LINE_SIZE 200
#define MAX_DATA 15


typedef struct{
    int row;
    int col;
    int prevdir;
}Stack;

typedef struct{
    int vert;
    int horiz;
}Direction;

int *Order(int cur){
    Direction direc[2][4];
    direc[0][0].vert=direc[1][3].vert=0; 
    direc[0][0].horiz=direc[1][3].horiz=1;
    direc[0][1].vert=direc[1][2].vert=1; 
    direc[0][1].horiz=direc[1][2].horiz=0;
    direc[0][2].vert=direc[1][1].vert=-1; 
    direc[0][2].horiz=direc[1][1].horiz=0;
    direc[0][3].vert=direc[1][0].vert=0;
    direc[0][3].horiz=direc[1][0].horiz=-1;
    cur++;
    static int next[3];
    next[0]=dir[cur].vert;
    next[1]=dir[cur].horiz;
    next[2]=cur;
    return next;
}

int *nextStep(int *current, int maze[MAX_DATA][MAX_DATA]){
    int *next;
    int currentdir=current[2];
    while(currentdir<4){
        next=dirOreder(currentdir);
        int nextrow=current[0]+next[0];
        int nextcol=current[1]+next[1];
        currentdir=next[2];
        if(nextrow==-1 || nextcol==-1 || nextrow>=MAX_DATA || nextcol>=MAX_DATA) continue;
        else if(maze[nextrow][nextcol]==0){
            current[0]=nextrow;
            current[1]=nextcol;
            current[2]=currentdir;
            return current;
        }
    }
    current[2]=currentdir;
    return current;
}

int *readStack(int top, Stack stack[]){
    static int front[3];
    front[0]=stack[top].row;
    front[1]=stack[top].col;
    front[2]=stack[top].prevdir;
    return front;
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
    
    return 0;
}
