#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct Node_s {
	struct Node_s* prev, * next;
	void* value;
} Node;

void initlist(Node* list) {
	list->next = list;
	list->prev = list;
	list->value = NULL;
}
//создаёт новый узел со значением ptr и вставляет его после узла node, возвращает указатель на созданный узел
Node* addafter(Node* node, void* ptr) {
	Node* p;
	p = malloc(sizeof(Node));
	p->next = node->next;
	p->prev = node;
	p->next->prev = p;
	node->next = p;
	p->value = ptr;
	return p;
}
//создаёт новый узел со значением ptr и вставляет его перед узлом node, возвращает указатель на созданный узел
Node* addbefore(Node* node, void* ptr) {
	Node* p;
	p = malloc(sizeof(Node));
	p->prev = node->prev;
	p->next = node;
	p->prev->next = p;
	node->prev = p;
	p->value = ptr;
	return p;
}
//удаляет заданный узел, возвращая значение, которое в нём лежало
void* erase(Node* node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	void* t = node->value;
	free(node);
	return t;
}

Node* a[100000] = { 0 };
Node* List;
int values[100000] = { 0 }; // массив значений (как идут по порядку начиная с первого индекса

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int T, Q, count;
	scanf("%d", &T);
	a[0] = malloc(sizeof(Node));
	List = a[0];
	initlist(a[0]);
	for (int i = 1; i <= T; i++)
	{
		scanf("%d", &Q);
		initlist(a[0]);
		count = 1;
		for (int j = 1; j <= Q; j++)
		{
			int type;
			int id;
			scanf("%d%d", &type, &id);
			id++;
			if (type == 1) {
				scanf("%d", &values[count]);
				a[count] = addafter(a[id], &values[count]);
				count++;
			}
			if (type == -1) {
				scanf("%d", &values[count]);
				a[count] = addbefore(a[id], &values[count]);
				count++;
			}
			if (type == 0) {
				void* t = erase(a[id]);
			}
		}
		Node* p = List;
		List = List->next;
		while (List != p) {
			int* k = List->value;
			printf("%d\n", *k);
			List = List->next;
		}
		printf("===\n");
	}
	return 0;
}
