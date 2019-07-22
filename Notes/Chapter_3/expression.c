#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_SIZE 200
typedef unsigned long int ui;

int stackRec(char *string) {
	int stack[MAX_SIZE];
	int top = -1;
	int i;
	ui len = strlen(string) - 1;
	printf("%lu\n",len);
	for (i = 0; i < len; i++) {
		if (isdigit(string[i])) {
			stack[++top] = string[i] - '0';
		}
		else {
			int oper1 = stack[top--];
			int oper2 = stack[top--];
			int res;
			if (string[i] == '+') res = oper1 + oper2;
			else if (string[i] == '-') res = oper2 - oper1;
			else if (string[i] == '*') res = oper2 * oper1;
			else if (string[i] == '/') res = oper2 / oper1;
			else if (string[i] == '%') res = oper2 % oper1;
			stack[++top] = res;
		}
	}
	return stack[0];
}

int main()
{
	char line[MAX_SIZE];
	fgets(line, MAX_SIZE, stdin);
	int ans = stackRec(line);
	printf("%d\n", ans);
	return 0;
}