#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200

typedef struct{
    int row;
    int col;
    int val;
}Matrix;

int main()
{
    int a[6][6]={0};
    Matrix matrix[N];
    a[0][0]=15;a[0][3]=22;a[0][5]=-15;a[1][1]=11;a[1][2]=3;a[2][3]=-6;a[4][0]=91;a[5][2]=28;
    int i,j;
    matrix[0].row=6;matrix[0].col=6;matrix[0].val=8;
    int count=1;
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
    for(i=0;i<count;i++) printf("[%d] %3d %3d %3d\n",i,matrix[i].row,matrix[i].col,matrix[i].val);
    return 0;
}
