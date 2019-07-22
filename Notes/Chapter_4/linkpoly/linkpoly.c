#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define N 100
typedef unsigned long int ui; 


typedef struct listnode *polyptr;
typedef struct listnode{
	int coef;
	int exp;
	polyptr link;
}Poly;

void printPoly(polyptr front){
	while(front){
		printf("coef: %d exp: %d\n",front->coef,front->exp);
		polyptr temp=front;
		front=front->link;
		free(temp);
	}
}

void addpoly(int a[],int b[],int counta,int countb){
	polyptr ptra=NULL,ptrb=NULL;
	polyptr ans=NULL,head;
	polyptr cura,curb;
	int i;
	for(i=0;i<counta;i+=2){
		polyptr node=malloc(sizeof(Poly));
		node->coef=a[i];
		node->exp=a[i+1];
		node->link=NULL;
		if(!ptra){
			ptra=node;
			cura=ptra;
		}
		else{
			ptra->link=node;
			ptra=node;
		}
	}
	for(i=0;i<countb;i+=2){
		polyptr node=malloc(sizeof(Poly));
		node->coef=b[i];
		node->exp=b[i+1];
		node->link=NULL;
		if(!ptrb){
			ptrb=node;
			curb=ptrb;
		}
		else{
			ptrb->link=node;
			ptrb=node;
		}
	}
	while(cura && curb){
		polyptr node=malloc(sizeof(Poly));
		if(cura->exp==curb->exp){
			node->exp=cura->exp;
			node->coef=cura->coef+curb->coef;
			node->link=NULL;
			polyptr tempa,tempb;
			tempa=cura;
			cura=cura->link;
			free(tempa);
			tempb=curb;
			curb=curb->link;
			free(tempb);
		}
		else if(cura->exp>curb->exp){
			node->exp=cura->exp;
			node->coef=cura->coef;
			node->link=NULL;
			polyptr temp=cura;
			cura=cura->link;
			free(temp);
		}
		else if(cura->exp<curb->exp){
			node->exp=curb->exp;
			node->coef=curb->coef;
			node->link=NULL;
			polyptr temp=curb;
			curb=curb->link;
			free(temp);
		}
		if(!ans){
			ans=node;
			head=ans;
		}
		else{
			ans->link=node;
			ans=node;
		}
	}
	while(cura){
		polyptr node=malloc(sizeof(Poly));
		node->exp=cura->exp;
		node->coef=cura->coef;
		node->link=NULL;
		polyptr temp=cura;
		cura=cura->link;
		free(temp);
		ans->link=node;
		ans=node;
	}
	while(curb){
		polyptr node=malloc(sizeof(Poly));
		node->exp=curb->exp;
		node->coef=curb->coef;
		node->link=NULL;
		polyptr temp=curb;
		curb=curb->link;
		free(temp);
		ans->link=node;
		ans=node;
	}
	printPoly(head);
}

int main(){
	FILE *file;
	file=fopen("test.txt","r");
	assert(file!=NULL);
	ui len;
	char line[N];
	int a[N],b[N];
	fgets(line,N,file);
	char *token;
	token=strtok(line," \0");
	int counta=0;
	while(token!=NULL){
		a[counta++]=atoi(token);
		token=strtok(NULL," \0");
	}
	fgets(line,N,file);
	token=strtok(line," \0");
	int countb=0;
	while(token!=NULL){
		b[countb++]=atoi(token);
		token=strtok(NULL," \0");
	}
	addpoly(a,b,counta,countb);
	return 0;
}