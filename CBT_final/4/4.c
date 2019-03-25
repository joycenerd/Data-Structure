#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010


FILE *fout;

int Swap(int arr[], int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
	return *arr;
}

void quicksort(int arr[], int n, int l, int r) {
	if (l < r) {
		int k;
		int i = l, j = r + 1, pivot = l;
		do {
			do i++; while (arr[i] < arr[pivot]);
			do j--; while (arr[j] > arr[pivot]);
			if (i < j) {
				*arr = Swap(arr, i, j);
				for ( k = 0; k < n; k++) fprintf(fout,"%d ", arr[k]);
				fprintf(fout,"\n");
			}
		} while (i < j);
		if (j != pivot) {
			*arr = Swap(arr, j, pivot);
			for (k = 0; k < n; k++) fprintf(fout,"%d ", arr[k]);
			fprintf(fout,"\n");
		}
		quicksort(arr, n, l, j - 1);
		quicksort(arr, n, j + 1, r);
	}
}

int main()
{
	FILE *fin = fopen("4input_3.txt", "r");
	fout=fopen("4output.txt","w");
	assert(fin != NULL);
	char l[N];
	fgets(l, N, fin);
	char *token = strtok(l, " \0");
	int n = 0;
	int arr[N];
	while (token != NULL) {
		arr[n++] = atoi(token);
		token = strtok(NULL, " \0");
	}
	quicksort(arr, n, 0, n - 1);
}