#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 200

int main()
{
	int failure[N];
	char pat[N];
	strncpy(pat,"ababbabababb",N);
	int len=strlen(pat);
	failure[0]=0;
	int cur,index;
	for(cur=1;cur<len;cur++){
		index=failure[cur-1];
		while((pat[cur]!=pat[index+1]) && (index>=1)) index=failure[index];
		if(pat[cur]==pat[index+1]) failure[cur]=index+1;
		else failure[cur]=0; 
	}
	int i;
	for(i=0;i<len;i++) printf("%c %d\n",pat[i],failure[i]);
	return 0;
}