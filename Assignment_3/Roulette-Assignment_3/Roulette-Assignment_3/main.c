//
//  main.c
//  Roulette-Assignment_3
//
//  Created by Joyce Chin on 2018/10/23.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_LEN 200
typedef unsigned long int ui;


// record my nodes
typedef struct listnode *listptr;
typedef struct listnode{
    char data[MAX_LEN]; // store my data (name)
    int mark; // check if the node is delete from my list
    listptr rlink; // clockwise
    listptr llink; // counterclockwise
}List;

// the main operation of the russian roulette game
// pop out data until the only survivior
void russianRoulette(int dir,listptr ptr,int total){
    printf("Input skip number: ");
    int skip;
    scanf("%d",&skip);
    int counter;
    if(dir==1){ // right
        do{
            printf("list length is: %d\n",total);
            for(counter=0;counter<=skip;counter++){
                do{
                    ptr=ptr->rlink;
                }while(ptr->mark);
            }
            printf("the data is popped: %s\n",ptr->data);
            ptr->mark=1;
        }while(total-- && total!=1);
        while(ptr->mark) ptr=ptr->rlink;
        printf("the last data is: %s\n",ptr->data);
    }
    else if(dir==2){ // left
        ptr=ptr->llink;
        do{
            printf("list length is: %d\n",total);
            for(counter=0;counter<=skip;counter++){
                do{
                    ptr=ptr->llink;
                }while(ptr->mark);
            }
            printf("the data is popped: %s\n",ptr->data);
            ptr->mark=1;
        }while(total-- && total!=1);
        while(ptr->mark) ptr=ptr->llink;
        printf("the last data is: %s\n",ptr->data);
    }
    while(ptr){
        listptr temp=ptr;
        ptr=ptr->rlink;
        free(temp);
    }
}

// choose the direction
int directionMenu(){
    printf("choose your direction: \n");
    printf("(1) right\n");
    printf("(2) left\n");
    int dir;
    scanf("%d",&dir);
    if(dir!=1 && dir!=2){
        printf("There is no this choice\n");
        directionMenu();
    }
    return dir;
}

// invert my linked list (left direction)
// current is the head of the original linked list, trail is the node which
// rlink point to current
listptr invertList(listptr current,listptr trail){
    listptr head=current;
    do{
        current->llink=trail;
        trail=current;
        current=current->rlink;
    }while(current!=head);
    return head;
}

// linked all my data
listptr createList(listptr ptr, char *data,ui len){
    listptr node=malloc(sizeof(List));
    strncpy(node->data,data,len-1);
    // node->mark if to see if the node has been pop
    node->mark=0;
    // linked in direction right
    if(!ptr){
        ptr=node;
        ptr->rlink=ptr;
    }
    else{
        node->rlink=ptr->rlink;
        ptr->rlink=node;
        ptr=node;
    }
    printf("%s is appended\n",ptr->data);
    return ptr;
}

listptr inputData(){
    int num;
    listptr ptr=NULL,head=NULL;
    printf("How many nodes do you want to append: ");
    scanf("%d\n",&num);
    char name[MAX_LEN];
    while(num--){
        fgets(name,MAX_LEN,stdin);
        ui len=strlen(name);
        if(!ptr){
            ptr=createList(ptr, name,len);
            head=ptr;
        }
        else ptr=createList(ptr, name,len);
    }
    head=invertList(head, ptr);
    return head;
}

// read the data from the file
listptr readData(){
    FILE *fp;
    fp=fopen("data.csv","r");
    assert(fp!=NULL);
    char line[MAX_LEN];
    listptr ptr=NULL,head=NULL;
    // create linked list (right direction)
    while(fgets(line,MAX_LEN,fp)!=NULL){
        ui len=strlen(line)-1;
        if(!ptr){
            ptr=createList(ptr,line,len);
            head=ptr;
        }
        else ptr=createList(ptr, line,len);
    }
    // invert my linked list (left direction)
    head=invertList(head,ptr);
    return head;
}

// choose what to do with the program
int menu(){
    printf("What do you want to do?\n");
    printf("(1) Read data from a file\n");
    printf("(2) Append new nodes\n");
    printf("(0) Exit\n");
    int choice;
    scanf("%d",&choice);
    return choice;
}

int main()
{
    while(1){
        int choice=menu();
        listptr ptr=NULL;
        if(choice==1){
            ptr=readData();
        }
        else if(choice==2){
            ptr=inputData();
        }
        else if(choice==0) break;
        else{
            printf("There is no this choice\n");
            continue;
        }
        listptr start=ptr;
        if(ptr==NULL){
            printf("The list is empty\n");
            continue;
        }
        printf("the list datas are:\n");
        printf("[");
        int totalnode=0;
        do{
            if(start->rlink==ptr) printf("%s]",start->data);
            else printf("%s, ",start->data);
            start=start->rlink;
            totalnode++;
        }while(start!=ptr);
        printf("\n");
        int dir=directionMenu();
        russianRoulette(dir,ptr,totalnode);
    }
    return 0;
}
