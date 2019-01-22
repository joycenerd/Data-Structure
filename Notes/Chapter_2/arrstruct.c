#include <stdio.h>
#include <stdlib.h>


int **makeMatrix(int row,int col){
	int **x;
	int i;
	x=malloc(row*sizeof(*x));
	for(i=0;i<row;i++) x[i]=malloc(col*sizeof(**x));
	return x;
}

typedef struct linkList{
	char data;
	struct linkList *link;
}LinkList;

int main()
{
	int n;
	scanf("%d", &n);
	//printf("%d\n",n);
	if (n < 1) {
		fprintf(stderr, "Improper size value\n");
		exit(EXIT_FAILURE);
	}
	int *ptr;
	ptr=(int *)malloc(n * sizeof(int));
	int i;
	for(i=0;i<n;i++) *(ptr+i)=rand()%100+1;
	printf("%d\n",n);
	for(i=0;i<n;i++) printf("%d ",ptr[i]);
	printf("\n");

// two-dimesional array
	int **mymatrix;
	mymatrix=makeMatrix(5,10);
	int j;
	for(i=0;i<5;i++){
		for(j=0;j<10;j++) mymatrix[i][j]=0;
	}
	for(i=0;i<5;i++){
		for(j=0;j<10;j++){
			if(j==9) printf("%d\n",mymatrix[i][j]);
			else printf("%d ",mymatrix[i][j]);
		}
	}

	// Self-Referential Structures
	LinkList item1,item2,item3;
	item1.data='a';
	item2.data='b';
	item3.data='c';
	item1.link=&item2;
	item2.link=&item3;
	printf("%c\n",item1.data);
	if(item1.link==NULL) printf("Link error");
	return 0;
}
