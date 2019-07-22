#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define N 200
typedef unsigned long int ui;


typedef struct listnode *polyptr;
typedef struct listnode{
	int coef;
	int exp;
	polyptr link;
}CircularPoly;

polyptr shiftandfree(polyptr poly){
	polyptr temp=poly;
	poly=poly->link;
	free(temp);
	return poly;
}

void printPoly(polyptr poly){
	polyptr head=poly;
	poly=poly->link;
	while(poly!=head){
		printf("coef: %d exp: %d\n",poly->coef,poly->exp);
		poly=shiftandfree(poly);
	}
	polyptr temp=head;
	head=NULL;
	free(temp);
}

int compareExp(polyptr a, polyptr b){
	if(a->exp==b->exp) return 1;
	else if(a->exp>b->exp) return 2;
	else if(a->exp<b->exp) return 3;
}

polyptr addpoly(polyptr a,polyptr b){
	polyptr head=malloc(sizeof(CircularPoly));
	head->exp=-1;
	head->link=head;
	polyptr ans=head;
	polyptr headA=a;
	polyptr headB=b;
	a=a->link;
	b=b->link;
	while(a!=headA && b!=headB){
		polyptr node=malloc(sizeof(CircularPoly));
		int cmp=compareExp(a,b);
		if(cmp==1){
			node->coef=a->coef+b->coef;
			node->exp=a->exp;
			a=shiftandfree(a);
			b=shiftandfree(b);
		}
		else if(cmp==2){
			node->coef=a->coef;
			node->exp=a->exp;
			a=shiftandfree(a);
		}
		else if(cmp==3){
			node->coef=b->coef;
			node->exp=b->exp;
			b=shiftandfree(b);
		}
		ans->link=node;
		node->link=head;
		ans=node;
	}
	while(a!=headA){
		polyptr node=malloc(sizeof(CircularPoly));
		node->coef=a->coef;
		node->exp=a->exp;
		a=shiftandfree(a);
		ans->link=node;
		node->link=head;
		ans=node;
	}
	while(b!=headB){
		polyptr node=malloc(sizeof(CircularPoly));
		node->coef=b->coef;
		node->exp=b->exp;
		b=shiftandfree(b);
		ans->link=node;
		node->link=head;
		ans=node;
	}
	return head;
}

polyptr constructpoly(int arr[],int count){
	polyptr poly;
	polyptr head=malloc(sizeof(CircularPoly));
	head->exp=-1;
	head->link=head;
	poly=head;
	int i;
	for(i=0;i<count;i+=2){
		polyptr node=malloc(sizeof(CircularPoly));
		node->coef=arr[i];
		node->exp=arr[i+1];
		poly->link=node;
		poly=node;
		node->link=head;
	}
	return head;
}

int main()
{
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
	int i;
	polyptr polyA=constructpoly(a,counta);
	polyptr polyB=constructpoly(b,countb);
	polyptr ans=addpoly(polyA,polyB);
	printPoly(ans);

}