#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200


char str[2*N];

typedef struct{
    int exp;
    int coef;
}Poly[N];

Poly poly[2];

int splitString(int which){
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
    int have=0;
    while(i<count){
        poly[which][have].exp=temp[i];
        poly[which][have].coef=temp[i+1];
        i+=2;have++;
    }
    return have;
}

int main()
{
    fgets(str,2*N,stdin);
    //printf("%s",str);
    int end1=splitString(0);
    fgets(str,2*N,stdin);
    //printf("%s",str);
    int end2=splitString(1);
    int start1=0,start2=0;
    Poly ans;
    int count=0;
    while(start1<end1 && start2<end2){
        if(poly[0][start1].exp==poly[1][start2].exp){
            ans[count].exp=poly[0][start1].exp;
            ans[count].coef=poly[0][start1].coef+poly[1][start2].coef;
            count++;start1++;start2++;
        }
        else if(poly[0][start1].exp>poly[1][start2].exp){
            ans[count].exp=poly[0][start1].exp;
            ans[count].coef=poly[0][start1].coef;
            count++;start1++;
        }
        else{
            ans[count].exp=poly[1][start2].exp;
            ans[count].coef=poly[1][start2].coef;
            count++;start2++;
        }
    }
    while(start1<end1){
        ans[count].exp=poly[0][start1].exp;
        ans[count].coef=poly[0][start1].coef;
        count++;start1++;
    }
    while(start2<end2){
        ans[count].exp=poly[1][start2].exp;
        ans[count].coef=poly[1][start2].coef;
        count++;start2++;
    }
    int i;
    for(i=0;i<count;i++) printf("exp: %d coeff: %d\n",ans[i].exp,ans[i].coef);
    return 0;
}
