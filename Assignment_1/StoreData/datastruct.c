#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define N 200


typedef struct{
    char name[N];
    int index;
}Data;

int main()
{
    FILE *file;
    file=fopen("data.csv","r");
    assert(file!=NULL);
    char line[N];
    int size=1;
    Data *pdata=malloc(size*sizeof(Data));
    int count=0;
    while(fgets(line,N,file)!=NULL){
        char *token[2];
        token[0]=strtok(line,",\0");
        if(token[0]!=NULL) token[1]=strtok(NULL,",\0");
        strncpy(pdata[count].name,token[0],N);
        pdata[count].index=atoi(token[1]);
        if(count+1==size){
            size*=2;
            Data *realldata=realloc(pdata,size*sizeof(Data));
            pdata=realldata;
        }
        count++;
    }
    int i;
    for(i=0;i<count;i++) printf("%s %d\n",pdata[i].name,pdata[i].index);
    return 0;
}