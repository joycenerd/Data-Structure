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

int main()
{
	char stack[N];
	int top=-1;
	int instack[]={12,12,13,13,0,19};
	int outstack[]={12,12,13,13,20,19};
	char line[N];
	scanf("%s",line);
	ui len=strlen(line);
	char revline[N];
	int i;
	for(i=0;i<len;i++){
		if(line[len-i-1]=='(') line[len-i-1]=')';
		else if(line[len-i-1]==')') line[len-i-1]='(';
		else  revline[i]=line[len-i-1];
	}
	char output[N];
	int cur=0;
	for(i=0;i<len;i++){
		if(isdigit(revline[i])){
			strncpy(output+cur,revline+i,1);
			cur++;
		}
		else{
			Operator operator=distinguish(revline[i]);
			Operator inoper;
			if(top==-1) stack[++top]=revline[i];
			else{
				inoper=distinguish(stack[top]);
				if(revline[i]==')'){
					while(stack[top]!='('){
						strncpy(output+cur,stack+top,1);
						cur++;top--;
					}
					top--;
				}
				else if(outstack[operator]>=instack[inoper]) stack[++top]=revline[i];
				else{
					while(1){
						inoper=distinguish(stack[top]);
						if(outstack[operator]<instack[inoper]){
							strncpy(output+cur,stack+top,1);
							top--; cur++;
						}
						else break;
					}
					stack[++top]=revline[i];
				}
			}
		}
	}
	for(i=top;i>-1;i--){
		strncpy(output+cur,stack+i,1);
		cur++;
	}
	len=strlen(output);
	for(i=len-1;i>=0;i--) printf("%c",output[i]);
	printf("\n");
	return 0;
}