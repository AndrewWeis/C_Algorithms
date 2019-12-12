// Removing duplicates by using hash table

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000001

typedef struct node {
	int val;
	struct node* next;
}node;

node* hash_table[SIZE];

void put_ht(node** list, int value) {
	node* head = (node*)malloc(sizeof(node));
	head->val = value;
	head->next = *list;
	*list = head;
}

int check_ht(node* list, int el) {
	node* p = list;
	while (p != NULL) {
		if (p->val == el)
			return 1;
		p = p->next;
	}

	return 0;
}

unsigned int hash(unsigned int a) {
	a = (a + 0x7ed55d16) + (a << 12);
	a = (a ^ 0xc761c23c) ^ (a >> 19);
	a = (a + 0x165667b1) + (a << 5);
	a = (a + 0xd3a2646c) ^ (a << 9);
	a = (a + 0xfd7046c5) + (a << 3);
	a = (a ^ 0xb55a4f09) ^ (a >> 16);
	return a;
}

int main() {
	node* list = NULL;

	put_ht(&list, 54);

	FILE* input = fopen("input.bin", "rb");

	int N, t = 0;

	fread(&N, sizeof(int), 1, input);

	int* a = (int*)malloc(sizeof(int) * N);
	int* res = (int*)malloc(sizeof(int) * N);

	fread(a, sizeof(int), N, input);


	for (int i = 0; i < N; i++) {
		int s = hash(a[i]) % SIZE;
		if (check_ht(hash_table[hash(a[i]) % SIZE], a[i]) == 0) {

			put_ht(&hash_table[hash(a[i]) % SIZE], a[i]);
			res[t++] = a[i];
		}
	}

	FILE* output = fopen("output.bin", "wb");
	fwrite(&t, sizeof(int), 1, output);
	fwrite(res, sizeof(int), t, output);

	fclose(input);
	fclose(output);
	return 0;
}
