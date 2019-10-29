#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int bitword;

bitword bwarr[312500]; 

void bitsetZero(bitword* arr, int num) { 
	int words = (num + 8 * sizeof(bitword) - 1) / (8 * sizeof(bitword));
	for (int i = 0; i < words; i++) {
		arr[i] = 0;
	}
}

int bitsetGet(const bitword* arr, int idx) {
	int byteId = idx / (8 * sizeof(bitword));
	int bitId = idx % (8 * sizeof(bitword));
	bitword byteCur = arr[byteId];
	int ans = byteCur & (1<<bitId);
	if (ans != 0) {
		ans = 1;
	}
	return ans;
}
void bitsetSet(bitword* arr, int idx, int newval) {
	int byteId = idx / (8 * sizeof(bitword));
	int bitsId = idx % (8 * sizeof(bitword));
	bitword byteCur = arr[byteId];
	int ans = byteCur & (1<<bitsId);
	if (ans != 0) {
		ans = 1;
	}
	if (ans != newval) {
		arr[byteId] ^= (1<<bitsId);
	}
}
int bitsetAny(const bitword* arr, int L, int R) {
	int LbyteId = L / (8 * sizeof(bitword));
	int LbitsId = L % (8 * sizeof(bitword));
	int RbyteId = R / (8 * sizeof(bitword));
	int RbitseId = R % (8 * sizeof(bitword));
	if (LbyteId == RbyteId) {
		for (int i = LbitsId; i < RbitseId; i++) {
			int ans = arr[LbyteId] & (1<<i);
			if (ans != 0)
				return 1;
		}
		return 0;
	}
	else {
		for (int i = LbitsId; i < (8 * sizeof(bitword)); i++) {
			int ans = arr[LbyteId] & (1<<i);
			if (ans != 0)
				return 1;
		}
		for (int i = LbyteId + 1; i < RbyteId; i++) {
			if (arr[i] != 0)
				return 1;
		}
		for (int i = 0; i < RbitseId; i++) {
			int ans = arr[RbyteId] & (1<<i);
			if (ans != 0)
				return 1;
		}
		return 0;
	}
}
int main() {
	int N, t, idx, num, newval, L, R;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &t);
		if (t == 0) {
			scanf("%d", &num);
			bitsetZero(bwarr, num);
		}
		if (t == 1) {
			scanf("%d", &idx);
			printf("%d\n", bitsetGet(bwarr, idx));
		}
		if (t == 2) {
			scanf("%d %d", &idx, &newval);
			bitsetSet(bwarr, idx, newval);
		}
		if (t == 3) {
			scanf("%d %d", &L, &R);
			int res = bitsetAny(bwarr, L, R);
			if (res == 1)
				printf("some\n");
			else
				printf("none\n");
		}
	}
	return 0;
}

// 0 - обнуляет массив битов
// 1 - берет значение бита по индексу
// 2 - меняет значение бита по индексу
// 3 - смотрит есть в диапазоне хоть один бит = 1
