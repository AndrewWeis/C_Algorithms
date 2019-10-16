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

	int index = 0, sth_do, tests, data, last, first, q, n;
	scanf("%d", &tests);
	for (int f = 0; f < tests; f++) {   // кол-во тестов 
		scanf("%d %d %d %d", &n, &first, &last, &q);
		arr[0].next = ++first;  // присваем индексам вспомогательного элемента индексы введеного первого
		arr[0].previous = ++last;
		++n; // собственно сдвиг по n
		for (int i = 1; i < n; i++) { // вводим элементы начиная с индекса один (нулевой под вспомогательный элемент)
			scanf("%d %d %d", &arr[i].data, &arr[i].next, &arr[i].previous); // ввод ячеек списка
			arr[i].next++; // сдвиг по индексам 
			arr[i].previous++;
		}

		for (int j = 0; j < q; j++) {
			scanf("%d ", &sth_do);
			if (sth_do == 0) {	// операция удаления 
				scanf("%d", &index); // индекс элемента, который нужно удалить
				del(index, arr, &n); // передаем в функцию: 1)индекс эелмент, который нужно удалить 2) сам список, адрес индекса под котором ячейка
			}
			else if (sth_do == 1) {	// операция добавления спереди
				scanf("%d %d", &index, &data); 
				add_after(index, data, arr, &n); // передаем: 1) индекс элемента для добавления 2) значения ячейки списка 3) сам список 4) адрес
			}
			else if (sth_do == -1) {	// операция добавления cзади
				scanf("%d %d", &index, &data);
				add_before(index, data, arr, &n);
			}
		}
		printf("===\n");
		for (int x = arr[0].next; x > 0; x = arr[x].next)  // вывод списка, вывод начинает с элемента на который указывает вспомогательный
			printf("%d\n", arr[x].data);
		printf("===\n");
	}
	return 0;
}