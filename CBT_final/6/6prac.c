#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 200


int n,start,end,dist[N],vis[N]={0};

typedef struct{
	int now;
	int step;
}Node;

int bfs(){
	Node v,next,pop;
	v.now=start;
	v.step=0;
	vis[start]=1;
	Node que[N];
	int front=-1,rear=-1,i;
	que[++rear]=v;
	while(front!=rear){
		pop=que[++front];
		if(pop.now==end) return pop.step;
		for(i=0;i<2;i++){
			if(i==0) next.now=pop.now+dist[pop.now];
			else next.now=pop.now-dist[pop.now];
			if(!vis[next.now] && next.now<=n && next.now>=1){
				if(next.now==end) return pop.step+1;
				vis[next.now]=1;
				next.step=pop.step+1;
				que[++rear]=next;
			}
		}
	}
	return -1;
}

int main()
{
	FILE *fin=fopen("6input_3.txt","r");
	assert(fin!=NULL);
	fscanf(fin,"%d %d %d\n",&n,&start,&end);
	int i;
	for(i=1;i<=n;i++) fscanf(fin,"%d",&dist[i]);
	int mini=bfs();
	printf("%d\n",mini);
	return 0;
}