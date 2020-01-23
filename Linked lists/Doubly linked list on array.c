#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef struct node {
	int previous;
	int data;
	int next;
} Node;

Node arr[1000001];

void add_after(int index, int data, Node *arr, int *n) {
	index++;
	arr[*n].next = arr[index].next;
	arr[index].next = *n;
	arr[*n].previous = index;
	arr[*n].data = data;
	arr[arr[*n].next].previous = *n;
	printf("%d\n", *n - 1);
	(*n)++;
}

void add_before(int index, int data, Node *arr, int *n) {
	index++;
	arr[arr[index].previous].next = *n;
	arr[*n].previous = arr[index].previous;
	arr[*n].next = index;
	arr[*n].data = data;
	arr[index].previous = *n;
	printf("%d\n", *n - 1);
	(*n)++;
}

void del(int index, Node *arr, int *n) {
	index++;
	arr[arr[index].previous].next = arr[index].next;
	arr[arr[index].next].previous = arr[index].previous;
	printf("%d\n", arr[index].data);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int index_to_do = 0, sth_do, tests, data, last, first, q, n;
	scanf("%d", &tests);
	for (int f = 0; f < tests; f++) {   // кол-во тестов 
		scanf("%d %d %d %d", &n, &first, &last, &q);
		arr[0].next = ++first;  // цикличность
		arr[0].previous = ++last;
		++n;
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &arr[i].data, &arr[i].next, &arr[i].previous); //реализация списка
			arr[i].next++;
			arr[i].previous++;
		}

		for (int j = 0; j < q; j++) {
			scanf("%d ", &sth_do);
			if (sth_do == 0) {	// операция удаления 
				scanf("%d", &index_to_do);
				del(index_to_do, arr, &n);
			}
			else if (sth_do == 1) {	// операция добавления спереди
				scanf("%d %d", &index_to_do, &data);
				add_after(index_to_do, data, arr, &n);
			}
			else if (sth_do == -1) {	// операция добавления cзади
				scanf("%d %d", &index_to_do, &data);
				add_before(index_to_do, data, arr, &n);
			}
		}
		printf("===\n");
		for (int x = arr[0].next; x > 0; x = arr[x].next)
			printf("%d\n", arr[x].data);
		printf("===\n");
	}
	return 0;
}
