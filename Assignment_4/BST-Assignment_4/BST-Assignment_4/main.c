//
//  main.c
//  BST-Assignment_4
//
//  Created by Joyce Chin on 2018/11/17.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 200
typedef unsigned long int ui;

typedef struct treenode *treeptr;
typedef struct treenode{
    int data;
    treeptr lchild;
    treeptr rchild;
}Node;

treeptr keystack[N]={NULL};

// print out level by level
void levelOrder(treeptr ptr){
    // using queue to manage the printing order
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

// LVR
void inorder(treeptr ptr){
    if(ptr){
        inorder(ptr->lchild);
        printf("%d ",ptr->data);
        inorder(ptr->rchild);
    }
}

// Search for node in BST
// if exist return 1 otherwise return -1
int search(treeptr head,int num){
    while(head){
        if(num<head->data) head=head->lchild;
        else if(num>head->data) head=head->rchild;
        else if(num==head->data) return 1;
    }
    return -1;
}

void findTreasure(treeptr head,int treasure,int top,int key){
    int i;
    int find=search(head,treasure);
    if(find==-1){
        printf("Adventurer only found the key.\nPath:");
        for(i=0;i<=top;i++) printf("%d->",keystack[i]->data);
        printf("Not found treasure.\n");
    }
    else{
        printf("Adventurer successfully found the treasure.\n");
        printf("Shortest path to find the treasure:\n");
        for(i=0;i<=top;i++){
            if(i==0) printf("%d",keystack[i]->data);
            else printf("->%d",keystack[i]->data);
        }
        if(treasure>=head->data && key<head->data){
            while(top--) printf("->%d",keystack[top]->data);
            if(treasure>head->data){
                head=head->rchild;
                while(treasure!=head->data){
                    printf("->%d",head->data);
                    if(treasure<head->data) head=head->lchild;
                    else if(treasure>head->data) head=head->rchild;
                }
                printf("->%d",head->data);
            }
            printf("\n");
        }
        else if(treasure<=head->data && key>head->data){
            while(top--) printf("->%d",keystack[top]->data);
            if(treasure<head->data){
                head=head->lchild;
                while(treasure!=head->data){
                    printf("->%d",head->data);
                    if(treasure<head->data) head=head->lchild;
                    else if(treasure>head->data) head=head->rchild;
                }
                printf("->%d",head->data);
            }
            printf("\n");
        }
        else if(key==head->data){
            while(treasure!=head->data){
                if(treasure<head->data) head=head->lchild;
                else if(treasure>head->data) head=head->rchild;
                printf("->%d",head->data);
            }
            printf("\n");
        }
        else{
            treeptr cur=keystack[top--];
            int check=-1;
            while(top!=-1 && check==-1){
                check=search(cur,treasure);
                if(check==1){
                    while(cur){
                        if(treasure==cur->data){
                            printf("\n");
                                break;
                            }
                            else if(treasure<cur->data) cur=cur->lchild;
                            else if(treasure>cur->data) cur=cur->rchild;
                            printf("->%d",cur->data);
                        }
                    }
                    else{
                        cur=keystack[top--];
                        printf("->%d",cur->data);
                    }
                }
            }
    }
}

int findKey(treeptr head, int key){
    int top=-1;
    while(head){
        keystack[++top]=head;
        if(key==head->data) return top;
        else if(key<head->data) head=head->lchild;
        else if(key>head->data) head=head->rchild;
    }
    return -1;
}

// Delete node
treeptr delete(treeptr head,int num,int id){
    int find=1;
    // check if the delete node exist in the BST
    if(id) find=search(head,num);
    // if exist find the location and delete it
    if(find==1){
        treeptr cur=head,parent=NULL;
        // find delete node's and its parent's location
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
        // if delete node's rchild doesn't exist
        if(tmp->rchild==NULL){
            // if the delete node is root, make it's left child to root
            if(parent==NULL){
                delnode=head;
                head=head->lchild;
                free(delnode);
            }
            // if it isn't root, link its parent to it's left child
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
        // if delete node's rchild exist
        // find the smallest in right subtree to replace the delete node
        else{
            tmp=tmp->rchild;
            parent=NULL;
            while(tmp->lchild){
                parent=tmp;
                tmp=tmp->lchild;
            }
            cur->data=tmp->data;
            // delete the prvious smallest value of replace it by it's child
            if(parent){
                delnode=tmp;
                if(tmp->rchild) parent->lchild=tmp->rchild;
                else parent->lchild=NULL;
                free(delnode);
            }
            else{
                cur->rchild=cur->rchild->rchild;
                free(tmp);
            }
        }
        printf("Number %d is deleted.\n",num);
    }
    // if delete node doesn't exist print error
    else printf("Number not found.\n");
    return head;
}

// search the bomb and delete it from BST
treeptr bombSearchDel(treeptr head,int bomb){
    treeptr que[N];
    int front=-1,rear=-1;
    que[++rear]=head;
    while(front!=rear){
        treeptr pop=que[++front];
        char str[N];
        sprintf(str,"%d",pop->data);
        ui len=strlen(str); int i;
        // every number contains bomb number in it will be deleted
        for(i=0;i<len;i++){
            if(str[i]-'0'==bomb){
                head=delete(head,pop->data,0);
                break;
            }
        }
        if(pop->lchild) que[++rear]=pop->lchild;
        if(pop->rchild) que[++rear]=pop->rchild;
    }
    return head;
}

// BST insertion
treeptr insert(treeptr head,int num,int id){
    // create a new node
    // initialize the data to the numberc entered
    treeptr node=malloc(sizeof(Node));
    node->data=num;
    node->lchild=node->rchild=NULL;
    // if bst is empty, the node will be root
    if(!head){
        head=node;
        if(id) printf("Number %d is inserted.\n",num);
    }
    // otherwise insert as the leaf node
    // find the vacant place to insert the node
    else{
        treeptr ptr=head;
        while(ptr){
            // if smaller move left
            if(num<ptr->data){
                if(ptr->lchild==NULL){
                    ptr->lchild=node;
                    if(id) printf("Number %d is inserted.\n",num);
                    break;
                }
                else ptr=ptr->lchild;
            }
            // if larger move right
            else if(num>ptr->data){
                if(ptr->rchild==NULL){
                    ptr->rchild=node;
                    if(id) printf("Number %d is inserted.\n",num);
                    break;
                }
                else ptr=ptr->rchild;
            }
            // if it exist print error
            else if(num==ptr->data){
                free(node);
                if(id) printf("Error. Number %d exists.\n",num);
                break;
            }
        }
    }
    return head;
}

// treasure hunting
void treasureHunt(){
    // read the BST map from a file
    printf("Please input the map file: ");
    char filename[N];
    scanf("%s",filename);
    FILE *file=fopen(filename,"r");
    assert(file!=NULL);
    int num;
    treeptr head=NULL;
    // construct BST using the insert method same a BST program
    while(!feof(file)){
        fscanf(file,"%d",&num);
        head=insert(head,num,0);
    }
    printf("Load file success.\n");
    int key,treasure,bomb;
    // enter key, treasure and bomb location
    printf("Please input the key location: ");
    scanf("%d",&key);
    printf("Please input the treasure location: ");
    scanf("%d",&treasure);
    printf("Please input the bomb number (0~9): ");
    scanf("%d",&bomb);
    // bomb are the node's needs to delete
    head=bombSearchDel(head,bomb);
    int top=findKey(head,key);
    if(top==-1) printf("Not found key!\n");
    else findTreasure(head,treasure,top,key);
}

// Binary Search tree menu
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

// Binary Search Tree
void BST(){
    treeptr head=NULL;
    while(1){
        int num;
        char choice=bstMenu();
        // I for insetion new node in the BST
        if(choice=='I' || choice=='i'){
            printf("Enter a number: ");
            scanf("%d",&num);
            head=insert(head,num,1);
        }
        // D for delete node
        else if(choice=='D' || choice=='d'){
            printf("Enter a number to delete: ");
            scanf("%d",&num);
            head=delete(head,num,1);
        }
        // search for specific number
        else if(choice=='S' || choice=='s'){
            printf("Enter the element to search: ");
            scanf("%d",&num);
            int find=search(head,num);
            if(find==1) printf("BINGO! Number is found.\n");
            else printf("SORRY. Number not found.\n");
        }
        // print inorder traversal and level order traversal of BST
        else if(choice=='P' || choice=='p'){
            printf("The tree in infix order: ");
            inorder(head);
            printf("\n");
            printf("The tree in level order: ");
            levelOrder(head);
        }
        // return to main menu if it's finish
        else if(choice=='r' ||choice=='R') break;
    }
}

// menu of choices
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
    // separate all the choice's of the main program
    while(1){
        int choice=mainMenu();
        if(choice==1) BST();
        else if(choice==2) treasureHunt();
        else if(choice==3) break;
        else printf("There is no such choice.\n");
    }
    return 0;
}
