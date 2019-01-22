#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200
typedef unsigned long int ui;

int main()
{
    char mainstring[N],pattern[N];
    fgets(mainstring,N,stdin);
    fgets(pattern,N,stdin);
    ui lens=strlen(mainstring)-1;
    ui lenp=strlen(pattern)-1;
    int i;
    int flag=0;
    for(i=0;i<lens-lenp+1;i++){
        if(strncmp(mainstring+i,pattern,lenp)==0){
            printf("starting index: %d\n",i);
            flag=1;
            break;
        }
    }
    if(flag==0) printf("Pattern not found\n");
    return 0;
}