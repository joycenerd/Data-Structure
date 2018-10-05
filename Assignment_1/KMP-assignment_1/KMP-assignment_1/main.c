//
//  main.c
//  KMP-assignment_1
//
//  Created by Joyce Chin on 2018/9/29.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define N 200
typedef unsigned long int ui;


// define my structure to store my data
typedef struct{
    char name[N];
    int index;
}Data;

// delete the pattern in the mainstring if matches
char *deleteString(char *string, int index, ui delsize){
    ui size=strlen(string);
    char *newstring=malloc(size*sizeof(char));
    strncpy(newstring,string,index);
    strcpy(newstring+index,string+index+delsize);
    return newstring;
}

// string matching using failure function to speed up the matching process
int KMPmatcher(char *string, char *pattern, int failure[]){
    ui stringlen=strlen(string);
    ui patlen=strlen(pattern);
    int strindex=0,patindex=0;
    while(strindex<stringlen && patindex<patlen){
        if(string[strindex]==pattern[patindex]){
            strindex++;patindex++;
        }
        else if(patindex==0) strindex++;
        else patindex=failure[patindex-1];
    }
    // if match return the first index of the pattern in the mainstring, else return -1 as not found
    if(patindex==patlen){
        int location=strindex-(int)patlen;
        return location;
    }
    else return -1;
}

// failure function
int *failFunc(char *pattern,ui len){
    int i,j;
    static int fail[N];
    fail[0]=0;
    char head=pattern[0];
    for(i=1;i<len;i++){
        if(fail[i-1]==0){
            if(pattern[i]==head) fail[i]=1;
            else fail[i]=0;
        }
        else{
            j=i-1;
            int index=0;
            while(j>=1){
                if(fail[j]==1){
                    index=j;
                    break;
                }
                j--;
            }
            int sectionlen=i-index+1;
            if(strncmp(pattern,pattern+index,sectionlen)==0) fail[i]=sectionlen;
            else{
                int flag=0;
                for(j=index+1;j<i;j++){
                    if(pattern[j]==head){
                        sectionlen=i-j+1;
                        if(strncmp(pattern,pattern+j,sectionlen)==0){
                            fail[i]=sectionlen;
                            flag=1;
                            break;
                        }
                    }
                }
                if(flag==0){
                    if(pattern[i]==head) fail[i]=1;
                    else fail[i]=0;
                }
            }
        }
    }
    return fail;
}

// Pop Data include find the pattern's failure function, string matching, and output the rest of mainstring after deleting the pattern from the mainstring
void popData(char *string){
    printf("enter your searching pattern: ");
    char pattern[N];
    // input the searching pattern
    scanf("%s",pattern);
    ui patlen=strlen(pattern);
    int *lsp;
    // finding the pattern's failure function
    lsp=failFunc(pattern, patlen);
    printf("lsp= [");
    for(int i=0;i<patlen;i++){
        if (i==0) printf("%d",*(lsp+i));
        else printf(", %d",*(lsp+i));
    }
    printf("]\n");
    // matching the mainstring and pattern
    int index=KMPmatcher(string, pattern, lsp);
    char *remainstr = NULL;
    // if match output the string after deleting the pattern from the mainstring, else print out the complete mainstring
    if(index==-1) remainstr=deleteString(string,0,0);
    else remainstr=deleteString(string,index,patlen);
    printf("the remaining string is: %s\n",remainstr);
}

