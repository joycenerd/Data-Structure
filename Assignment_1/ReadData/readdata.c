#include <stdio.h>
#include <assert.h>
#define N 100

int main()
{
    FILE *file;
    file=fopen("data.csv","r");
    assert(file!=NULL);
    char line[N];
    while(fgets(line,N,file)!=NULL){
        fputs(line,stdout);
    }
    fclose(file);
    return 0;
}
