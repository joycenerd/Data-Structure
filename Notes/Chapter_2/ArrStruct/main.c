//
//  main.c
//  ArrStruct
//
//  Created by Joyce Chin on 2018/9/22.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200
typedef unsigned long int ui;


int main()
{
    char string[200];
    strncpy(string,"ababbabababb",N);
    ui lens=strlen(string);
     int i,j;
    int failure[N];
    failure[0]=0;
    char head=string[0];
    for(i=1;i<lens;i++){
        if(failure[i-1]==0){
            if(string[i]==head) failure[i]=1;
            else failure[i]=0;
        }
        else{
            j=i-1;
            int index = 0;
            int find=0;
            while(j>1){
                if(failure[j]==1 && j+failure[i-1]==i){
                    index=j;
                    find=1;
                    break;
                }
                j--;
            }
            if(find==0){
                j=i-1;
                while(j>0){
                    if(string[j]==head){
                        index=j;
                        break;
                    }
                    j--;
                }
            }
            int count;
            count=i-index+1;
            if(strncmp(string+0,string+index,count)==0) failure[i]=count;
            else{
                int flag=0;
                for(j=index+1;j<i;j++){
                    if(string[j]==head){
                        count=i-j+1;
                        if(strncmp(string,string+j,count)==0){
                            failure[i]=count;
                            flag=1;
                            break;
                        }
                    }
                }
                if(flag==0){
                    if(string[i]==head) failure[i]=1;
                    else failure[i]=0;
                }
            }
        }
    }
    char test[N];
    strncpy(test,"ababbbababbabababbaa",N);
    ui lent=strlen(test);
    i=0;j=0;
    while(i<lent && j<lens){
        if(test[i]==string[j]){
            i++;j++;
        }
        else if(j==0) i++;
        else{
            i+=failure[j-1]+1;
            j=0;
        }
    }
    if(j==lens) printf("%lu\n",i-lens);
    else printf("-1\n");
    return 0;
}