// after putting my data into sturcture, consturct the mainstring according to name string and the index it's inserting in
char *constructString(Data *data,int howmany){
    printf("\n");
    int i;
    int strsize=N;
    char *mainstring=malloc(strsize*sizeof(char));
    int insertindex=0,charcount=0;
    for(i=0;i<howmany;i++){
        printf("name: %s\n",data[i].name);
        printf("next position: %d\n",data[i].index);
        ui len=strlen(data[i].name);
        if((charcount+len)>=strsize){
            strsize*=2;
            char *reallstr=realloc(mainstring,strsize*sizeof(char));
            mainstring=reallstr;
        }
        // string insertion include string concatenation and I choose to use string copy.
        //original string + insetion string(from some index) + the rest of original string
        char *tempstr=malloc(strsize*sizeof(char));
        strncpy(tempstr,mainstring,strsize);
        strncpy(mainstring, tempstr, insertindex);
        strncpy(mainstring+insertindex,data[i].name,len);
        strcpy(mainstring+insertindex+len, tempstr+insertindex);
        printf("mainstring after insertion: %s\n",mainstring);
        printf("========================================================\n");
        charcount+=len;
        insertindex=data[i].index;
    }
    return mainstring;
}

// doing sturcture memory realloction
Data memory(Data *mydata,int size){
    size*=2;
    Data *reallstruct=realloc(mydata,size*sizeof(Data));
    mydata=reallstruct;
    return *mydata;
}

// choice 2 input data using command line
char *inputData(){
    char inputname[N],yn[N]="0";
    int size=1;
    int inputindex;
    int counter=0;
    // structure for my datasets
    Data *data=malloc(size*sizeof(Data));
    while(1){
        printf("enter the name: ");
        scanf("%s",inputname);
        // if input is 0 then I know input come to an end
        if(strncmp(inputname,yn,1)==0) break;
        printf("enter the index: ");
        scanf("%d",&inputindex);
        // write my input data to my structure
        if(counter+1==size) *data=memory(data,size);
        strncpy(data[counter].name,inputname,N);
        inputname[0]='\0';
        data[counter].index=inputindex;
        counter++;
    }
    char *string=constructString(data,counter);
    return string;
}

// every line of csv file contains name and index, and this function is separate name and index and put into my structure
Data splitLine(char *string,Data *mydata,int cur){
    char *token[2];
    token[0]=strtok(string,",\0");
    if(token[0]!=NULL) token[1]=strtok(NULL,",\0");
    strcpy(mydata[cur].name,token[0]);
    mydata[cur].index=atoi(token[1]);
    return *mydata;
}

// choice 1 read csv file
char *readfile(){
    printf("enter your filename and path: ");
    char filename[N];
    scanf("%s",filename);
    FILE *file;
    file=fopen(filename,"r");
    assert(file!=NULL);
    char line[N];
    int structsize=1;
    int counting=0;
    // the datasets in csv file will go into the structure, using malloc and realloc to save memory
    Data *data=malloc(structsize*sizeof(Data));
    while(fgets(line,N,file)!=NULL){
        if(counting==structsize) *data=memory(data,structsize);
        // parsing my string in my file
        *data=splitLine(line,data,counting);
        counting++;
    }
    // construct mainstring after putting all my data into my structure
    char *mymainstring=constructString(data,counting);
    return mymainstring;
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
    // choose what you want to do with the program
    while(1){
        int choice=menu();
        // choice 1 is to read the data from a file and do things with the data
        if(choice==1){
            char *maintring=readfile();
            while(1){
                printf("\n");
                choice=menu();
                if(choice==1) printf("You must first exit to input other data\n");
                else if(choice==2) printf("You must first exit to input other data\n");
                else if(choice==3) popData(maintring);
                else if(choice==4){
                    break;
                }
                else printf("There is no this choice\n");
            }
        }
        // choice 2 is to input data from the command line
        else if(choice==2){
            char *maintring=inputData();
            while(1){
                printf("\n");
                choice=menu();
                if(choice==1) printf("You must first exit to input other data\n");
                else if(choice==2) printf("You must first exit to input other data\n");
                else if(choice==3) popData(maintring);
                else if(choice==4){
                    break;
                }
                else printf("There is no this choice\n");
            }
        }
        else if(choice==3) printf("You haven't input any data yet\n");
        else if(choice==4) break;
        else printf("There is no this choice\n");
    }
    return 0;
}
