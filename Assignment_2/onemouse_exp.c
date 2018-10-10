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
