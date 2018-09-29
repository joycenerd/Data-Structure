//
//  main.c
//  KMP-assignment_1
//
//  Created by Joyce Chin on 2018/9/29.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#define N 200

void readfile(){
    printf("enter your filename and path: ");
    char filename[N];
    scanf("%s",filename);
    FILE *file;
    file=fopen(filename,"r");
    assert(file!=NULL);
}


int menu()
{
    printf("What do you want to do?\n");
    printf("(1) read data from a file\n");
    printf("(2) write your own data\n");
    printf("(3) pop you data\n");
    printf("(4) exit\n");
    printf("please enter your choice: ");
    int choice;
    scanf("%d",&choice);
    return choice;
}

int main()
{
    int choice=menu();
    if(choice==1){
        readfile();
    }
    
}
