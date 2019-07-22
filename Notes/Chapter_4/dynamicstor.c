#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i,*pi;
	float *pf;
	i=1024;
	pi=(int *)malloc(sizeof(int));
	pi=&i;
	pf=(float *)malloc(sizeof(float));
	*pf=3.1415;
	printf("%d %f\n",*pi,*pf);

	free(pf);
	return 0;
}