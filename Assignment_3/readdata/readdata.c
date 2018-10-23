#include <stdio.h>
#include <string.h>
#include <assert.h>
#define N 200


int main()
{
	FILE *fp;
	fp=fopen("data.csv","r");
	assert(fp!=NULL);
	char line[N];
	while(fgets(line,N,fp)!=NULL){
		printf("%s",line);
	}
	return 0; 
}