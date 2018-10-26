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

void russianRoulette(int dir,listptr ptr,int total){
    printf("Input skip number: ");
    int skip;
    scanf("%d",&skip);
    int counter;
    if(dir==1){
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
    else if(dir==2){
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
}

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

listptr invertList(listptr current,listptr trail){
    listptr head=current;
    do{
        current->llink=trail;
        trail=current;
        current=current->rlink;
    }while(current!=head);
    return head;
}

listptr createList(listptr ptr, char *data,ui len){
    listptr node=malloc(sizeof(List));
    strncpy(node->data,data,len-1);
    node->mark=0;
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

listptr readData(){
    FILE *fp;
    fp=fopen("data.csv","r");
    assert(fp!=NULL);
    char line[MAX_LEN];
    listptr ptr=NULL,head=NULL;
    while(fgets(line,MAX_LEN,fp)!=NULL){
        ui len=strlen(line)-1;
        if(!ptr){
            ptr=createList(ptr,line,len);
            head=ptr;
        }
        else ptr=createList(ptr, line,len);
    }
    head=invertList(head,ptr);
    return head;
}

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
        break;
    }
}
