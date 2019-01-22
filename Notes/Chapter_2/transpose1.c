#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200


typedef struct{
    int row;
    int col;
    int val;
}Matrix;

Matrix matrix[N],transpose[N];

// doing transpose
void doTranspose(int pos,int cur){
    transpose[cur].row=matrix[pos].col;
    transpose[cur].col=matrix[pos].row;
    transpose[cur].val=matrix[pos].val;
}

int main()
{
    int a[6][6]={0};
    a[0][0]=15;a[0][3]=22;a[0][5]=-15;a[1][1]=11;a[1][2]=3;a[2][3]=-6;a[4][0]=91;a[5][2]=28;
    int i,j;
    matrix[0].row=6;matrix[0].col=6;matrix[0].val=8;
    int count=1;
    // define my sparse matrix
    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
            if(a[i][j]!=0){
                matrix[count].row=i;
                matrix[count].col=j;
                matrix[count].val=a[i][j];
                count++;
            }
        }
    }
    // Scan the array
    doTranspose(0,0);
    int cur=1;
    for(i=0;i<matrix[0].col;i++){
        for(j=1;j<=matrix[0].val;j++){
            if(matrix[j].col==i){
                doTranspose(j,cur);
                cur++;
            }
        }
    }
    printf("origin             transpose\n");
    for(i=0;i<matrix[0].val;i++){
        printf("[%d]%3d %3d %3d   ",i,matrix[i].row,matrix[i].col,matrix[i].val);
        printf("%3d %3d %3d\n",transpose[i].row,transpose[i].col,transpose[i].val);
    }
    return 0;
}