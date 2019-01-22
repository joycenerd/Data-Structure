# include <stdio.h>
# include <stdlib.h>
#include <time.h>


// Space Complexity

float rsum(float list[],int n){
	if(n) return rsum(list,n-1)+list[n-1];
	return 0;
}


int main() {
	clock_t start=clock();
// Dynamic Memory Allocation

	int i, *pi;
	float f, *pf;
	pi = (int *)malloc(sizeof(int));
	pf = (float *)malloc(sizeof(float));
	*pi = 1024;
	*pf = 3.1415;
	printf("integer: %d floating number: %f\n", *pi, *pf);
	free(pi);
	free(pf);
	/*if(!(pi==malloc(sizeof(int))) || !(pf==malloc(sizeof(float)))){
		fprintf(stderr, "insufficient memory\n");
		exit(EXIT_FAILURE);
	}*/

	float floatlist[7]={2.3,66,7,33.09,45.8,9,77};
	float myfloatingsum=rsum(floatlist,7);
	printf("sum= %f\n",myfloatingsum);
	clock_t stop=clock();
	double duration=((double)(stop-start)/CLOCKS_PER_SEC);
	printf("time consume: %fsecs\n",duration);
	return 0;
}
