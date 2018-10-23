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
        
    }
}
