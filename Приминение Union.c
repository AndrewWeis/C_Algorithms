#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

union MyUnion {
	long double N;
	unsigned long long int k;
};

union MyUnion stuff;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
  
	int N;
	unsigned long long int F;
	long double p = 0, q = 0;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%lf/%lf xor %llx", &p, &q, &F);
		
		stuff.N = p / q;
		stuff.k ^= F;

		printf("%0.15g\n", stuff.k);
	}
	return 0;
}

// input: 1/1 xor 7ff0000000000000
// output: 2
