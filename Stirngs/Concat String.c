#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
char f[1000001] = { 0 }; 

char* concat(char* pref, char* suff, int length_str, int lenght) {
	int lenP = lenght; 
	int lenS = length_str; 
	for (int i = 0; i < lenS; i++)
		pref[lenP + i] = suff[i]; 
	pref[lenP + lenS] = '\0';
	return pref;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int lenght_str = 0;
	int len = 0;
	char second[101] = { 0 };
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%s", second);
		while (second[lenght_str])
			lenght_str++; // длина одной строчки
		concat(f, second, lenght_str, len);
		len += lenght_str; // длина склеиной строчки
		lenght_str = 0;
	}
	printf("%s", f);
	return 0;
}
