#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char str[101];

void reverse(char* start, int len) {
	char exchange;

	for (int i = 0; i < len / 2; i++) {
		exchange = str[len - i - 1];
		str[len - i - 1] = str[i];
		str[i] = exchange;;
	}
}

main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, j;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		j = 0;
		scanf("%s", str);
		while (str[j]) {
			j++;
		}
		reverse(str, j);
		printf("%s\n", str);
	}
	return 0;
}
