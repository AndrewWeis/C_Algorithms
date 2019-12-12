#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int mat[500][500];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int N;
	char p;
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		scanf("%c", &p);
		for (int j = 0; j < N; j++) {
			scanf("%c", &p);

			if (p == '0')
				mat[i][j] = 0;
			else
				mat[i][j] = 1;
		}
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)
					mat[i][j] = 1;
				else
					mat[i][j] = mat[i][j] || (mat[i][k] && mat[k][j]);	
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (i > 0) printf("\n");
		for (int j = 0; j < N; j++)
			printf("%d", mat[i][j]);
	}
	return 0;
}
