//
//  main.c
//  intro
//
//  Created by Joyce Chin on 2018/9/11.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define MIN 10000000

// Selection Sort

void swap(int *num1, int *num2){
    int temp=*num1;
    *num1=*num2;
    *num2=temp;
}

void charSwap(char *char1, char *char2){
    char temp;
    temp=*char1;
    *char1=*char2;
    *char2=temp;
}

int *sort(int list[],int number){
    int i=0;
    while(i<number){
        int j;
        int min=MIN;
        int min_index = 0;
        for(j=i+1;j<number;j++){
            if(list[j]<min){
                min=list[j];
                min_index=j;
        }
        if(list[min_index]<list[i]) swap(&list[min_index],&list[i]);
        }
        i++;
    }
    return list;
}

// Binary Search

int compare(int x,int y){
    if(x<y) return -1;
    else if(x==y) return 0;
    else return 1;
}

int BinarySearch(int list[],int target,int count){
    int left=0;
    int right=count-1;
    while(left<=right){
        int middle=(left+right)/2;
        switch(compare(list[middle],target)){
            case -1: left=middle+1;
                break;
            case 0: return middle;
            case 1: right=middle-1;
        }
    }
    if(list[left]==target) return left;
    else return -1;
}

// Selection Problem I

int SelectionI(int list[],int count,int k){
    return list[count-k];
}

// Selection Problem II

int SelectionII(int list[],int count,int k){
    int i;
    int temparray[k];
    for(i=0;i<k;i++) temparray[i]=list[i];
    int *sortarray;
    sortarray=sort(temparray,k);
    int reversearr[k];
    for(i=0;i<k;i++) reversearr[i] = *(sortarray+k-i-1);
    for(i=k;i<count;i++){
        if(list[i]<reversearr[k-1]) continue;
        int j;
        for(j=0;j<k;j++){
            int flag=0;
            if(list[i]>reversearr[j]){
                int temp=k-1;
                while(temp>j){
                    reversearr[temp]=reversearr[temp-1];
                    temp--;
                }
                reversearr[j]=list[i];
                flag=1;
            }
            if(flag) break;
        }
    }
    return reversearr[k-1];
}

// Recursive Multiplication

int RecurMulti(int a, int b){
    if(b==1) return a;
    else return RecurMulti(a, b-1)+a;
}

//Recursive Permutation

void RecurPerm(char *string,int left,int right){
    int i;
    if(left==right) printf("%s\n",string);
    else{
        for(i=left;i<=right;i++){
            charSwap(string+left, string+i);
            RecurPerm(string, left+1, right);
            charSwap(string+left, string+i);
        }
    }
}

int main()
{
    int list[5]={5,4,9,8,5};
    int *sortinglist;
    sortinglist=sort(list,5);
    int i;
    for(i=0;i<5;i++){
        if(i==0) printf("%d",*(sortinglist+i));
        else printf(" %d",*(sortinglist+i));
    }
    printf("\n");
    
    int index=BinarySearch(sortinglist, 8, 5);
    if(index==-1) printf("Target Not Found\n");
    else printf("%d\n",index);
    
    int select1=SelectionI(sortinglist, 5, 2);
    printf("%d\n",select1);
    
    int array[7]={37,5959,22,59,30,4569,45};
    int select2=SelectionII(array,7,4);
    printf("%d\n",select2);
    
    int multiresult=RecurMulti(34, 5);
    printf("%d\n",multiresult);
    
    char string[]="abc";
    int length=strlen(string);
    RecurPerm(string, 0, length-1);
    
}
