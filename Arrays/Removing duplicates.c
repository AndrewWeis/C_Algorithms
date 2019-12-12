#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* a, int ak, int* b, int bk, int* res) {
	int aid = 0, bid = 0;

	while (aid < ak && bid < bk) {
		if (a[aid] < b[bid])
			res[aid + bid] = a[aid++];
		else 
			res[aid + bid] = b[bid++];		
	}

	while (aid < ak)
		res[aid + bid] = a[aid++];

	while (bid < bk)
		res[aid + bid] = b[bid++];
}

void mergeSort(int ary[], int size) {
	int* tmp = (int*)malloc(size * sizeof(int));
	if (size <= 1)
		return;
	const int mid = size / 2;
	mergeSort(ary, mid);
	mergeSort(ary + mid, size - mid);
	merge(ary, mid, ary + mid, size - mid, tmp);
	memcpy(ary, tmp, size * sizeof(int));
}

int arr[300002] = { 0 };
int res[300002] = { 0 };

int main() {
	int N, k = 0;
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	mergeSort(arr, N);
	arr[N] = arr[N-1] + 1;
	for (int i = 0; i < N; i++) {
		if (arr[i] < arr[i + 1])
			res[k++] = arr[i];
	}
		
	printf("%d\n", k);
	for (int i = 0; i < k; i++) {
		printf("%d\n", res[i]);
	}
	return 0;
}
