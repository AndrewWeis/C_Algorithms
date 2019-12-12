#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int arr[500000];

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

void mergeSort(int* arr, int size) {
	int* tmp = (int*)malloc(size * sizeof(int));
	if (size <= 1) return;
	const int mid = size / 2;
	mergeSort(arr, mid);
	mergeSort(arr + mid, size - mid);
	merge(arr, mid, arr + mid, size - mid, tmp);
	memcpy(arr, tmp, size * sizeof(int));
	free(tmp);
}

int partition(int* arr, int n, int pivot, int* a, int* b) {
	int sameP = 0, aL = 0, aR = 0, k = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] < pivot || (arr[i] == pivot && sameP == 0)) {
			a[aL++] = arr[i];

			if (arr[i] == pivot)
				sameP = 1;
			k++;
		}
		else if (arr[i] > pivot || (arr[i] == pivot && sameP == 1)) {
			b[aR++] = arr[i];
			if (arr[i] == pivot)
				sameP = 0;
		}
	}
	return k;
}

void qSort(int* arr, int size) {
	int* a = (int*)malloc(size * sizeof(int));
	int* b = (int*)malloc(size * sizeof(int));

	int max = -2147483647;
	int min = 2147483647;
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) max = arr[i];
		if (arr[i] < min) min = arr[i];
	}

	int pivot = rand() % (max - min + 1) + min;

	int k = partition(arr, size, pivot, a, b);
	mergeSort(a, k);
	mergeSort(b, size - k);
	merge(a, k, b, size - k, arr);
}

int main() {
	FILE* input = fopen("input.bin", "rb");
	FILE* output = fopen("output.bin", "wb");

	int N;

	fread(&N, sizeof(int), 1, input);
	fread(&arr, sizeof(int), N, input);

	qSort(arr, N);

	for (int i = 0; i < N; i++) {
		fwrite(&arr[i], sizeof(int), 1, output);
	}

	fclose(input);
	fclose(output);
	return 0;
}
