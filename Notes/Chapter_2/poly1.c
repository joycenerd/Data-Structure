#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200


int poly[2][N]={0};
char str[2*N];

void splitString(int which){
    char *token;
    int temp[N];
    token=strtok(str," \0");
    int count=0;
    while(token!=NULL){
        temp[count]=atoi(token);
        token=strtok(NULL," \0");
        count++;
    }
    int i=0;
    while(i<count){
        poly[which][temp[i]]=temp[i+1];
        i+=2;
    }
}

int main()
{
    int ans[N]={0};
    fgets(str,2*N,stdin);
    //printf("%s",str);
    splitString(0);
    fgets(str,2*N,stdin);
    //printf("%s",str);
    splitString(1);
    int i;
    for(i=N-1;i>=0;i--){
        if(poly[0][i]!=0 && poly[1][i]!=0) ans[i]=poly[0][i]+poly[1][i];
        else if(poly[0][i]!=0 && poly[1][i]==0) ans[i]=poly[0][i];
        else if(poly[0][i]==0 && poly[1][i]!=0) ans[i]=poly[1][i];
    }
    for(i=N-1;i>=0;i--) if(ans[i]!=0) printf("exp: %d coeff: %d\n",i,ans[i]);
    return 0;
}
