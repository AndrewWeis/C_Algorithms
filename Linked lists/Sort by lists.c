#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_s {
	int key;
	char str[8];
	struct Node_s* next;
}Node;

Node* linkedLists[1000001];
Node* LLwithOneElements[1000001];

Node* createNode(int key);
void appendNode(int key);
void printList(Node* head);

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	scanf("%d", &N);
	int key;

	for (int i = 0; i < N; i++)
	{
		scanf("%d ", &key);

		if (linkedLists[key] == NULL)
		{
			Node* newElem = createNode(key);
			LLwithOneElements[key] = newElem;
			linkedLists[key] = newElem;
 		}
		else
			appendNode(key);
	}

	for (int i = 0; i < 1000001; i++)
	{
		if (linkedLists[i] != NULL)
			printList(linkedLists[i]);
	}
	return 0;
}

Node* createNode(int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	scanf("%s", &newNode->str);
	newNode->key = key;
	newNode->next = NULL;

	return newNode;
}

void appendNode(int key)
{
	Node* current = LLwithOneElements[key];

	Node* newElem = createNode(key);

	current->next = newElem;
	LLwithOneElements[key] = newElem;
}

void printList(Node* head)
{
	Node* current = head;

	while (current != NULL)
	{
		printf("%d %s\n", current->key, current->str);

		Node* tmp = current;

		current = current->next;
		free(tmp);
	}
}
