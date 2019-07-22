#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define N 30

int binarySearch(int data[], int l, int r, int searchnum) {
	//printf("%d\n", searchnum);
	while (r > l + 1) {
		//printf("%d %d\n",l,r);
		int mid = (l + r) / 2;
		if (searchnum < data[mid]) r = mid;
		else if (searchnum > data[mid]) l = mid;
	}
	//printf("%d %d\n", data[l], data[r]);
	if (searchnum < data[l]) return l;
	else return r;
}

void insertionSort(int data[], int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		int cur = data[i];
		if (cur > data[i - 1]) continue;
		else if (cur < data[0]) {
			for (j = i - 1; j >= 0; j--) data[j + 1] = data[j];
			data[0] = cur;
		}
		else {
			int index = binarySearch(data, 0, i - 1, cur);
			for (j = i - 1; j >= index; j--) data[j + 1] = data[j];
			data[index] = cur;
		}
		//for (i = 0; i < n; i++) printf("%d ", data[i]);
		//printf("\n");
	}
	for (i = 0; i < n; i++) printf("%d ", data[i]);
	printf("\n");
}

int main()
{
	FILE *file = fopen("test.txt", "r");
	assert(file != NULL);
	while (!feof(file)) {
		int data[N];
		int n, i;
		fscanf(file, "%d", &n);
		for (i = 0; i < n; i++) fscanf(file, "%d", &data[i]);
		insertionSort(data, n);
	}
	return 0;
}