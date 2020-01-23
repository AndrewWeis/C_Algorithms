// Double linked list with using dynamics

#include <stdio.h> 
#include <stdlib.h> 

struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
};

void push(struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	new_node->data = new_data;
	new_node->next = (*head_ref);
	new_node->prev = NULL;

	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;

	(*head_ref) = new_node;
}

void insertAfter(struct Node* prev_node, int new_data)
{
	if (prev_node == NULL) {
		printf("the given previous node cannot be NULL");
		return;
	}

	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
	new_node->prev = prev_node;

	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void append(struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	struct Node* last = *head_ref; 

	new_node->data = new_data;
	new_node->next = NULL;

	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	new_node->prev = last;
}

void deleteNode(struct Node** head_ref, struct Node* del)
{
	if (*head_ref == NULL || del == NULL)
		return;

	if (*head_ref == del)
		*head_ref = del->next;

	if (del->next != NULL)
		del->next->prev = del->prev;

	if (del->prev != NULL)
		del->prev->next = del->next;

	free(del);
}

void deleteByPosition(struct Node** head_ref, int position)
{
	if (*head_ref == NULL || position <= 0)
		return;

	struct Node* current = *head_ref;

	for (int i = 0; current != NULL && i < position; i++)
		current = current->next;

	if (current == NULL)
		return;

	deleteNode(head_ref, current);
}

void deleteByKey(struct Node** head_ref, int key)
{
	if ((*head_ref) == NULL)
		return;

	struct Node* current = *head_ref;
	struct Node* next;

	while (current != NULL) 
	{
		if (current->data == key) 
		{
			next = current->next;
			deleteNode(head_ref, current);
			current = next;
		}
		else
			current = current->next;
	}
}

void printList(struct Node* node)
{
	struct Node* last = NULL;
	printf("\nTraversal in forward direction: ");
	while (node != NULL) {
		printf(" %d ", node->data);
		last = node;
		node = node->next;
	}

	printf("\nTraversal in reverse direction: ");
	while (last != NULL) {
		printf(" %d ", last->data);
		last = last->prev;
	}
}

int main()
{
	struct Node* head = NULL;

	push(&head, 2);
	insertAfter(head, 3);
	push(&head, 1);
	append(&head, 4);
	append(&head, 5);
	// 1 -> 2 -> 3 -> 4 -> 5 

	deleteByPosition(&head, 1);
	deleteByKey(&head, 3);
	// 1 -> 4 -> 5

	printf("Created DLL is: ");
	printList(head);
	printf("\n\n\n\n\n");
	
	return 0;
}
