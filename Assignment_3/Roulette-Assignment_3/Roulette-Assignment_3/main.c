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


typedef struct listnode *listptr;
typedef struct listnode{
    char data[MAX_LEN];
    int mark;
    listptr rlink;
    listptr llink;
}List;

listptr invertList(listptr current,listptr trail){
    listptr head=current;
    do{
        current->llink=trail;
        trail=current;
        current=current->rlink;
    }while(current!=head);
    do{
        printf("%s\n",current->data);
        current=current->llink;
    }while(current!=head);
    return 0;
}

listptr createList(listptr ptr, char *data){
    listptr node=malloc(sizeof(List));
    ui len=strlen(data)-1;
    strncpy(node->data,data,len-1);
    if(!ptr){
        ptr=node;
        ptr->rlink=ptr;
    }
    else{
        node->rlink=ptr->rlink;
        ptr->rlink=node;
        ptr=node;
    }
    return ptr;
}

void readData(){
    FILE *fp;
    fp=fopen("data.csv","r");
    assert(fp!=NULL);
    char line[MAX_LEN];
    listptr ptr=NULL,head=NULL;
    while(fgets(line,MAX_LEN,fp)!=NULL){
        if(!ptr){
            ptr=createList(ptr,line);
            head=ptr;
        }
        else ptr=createList(ptr, line);
    }
    head=invertList(head,ptr);
}

int menu(){
    printf("What do you want to do?\n");
    printf("(1) Read data drom a file\n");
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
        if(choice==1){
            readData();
            break;
        }
    }
}
