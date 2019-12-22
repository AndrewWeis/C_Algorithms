#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* a, int ak, int* b, int bk, int* res) {
	int aid = 0, bid = 0;
	while (aid < ak && bid < bk) {
		if (a[aid] < b[bid]) {
			res[aid + bid] = a[aid];
			aid++;
		}
		else {
			res[aid + bid] = b[bid];
			bid++;
		}
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

int arr[500001] = { 0 };

int main() {
	int N;
	FILE* input = fopen("input.bin", "rb");
	FILE* output = fopen("output.bin", "wb");

	fread(&N, sizeof(int), 1, input);

	for (int i = 0; i < N; i++) {
		fread(&arr[i], sizeof(int), 1, input);
	}

	mergeSort(arr, N);

	for (int i = 0; i < N; i++)
		fwrite(&arr[i], sizeof(int), 1, output);

	fclose(input);
	fclose(output);
	return 0;
}
