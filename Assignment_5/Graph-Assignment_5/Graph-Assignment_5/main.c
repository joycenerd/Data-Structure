//
//  main.c
//  Graph-Assignment_5
//
//  Created by Joyce Chin on 2018/12/2.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>


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
    int choice=mainMenu();
    printf("%d\n",choice);
}
