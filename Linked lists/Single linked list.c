// REWRITE !!! ITS SHIT CODE

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int i = 0, q = 0, n = 0;
int first = 0; // указатель на первый эдемент

struct node {  // linked list
	char data[10];
	int next;
}arr[1000000];

void add(int pointer) {
	if (pointer == -1)
	{
		arr[n].next = first; // пересваивает значения индекса первого элемента
		first = n;  // пересваивает сам индекс
		printf("%d\n", n);
	}
	else
	{
		arr[n].next = arr[pointer].next;
		arr[pointer].next = n;
		printf("%d\n", n);
	}
}

void del(int pointer) {

	if (pointer == -1)
	{
		printf("%s\n", arr[first].data);
		first = arr[first].next;
	}
	else
	{
		printf("%s\n", arr[arr[pointer].next].data);
		arr[pointer].next = arr[arr[pointer].next].next;
		
	}
}

int main() {
	int sth_do = 0, index_to_do = 0;
	int tests = 0;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &tests);


	for (int f = 0; f < tests; f++) {   // кол-во тестов
		scanf("%d %d %d", &n, &first, &q);
		n--;
		for (int i = 0; i <= n; i++) {
			scanf("%s %d", &arr[i].data, &arr[i].next); //реализация списка
		}

		for (int j = 1; j <= q; j++) {
			scanf("%d ", &sth_do);
			if (sth_do == 1)  // операция удаления
			{
				scanf("%d", &index_to_do);
				del(index_to_do);
			}
			else  // операция добавления
			{
				n++;
				scanf("%d %s", &index_to_do, &arr[n].data);
				add(index_to_do);
			}
		}

		printf("===\n");
		//вывод списка		
		for (int x = first; x != -1; x = arr[x].next)
			printf("%s\n", arr[x].data);
		printf("===\n");
	}
	return 0;
}
