#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 200
typedef unsigned long int ui;


typedef enum{add=0,sub,multi,div,lparen,rparen} Operator;

Operator distinguish(char symbol){
	switch(symbol){
		case '+': return add;
		case '-':return sub;
		case '*': return multi;
		case '/': return div;
		case '(': return lparen;
		case ')': return rparen; 
	}
}

int main(){
	char stack[N];
	int top=-1;
	int instack[]={12,12,13,13,0,19};
	int outstack[]={12,12,13,13,20,19};
	char line[N];
	scanf("%s",line);
	int i;
	ui len=strlen(line);
	for(i=0;i<len;i++){
		if(isdigit(line[i])) printf("%c",line[i]);
		else{
			Operator operator=distinguish(line[i]);
			Operator inoper;
			if(top==-1) stack[++top]=line[i];
			else{
				inoper=distinguish(stack[top]);
				if(line[i]==')'){
					while(stack[top]!='(') printf("%c",stack[top--]);
					top--;
				}
				else if(outstack[operator]>instack[inoper]) stack[++top]=line[i];
				else{
					while(1){
						inoper=distinguish(stack[top]);
						if(outstack[operator]<=instack[inoper]) printf("%c",stack[top--]);
						else break;
					}
					stack[++top]=line[i];
				}
			}
		}
		int j;
		//for(j=top;j>-1;j--) printf("%c",stack[j]);
		//printf("\n");
	}
	for(i=top;i>-1;i--) printf("%c",stack[i]);
	printf("\n");
	return 0;
}