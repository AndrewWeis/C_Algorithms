#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node 
{
   int data;
   struct Node* next;
};


void deleteByPostion(struct Node** head_ref, int position)
{
    if (*head_ref == NULL)
        return;
    // first Node is position 0 
    struct Node* temp = *head_ref;
 
    if (position == 0)
    {
        *head_ref = temp->next;   
        free(temp);              
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return;

    struct Node* next = temp->next->next;

    free(temp->next);
    temp->next = next;  
}

void deleteByKey(struct Node** head_ref, int key)
{
    struct Node* prev = NULL;
    struct Node* temp = *head_ref;
    
    if (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next;   
        free(temp);               
        return;
    }

    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void insertAfter(struct Node* prev_node, int new_data)
{
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void append(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = NULL;
 
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

void printList(struct Node* n)
{
    while (n != NULL) {
        printf(" %d ", n->data);
        n = n->next;
    }
}

int main() 
{
    struct Node* head = NULL;

    append(&head, 4);
    push(&head, 3);
    append(&head, 5);
    push(&head, 1);
    insertAfter(head, 2);
    // head -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL
	
    deleteByKey(&head, 3);
    // head -> 1 -> 2 -> 4 -> 5 -> NULL
    deleteByPostion(&head, 2);
    // head -> 1 -> 2 -> 5 -> NULL
	
    printf("Created Linked list is: ");
    printList(head);
    printf("\n\n\n\n\n");

	return 0;
} 
