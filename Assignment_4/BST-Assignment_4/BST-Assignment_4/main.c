//
//  main.c
//  BST-Assignment_4
//
//  Created by Joyce Chin on 2018/11/17.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <assert.h>
#define N 200

typedef struct treenode *treeptr;
typedef struct treenode{
    int data;
    treeptr lchild;
    treeptr rchild;
}Node;

void levelOrder(treeptr ptr){
    treeptr que[N];
    int front=-1,rear=-1;
    que[++rear]=ptr;
    while(front!=rear){
        treeptr pop=que[++front];
        printf("%d ",pop->data);
        if(pop->lchild) que[++rear]=pop->lchild;
        if(pop->rchild) que[++rear]=pop->rchild;
    }
    printf("\n");
}

void inorder(treeptr ptr){
    if(ptr){
        inorder(ptr->lchild);
        printf("%d ",ptr->data);
        inorder(ptr->rchild);
    }
}

int search(treeptr head,int num){
    while(head){
        if(num<head->data) head=head->lchild;
        else if(num>head->data) head=head->rchild;
        else if(num==head->data) return 1;
    }
    return -1;
}

treeptr delete(treeptr head,int num,int id){
    int find=1;
    if(id) find=search(head,num);
    if(find==1){
        treeptr cur=head,parent=NULL;
        while(cur){
            if(num<cur->data){
                parent=cur;
                cur=cur->lchild;
            }
            else if(num>cur->data){
                parent=cur;
                cur=cur->rchild;
            }
            else break;
        }
        treeptr tmp=cur,delnode;
        if(tmp->rchild==NULL){
            if(parent==NULL){
                delnode=head;
                head=head->lchild;
                free(delnode);
            }
            else if(parent->lchild==tmp){
                delnode=tmp;
                parent->lchild=tmp->lchild;
                free(delnode);
            }
            else if(parent->rchild==tmp){
                delnode=tmp;
                parent->rchild=tmp->lchild;
                free(delnode);
            }
        }
        else{
            tmp=tmp->rchild;
            while(tmp->lchild) tmp=tmp->lchild;
            cur->data=tmp->data;
            tmp=NULL;
        }
        printf("Number %d is deleted.\n",num);
    }
    else printf("Number not found.\n");
    return head;
}

treeptr insert(treeptr head,int num,int id){
    treeptr node=malloc(sizeof(Node));
    node->data=num;
    node->lchild=node->rchild=NULL;
    if(!head){
        head=node;
        if(id) printf("Number %d is inserted.\n",num);
    }
    else{
        treeptr ptr=head;
        while(ptr){
            if(num<ptr->data){
                if(ptr->lchild==NULL){
                    ptr->lchild=node;
                    if(id) printf("Number %d is inserted.\n",num);
                    break;
                }
                else ptr=ptr->lchild;
            }
            else if(num>ptr->data){
                if(ptr->rchild==NULL){
                    ptr->rchild=node;
                    if(id) printf("Number %d is inserted.\n",num);
                    break;
                }
                else ptr=ptr->rchild;
            }
            else if(num==ptr->data){
                free(node);
                if(id) printf("Error. Number %d exists.\n",num);
                break;
            }
        }
    }
    return head;
}

void treasureHunt(){
    printf("Please input the map file: ");
    char filename[N];
    scanf("%s",filename);
    FILE *file=fopen(filename,"r");
    assert(file!=NULL);
}

char bstMenu(){
    char choice = '\0';
    printf("(I)nsert a number.\n");
    printf("(D)elete a number.\n");
    printf("(S)earch a number.\n");
    printf("(P)rint Infix and Level Order.\n");
    printf("(R)Return\n");
    scanf("\n");
    scanf("%c",&choice);
    return choice;
}

void BST(){
    treeptr head=NULL;
    while(1){
        int num;
        char choice=bstMenu();
        if(choice=='I' || choice=='i'){
            printf("Enter a number: ");
            scanf("%d",&num);
            head=insert(head,num,1);
        }
        else if(choice=='D' || choice=='d'){
            printf("Enter a number to delete: ");
            scanf("%d",&num);
            head=delete(head,num,1);
        }
        else if(choice=='S' || choice=='s'){
            printf("Enter the element to search: ");
            scanf("%d",&num);
            int find=search(head,num);
            if(find==1) printf("BINGO! Number is found.\n");
            else printf("SORRY. Number not found.\n");
        }
        else if(choice=='P' || choice=='p'){
            printf("The tree in infix order: ");
            inorder(head);
            printf("\n");
            printf("The tree in level order: ");
            levelOrder(head);
        }
        else if(choice=='r' ||choice=='R') break;
    }
}

int mainMenu(){
    int choice;
    printf("(1)Binary Search Tree.\n");
    printf("(2)Treasure Hunter.\n");
    printf("(3)Exit.\n");
    printf("enter your choice: ");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    while(1){
        int choice=mainMenu();
        if(choice==1) BST();
        else if(choice==2) treasureHunt();
    }
}
