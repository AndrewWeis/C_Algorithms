#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int a[1000000];
int b[100000]; 
int c[1000000] = { 0 };
main() {
	int  n, i = 0, j = 0, q, x, k1;
	scanf("%d", &n);
	c[0] = 1;
	j = 0;
	if (n == 2) printf("2");
	else if (n == 1) printf("1");
	else {
		b[0] = 1;
		c[0] = 0;
		for (int h = 1; h <= n; h++) {
			q = h;
			i = -1;
			while (q > 0) {
				i++;
				a[i] = q % 10;
				q = q / 10;
			}
			x = 0;
			k1 = j;
			for (int z = 0; z <= j; z++) {
				for (int y = 0; y <= i; y++) {
					c[y + x] += b[z] * a[y];
					if (y + x > k1) k1++;
					if (c[y + x] > 9) {
						if (y + x + 1 > k1) k1++;
						c[y + x + 1] += c[y + x] / 10;
						c[y + x] = c[y + x] % 10;
					}
				}
				x++;
			}
			j = k1;
			if (h != n) {
				for (int z = 0; z <= j; z++) {
					b[z] = c[z];
					c[z] = 0;
				}
			}
		}
		for (int z = j; z >= 0; z--) printf("%d", c[z]);
	}
	return 0;
}
