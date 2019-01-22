#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200

typedef struct{
    int row;
    int col;
    int val;
}Matrix;

Matrix matrixa[N],matrixb[N],transposeb[N];

void doTranspose(int pos,int cur){
    transposeb[cur].row=matrixb[pos].col;
    transposeb[cur].col=matrixb[pos].row;
    transposeb[cur].val=matrixb[pos].val;
}

int main()
{
    int a[2][3]={0},b[3][4]={0};
    a[0][0]=15;a[0][2]=-1;a[1][1]=3;a[1][2]=5;
    b[0][2]=9;b[1][0]=5;b[1][1]=-1;b[1][3]=4;b[2][0]=3;b[2][2]=1;b[2][3]=5;
    int i,j;
    matrixa[0].row=2;matrixa[0].col=3;
    matrixb[0].row=3;matrixb[0].col=4;
    int count=1;
    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            if(a[i][j]!=0){
                matrixa[count].row=i;
                matrixa[count].col=j;
                matrixa[count].val=a[i][j];
                count++;
            }
        }
    }
    matrixa[0].val=count-1;
    count=1;
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            if(b[i][j]!=0){
                matrixb[count].row=i;
                matrixb[count].col=j;
                matrixb[count].val=b[i][j];
                count++;
            }
        }
    }
    //matrixb transpose
    matrixb[0].val=count-1;
    int rec[2][N]={0};
    for(i=1;i<=matrixb[0].val;i++) rec[0][matrixb[i].col]++;
    rec[1][0]=1;
    for(i=1;i<matrixb[0].col;i++) rec[1][i]=rec[0][i-1]+rec[1][i-1];
    doTranspose(0,0);
    for(i=1;i<=matrixb[0].val;i++){
        doTranspose(i,rec[1][matrixb[i].col]);
        rec[1][matrixb[i].col]++;
    }
    // sparse matrix multiplication
    int apos=1,bpos=1;
    int multi[N][N]={0};
    while(apos<=matrixa[0].val){
        while(bpos<=transposeb[0].val){
            if(matrixa[apos].col==transposeb[bpos].col){
                multi[matrixa[apos].row][transposeb[bpos].row]+=matrixa[apos].val*transposeb[bpos].val;
            }
            bpos++;
        }
        bpos=1;
        apos++;
    }
    for(i=0;i<matrixa[0].row;i++){
        for(j=0;j<transposeb[0].row;j++){
            if(j==0) printf("%3d",multi[i][j]);
            else printf(" %3d",multi[i][j]);
        }
        printf("\n");
    }
    return 0;
}
