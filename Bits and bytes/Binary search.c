#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int arr[100001] = { 0 };
int prevAns = 0;
int search(int Q, int size, int x) {
	
	int L = 0, R = size - 1, m = 0;
	x += prevAns;
	int max = -1;
	int search = -1;
	while (L <= R) {
		m = (L + R) / 2;
		if (x == arr[m]) {
			if (m > max) {
				search = m;
				max = search;
			}	
		}
		if (x < arr[m])
			R = m - 1;
		else
			L = m + 1;
	}
	if ((search == -1) && (max == -1)) 
		m = -1;
	else
		m = search;

		prevAns = m;
	return m;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int N = 0, Q = 0, x = 0, res = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d ", &arr[i]);
	scanf("%d", &Q);
	
	for (int i = 1; i <= Q; i++) {
		scanf("%d\n", &x);
	res = search(Q, N, x);
	printf("%d\n", res);
	}

	return 0;
}
