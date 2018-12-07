//
//  main.c
//  Graph-Assignment_5
//
//  Created by Joyce Chin on 2018/12/2.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#define N 20
#define MAX_WEIGHT 1000000
typedef unsigned long int ui;

typedef struct{
    int vertex1;
    int vertex2;
    int weight;
    int mark;
}Graph;

int choice(int dist[],int visit[],int totalnodes){
    int mini=MAX_WEIGHT;
    int index=-1;
    int i;
    for(i=0;i<totalnodes;i++){
        if(dist[i]<mini && !visit[i]){
            mini=dist[i];
            index=i;
        }
    }
    return index;
}

void Dijkstra(FILE *fin){
    int totalnodes,i,j;
    fscanf(fin,"%d",&totalnodes);
    int cost[N][N];
    for(i=0;i<totalnodes;i++){
        for(j=0;j<totalnodes;j++){
            fscanf(fin,"%d",&cost[i][j]);
            if(cost[i][j]==0) cost[i][j]=MAX_WEIGHT;
        }
    }
    printf("Enter two vertices <start end>: ");
    int start,end;
    scanf("%d%d",&start,&end);
    int visit[N]={0},dist[N];
    for(i=0;i<totalnodes;i++) dist[i]=cost[start][i];
    visit[start]=1;
    for(i=0;i<totalnodes-2;i++){
        int next=choose(dist,visit,totalnodes);
    }
}

int cmp(const void *a, const void *b){
    int l = ((Graph *)a)->weight;
    int r = ((Graph *)b)->weight;
    return (l - r);
}

int findEdge(int subset[],int totalnodes,Graph graph[],int count){
    int i;
    for(i=0;i<count;i++){
        if(graph[i].mark==1) continue;
        int v=graph[i].vertex1;
        int w=graph[i].vertex2;
        if(subset[v] && !subset[w]) return i;
        else if(!subset[v] && subset[w]) return i;
    }
    return 0;
}

void Prim(FILE *fin){
    printf("The output is\n");
    int totalnodes;
    fscanf(fin,"%d",&totalnodes);
    Graph graph[N];
    int i,j,v,w;
    int edge[N][N];
    int count=0;
    for(i=0;i<totalnodes;i++){
        for(j=0;j<totalnodes;j++){
            fscanf(fin,"%d",&edge[i][j]);
            if(j<i && edge[i][j]!=0){
                graph[count].vertex1=j;
                graph[count].vertex2=i;
                graph[count].mark=0;
                graph[count++].weight=edge[i][j];
            }
        }
    }
    qsort(graph,count,sizeof(Graph),cmp);
    int subset[N]={0};
    int start;
    fscanf(fin,"%d",&start);
    subset[start-1]=1;
    int edgecount=1,mincost=0;
    while(edgecount<totalnodes){
        int index=findEdge(subset,totalnodes,graph,count);
        v=graph[index].vertex1;
        w=graph[index].vertex2;
        graph[index].mark=1;
        printf("Edge %d: (%d,%d) cost: %d\n",edgecount++,v+1,w+1,edge[v][w]);
        mincost+=edge[v][w];
        subset[v]=subset[w]=1;
    }
    printf("Minimum cost = %d\n\n",mincost);
}


int *maintainSubset(int v,int w,int arr[],int totalnodes){
    int i,parent;
    if(arr[v]<0 && arr[w]<0){
        arr[v]+=arr[w];
        for(i=0;i<totalnodes;i++){
            if(arr[i]==w) arr[i]=v;
        }
        arr[w]=v;
    }
    else if(arr[v]<0 && arr[w]>=0){
        parent=arr[w];
        arr[v]+=arr[parent];
        for(i=0;i<totalnodes;i++){
            if(arr[i]==parent) arr[i]=v;
        }
        arr[parent]=v;
    }
    else if(arr[v]>=0 && arr[w]<0){
        parent=arr[v];
        arr[w]+=arr[parent];
        for(i=0;i<totalnodes;i++){
            if(arr[i]==parent) arr[i]=w;
        }
        arr[parent]=w;
    }
    else{
        int p1=arr[v],p2=arr[w];
        arr[p1]+=arr[p2];
        for(i=0;i<totalnodes;i++){
            if(arr[i]==p2) arr[i]=p1;
        }
        arr[p2]=p1;
    }
    return arr;
}

int checkInSub(int v,int w, int arr[],int totalnodes){
    if(arr[v]<0 && arr[w]<0) return 1;
    else if(v==arr[w]) return -1;
    else if(w==arr[v]) return -1;
    else return 1;
}

void Kruskal(FILE *fin){
    printf("The cost of Minimum Cost Spanning Tree are\n");
    Graph graph[N];
    int totalnodes;
    fscanf(fin,"%d",&totalnodes);
    int i,j,v,w;
    int edge[N][N];
    int count=0;
    for(i=0;i<totalnodes;i++){
        for(j=0;j<totalnodes;j++){
            fscanf(fin,"%d",&edge[i][j]);
            if(j<i && edge[i][j]!=0){
                graph[count].vertex1=j;
                graph[count].vertex2=i;
                graph[count].mark=0;
                graph[count++].weight=edge[i][j];
            }
        }
    }
    qsort(graph,count,sizeof(Graph),cmp);
    int subset[N];
    for(i=0;i<totalnodes;i++) subset[i]=-1;
    int edgecount=1,cur=0,mincost=0;
    while(edgecount<totalnodes){
        v=graph[cur].vertex1;
        w=graph[cur++].vertex2;
        int check=checkInSub(v, w, subset, totalnodes);
        if(check==1){
            printf("Edge %d: (%d,%d) cost: %d\n",edgecount++,v+1,w+1,edge[v][w]);
            mincost+=edge[v][w];
            *subset=*maintainSubset(v,w,subset,totalnodes);
        }
    }
    printf("Minimum cost = %d\n\n",mincost);
}

int mainMenu(){
    int choice;
    printf("(1) Kruskal Algorithm\n");
    printf("(2) Prim Algorithm\n");
    printf("(3) Dijkstra Algorithm\n");
    printf("(4) Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    while(1){
        int choice=mainMenu();
        printf("please enter your file: ");
        char str[N],filename[N];
        scanf("\n");
        fgets(str,N,stdin);
        ui len=strlen(str);
        int i;
        for(i=0;i<len-1;i++) filename[i]=str[i];
        FILE *fin=fopen(filename,"r");
        assert(fin!=NULL);
        if(choice==1) Kruskal(fin);
        else if(choice==2) Prim(fin);
        else if(choice==3) Dijkstra(fin);
    }
}
