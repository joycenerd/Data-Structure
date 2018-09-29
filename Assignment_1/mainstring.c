#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200


typedef struct{
    char name[N];
    int index;
}Data;

int main()
{
    char string[5][N]={"jim","tom","patty","helen","aaaaa"};
    int num[5]={1,2,3,4,4};
    int i;
    Data data[5];
    for(i=0;i<5;i++){
        strncpy(data[i].name,string[i],N);
        data[i].index=num[i];
    }
    int strsize=N;
    char *mainstring=malloc(strsize*sizeof(char));
    int strcount=0,location=0;
    printf("Current mainstring: """);
    int insertindex=0;
    for(i=0;i<5;i++){
        printf("name: %s\n",data[i].name);
        printf("index: %d\n",data[i].index);
        if(strcount+strlen(data[i].name)>strsize){
            strsize*=2;
            char *pstr=realloc(mainstring,strsize*sizeof(char));
            mainstring=pstr;
        }
        char *tempstr=malloc(strsize*sizeof(char));
        strncpy(tempstr,mainstring,strsize);
        strncpy(mainstring,tempstr,insertindex);
        strncpy(mainstring+insertindex,data[i].name,strlen(data[i].name));
        strcpy(mainstring+insertindex+strlen(data[i].name),tempstr+insertindex);
        insertindex+=data[i].index;
        printf("after insertion to my mainstring: %s\n",mainstring);
    }
    return 0;
}