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

int swap2(int arr[],int a,int b){
    int tmp=arr[a];
    arr[a]=arr[b];
    arr[b]=tmp;
    return *arr;
}

void quickSort(int arr[],int l,int r,int n){
    int pivot,i,j,k;
    if(l<r){
        i=l;j=r+1;pivot=l;
        do{
            do i++; while(arr[i]<arr[pivot]);
            do j--; while(arr[j]>arr[pivot]);
            if(i<j) *arr=swap2(arr,i,j);
        }while(i<j);
        *arr=swap2(arr,pivot,j);
        for(k=0;k<n;k++){
            if(k==n-1) printf("%3d\n",arr[k]);
            else printf("%3d ",arr[k]);
        }
        quickSort(arr, l, j-1, n);
        quickSort(arr, j+1, r, n);
    }
}

int binarySearch(int data[], int l, int r, int searchnum) {
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (searchnum < data[mid]) r = mid;
        else if (searchnum > data[mid]) l = mid;
    }
    if (searchnum < data[l]) return l;
    else return r;
}

void insertionSort(int arr[],int n){
    printf("insertion sort:\n");
    int i,j,k;
    for (i = 1; i < n; i++) {
        for(k=0;k<n;k++){
            if(k==n-1) printf("%3d\n",arr[k]);
            else printf("%3d ",arr[k]);
        }
        int cur = arr[i];
        if (cur > arr[i - 1]) continue;
        else if (cur < arr[0]) {
            for (j = i - 1; j >= 0; j--) arr[j + 1] = arr[j];
            arr[0] = cur;
        }
        else {
            int index = binarySearch(arr, 0, i - 1, cur);
            for (j = i - 1; j >= index; j--) arr[j + 1] = arr[j];
            arr[index] = cur;
        }
    }
    for(k=0;k<n;k++){
        if(k==n-1) printf("%3d\n",arr[k]);
        else printf("%3d ",arr[k]);
    }
    printf("Total step: %d\n\n",n);
}

void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void bubbleSort(int arr[],int n){
    printf("bubble sort:\n");
    int i,j,k;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]) swap(&arr[j],&arr[j+1]);
        }
        for(k=0;k<n;k++){
            if(k==n-1) printf("%3d\n",arr[k]);
            else printf("%3d ",arr[k]);
        }
    }
    printf("Total step: %d\n\n",n-1);
}

void selectionSort(int arr[], int n){
    printf("selection sort:\n");
    int i,j,k;
    for(i=0;i<n-1;i++){
        int mini=i;
        for(j=i+1;j<n;j++){
            if(arr[j]<arr[mini]) mini=j;
        }
        swap(&arr[i],&arr[mini]);
        for(k=0;k<n;k++){
            if(k==n-1) printf("%3d\n",arr[k]);
            else printf("%3d ",arr[k]);
        }
    }
    printf("Total step: %d\n\n",n);
}

// main menu of the program
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
        // choose what to do in this program
        int choice=menu();
        // exit program if enter 0
        if(choice==0) break;
        else if(choice==1){
            // enter filename
            printf("Enter your file to do sorting: ");
            char str[N],filename[N]={"\0"};
            scanf("\n");
            fgets(str,N,stdin);
            ui len=strlen(str);
            int i;
            for(i=0;i<len-1;i++) filename[i]=str[i];
            FILE *file=fopen(filename,"r");
            assert(file!=NULL);
            // define array for the input data
            int arrlength=0;
            int arr[MAX_ARRAY];
            while(!feof(file)) fscanf(file,"%d",&arr[arrlength++]);
            // print the original data
            printf("Input array:\n");
            for(i=0;i<arrlength;i++){
                if(i==arrlength-1) printf("%3d\n\n",arr[i]);
                else printf("%3d ",arr[i]);
            }
            // doing swap will change the memory of the array
            // before calling any sorting array first copy the original data
            int selectarr[MAX_ARRAY],bubblearr[MAX_ARRAY],insertarr[MAX_ARRAY],quickarr[MAX_ARRAY];
            for(i=0;i<arrlength;i++){
                selectarr[i]=bubblearr[i]=insertarr[i]=quickarr[i]=arr[i];
            }
            // calling sorting algorithm
            selectionSort(selectarr,arrlength);
            bubbleSort(bubblearr,arrlength);
            insertionSort(insertarr,arrlength);
            printf("quick sort:\n");
            quickSort(quickarr, 0, arrlength-1,arrlength);
        }
    }
    return 0;
}
