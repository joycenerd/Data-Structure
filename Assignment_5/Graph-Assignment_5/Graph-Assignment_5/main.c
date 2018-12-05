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
#define N 20
typedef unsigned long int ui;

typedef struct{
    int vertex1;
    int vertex2;
    int weight;
    int mark;
}Graph;

int *maintainSubset(int v,int w,int arr[],int totalnodes){
    int i;
    if(arr[v]<0 && arr[w]<0){
        arr[v]+=arr[w];
        for(i=0;i<totalnodes;i++){
            if(arr[i]==w) arr[i]=v;
        }
        arr[w]=v;
    }
    return arr;
}

int checkInSub(int v,int w, int arr[],int totalnodes){
    if(arr[v]<0 && arr[w]<0) return 1;
    else if(v==arr[w]) return -1;
    else if(w==arr[v]) return -1;
    else return 1;
}

int cmp(const void *a, const void *b){
    int l = ((Graph *)a)->weight;
    int r = ((Graph *)b)->weight;
    return (l - r);
}

void Kruskal(FILE *fin){
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
                graph[count].vertex1=i;
                graph[count].vertex2=j;
                graph[count].mark=0;
                graph[count++].weight=edge[i][j];
            }
        }
    }
    qsort(graph,count,sizeof(Graph),cmp);
    int subset[N];
    for(i=0;i<totalnodes;i++) subset[i]=-1;
    int edgecount=0,cur=0;
    while(edgecount<totalnodes-1){
        v=graph[cur].vertex1-1;
        w=graph[cur].vertex2-1;
        int check=checkInSub(v, w, subset, totalnodes);
        if(check==1){
            printf("Edge %d: (%d,%d) cost: %d",edgecount,v+1,w+1,edge[v+1][w+1]);
            *subset=*maintainSubset(v,w,subset,totalnodes);
        }
    }
}

int mainMenu(){
    int choice;
    printf("(1) Kruskal Algorithm\n");
    printf("(2) Prim Algorithm\n");
    printf("(3) Dijkstra Algorithm\n");
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
    }
}
