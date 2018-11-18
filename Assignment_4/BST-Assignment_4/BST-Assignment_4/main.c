//
//  main.c
//  BST-Assignment_4
//
//  Created by Joyce Chin on 2018/11/17.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct treenode *treeptr;
typedef struct treenode{
    int data;
    treeptr lchild;
    treeptr rchild;
}Node;

int search(treeptr head,int num){
    while(head){
        if(num<head->data) head=head->lchild;
        else if(num>head->data) head=head->rchild;
        else if(num==head->data) return 1;
    }
    return -1;
}

treeptr delete(treeptr head,int num){
    int find=search(head,num);
    if(find==1){
        treeptr parent=NULL;
        while(head){
            if(num<head->data){
                parent=head;
                head=head->lchild;
            }
            else if(num>head->data){
                parent=head;
                head=head->rchild;
            }
            else if(num==head->data){
                treeptr ptr;
                if(!parent){
                    ptr=head;
                    ptr=ptr->rchild;
                    if(ptr==NULL) head=head->lchild;
                    else{
                        while(ptr->lchild) ptr=ptr->lchild;
                        head->data=ptr->data;
                        ptr=NULL;
                    }
                }
            }
        }
    }
}

treeptr insert(treeptr head,int num){
    treeptr node=malloc(sizeof(Node));
    node->data=num;
    node->lchild=node->rchild=NULL;
    if(!head){
        head=node;
        printf("Number %d is inserted.\n",num);
    }
    else{
        treeptr ptr=head;
        while(ptr){
            if(num<ptr->data){
                if(ptr->lchild==NULL){
                    ptr->lchild=node;
                    printf("Number %d is inserted.\n",num);
                    break;
                }
                else ptr=ptr->lchild;
            }
            else if(num>ptr->data){
                if(ptr->rchild==NULL){
                    ptr->rchild=node;
                    printf("Number %d is inserted.\n",num);
                    break;
                }
                else ptr=ptr->rchild;
            }
            else if(num==ptr->data){
                free(node);
                printf("Error. Number %d exists.\n",num);
                break;
            }
        }
    }
    return head;
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
            head=insert(head,num);
        }
        else if(choice=='D' || choice=='d'){
            printf("Enter a number to delete: ");
            scanf("%d",&num);
            head=delete(head,num);
        }
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
    }
}
