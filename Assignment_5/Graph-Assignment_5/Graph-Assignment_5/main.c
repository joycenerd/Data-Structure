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
#define MAX_WEIGHT 1000000
typedef unsigned long int ui;


// structure for undirected graph
typedef struct{
    int vertex1;
    int vertex2;
    int weight;
    int mark;
}Graph;

// choosing smallest weight node
int choose(int dist[],int visit[],int totalnodes){
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

// find shortest path of directed graph with nonnegative weights
void Dijkstra(FILE *fin){
    int totalnodes,i,j;
    fscanf(fin,"%d",&totalnodes);
    int cost[N][N];
    // graph realtion matrix
    // if two nodes doesn't have directed edge connected set the cost[][] as a large number
    for(i=0;i<totalnodes;i++){
        for(j=0;j<totalnodes;j++){
            fscanf(fin,"%d",&cost[i][j]);
            if(cost[i][j]==0) cost[i][j]=MAX_WEIGHT;
        }
    }
    printf("Enter two vertices <start end>: ");
    int start,end;
    scanf("%d%d",&start,&end);
    // check if the starting node is in the graph
    if(start<1 || start>totalnodes) printf("Invalid starting node\n");
    if(end<1 || end>totalnodes) printf("Invalid ending node\n");
    int visit[N]={0},dist[N];
    // initialize all the distance to cost[start][]
    for(i=0;i<totalnodes;i++) dist[i]=cost[start-1][i];
    // mark starting node as visited
    visit[start-1]=1;
    // initialize starting node distance to 0
    dist[start-1]=0;
    // from reachable node choose the smallest weight total as the next node and visit it
    for(i=0;i<totalnodes-2;i++){
        int next=choose(dist,visit,totalnodes);
        visit[next]=1;
        int v;
        // update all the other unvisited nodes' distance
        for(v=0;v<totalnodes;v++){
            if(!visit[v] && dist[next]+cost[next][v]<dist[v]){ dist[v]=dist[next]+cost[next][v];
            }
        }
    }
    int mincost=dist[end-1];
    printf("The cost from %d to %d is: ",start,end);
    // if doesn't find a path from starting node to ending node, print -1
    if(mincost==MAX_WEIGHT) printf("-1\n");
    else printf("%d\n",mincost);
}

// compare function of qsort
int cmp(const void *a, const void *b){
    int l = ((Graph *)a)->weight;
    int r = ((Graph *)b)->weight;
    return (l - r);
}

// find smallest edge from nodes in-set to node out-set
int findEdge(int subset[],int totalnodes,Graph graph[],int count){
    int i;
    for(i=0;i<count;i++){
        if(graph[i].mark==1) continue; // if edge already chosen skip
        int v=graph[i].vertex1;
        int w=graph[i].vertex2;
        // choosing edge be one node in-set and another node out-set
        if(subset[v] && !subset[w]) return i;
        else if(!subset[v] && subset[w]) return i;
    }
    return 0;
}

// add edges (in-set node, out-set node)
void Prim(FILE *fin){
    printf("The output is\n");
    int totalnodes;
    fscanf(fin,"%d",&totalnodes);
    Graph graph[N];
    int i,j,v,w;
    int edge[N][N];
    int count=0;
    // construct graph relation struct
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
    // sort wieght from the smallest to the largest
    qsort(graph,count,sizeof(Graph),cmp);
    int subset[N]={0};
    int start;
    // starting node --> the set only contains starting node in the beginning
    fscanf(fin,"%d",&start);
    subset[start-1]=1;
    int edgecount=1,mincost=0;
    while(edgecount<totalnodes){
        // find smallest edge from nodes in-set to node out-set
        int index=findEdge(subset,totalnodes,graph,count);
        v=graph[index].vertex1;
        w=graph[index].vertex2;
        // if chosen mark as 1
        graph[index].mark=1;
        printf("Edge %d: (%d,%d) cost: %d\n",edgecount++,v+1,w+1,edge[v][w]);
        mincost+=edge[v][w];
        subset[v]=subset[w]=1;
    }
    printf("Minimum cost = %d\n",mincost);
}

// root is always smaller than 0
// other nodes' value is the root index represent as in the same set
int *maintainSubset(int v,int w,int arr[],int totalnodes){
    int i,parent;
    // create subset
    if(arr[v]<0 && arr[w]<0){
        arr[v]+=arr[w];
        for(i=0;i<totalnodes;i++){
            if(arr[i]==w) arr[i]=v;
        }
        arr[w]=v;
    }
    // merging two subsets
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

// check if the two nodes are in the same set or not
int checkInSub(int v,int w, int arr[],int totalnodes){
    if(arr[v]<0 && arr[w]<0) return 1;
    else if(v==arr[w]) return -1;
    else if(w==arr[v]) return -1;
    else return 1;
}

// add edges from smallest weight to the largest
// check there is no circle while adding edges
void Kruskal(FILE *fin){
    printf("The cost of Minimum Cost Spanning Tree are\n");
    Graph graph[N];
    int totalnodes;
    fscanf(fin,"%d",&totalnodes);
    int i,j,v,w;
    int edge[N][N];
    int count=0;
    // if the nodes are connected add to graph struct
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
    // sort the weight of the edges from smallest to largest
    qsort(graph,count,sizeof(Graph),cmp);
    // subset is used to check if there will be circle while adding edges
    int subset[N];
    for(i=0;i<totalnodes;i++) subset[i]=-1;
    int edgecount=1,cur=0,mincost=0;
    while(edgecount<totalnodes){
        v=graph[cur].vertex1;
        w=graph[cur++].vertex2;
        // if v and w are in the same set discard this edge
        // because there will be cycle if adding this edge
        int check=checkInSub(v, w, subset, totalnodes);
        // if not in the same subset then add this edge
        // make v and w and all nodes related to them to the same set
        if(check==1){
            printf("Edge %d: (%d,%d) cost: %d\n",edgecount++,v+1,w+1,edge[v][w]);
            mincost+=edge[v][w];
            // revise subset array everytime adding new edges
            *subset=*maintainSubset(v,w,subset,totalnodes);
        }
    }
    printf("Minimum cost = %d\n",mincost);
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
        // choose algorithm for finding the shortest path
        int choice=mainMenu();
        if(choice==4) break;
        printf("please enter your file: ");
        // read file
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
        printf("\n");
    }
    return 0;
}
