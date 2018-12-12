//
//  main.c
//  Sorting-Assignment_6
//
//  Created by Joyce Chin on 2018/12/13.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 200
#define MAX_ARRAY 1000
typedef unsigned long int ui;


void quicksort(){
    
}

void insertionSort(){
    
}

void bubbleSort(){
    
}

void selectionSort(FILE *file){
    
}

int menu(){
    int choice;
    printf("(1)Do sorting\n");
    printf("(0)Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    while(1){
        int choice=menu();
        if(choice==0) break;
        else if(choice==1){
            printf("Enter your file to do sorting: ");
            char str[N],filename[N]={"\0"};
            scanf("\n");
            fgets(str,N,stdin);
            ui len=strlen(str);
            int i;
            for(i=0;i<len-1;i++) filename[i]=str[i];
            FILE *file=fopen(filename,"r");
            assert(file!=NULL);
            int arrlength=0;
            int arr[MAX_ARRAY];
            while(!feof(file)) fscanf(file,"%d",&arr[arrlength++]);
            printf("Input array:\n");
            for(i=0;i<arrlength;i++){
                if(i==arrlength-1) printf("%3d\n",arr[i]);
                else printf("%3d ",arr[i]);
            }
            selectionSort(file);
        }
    }
}
