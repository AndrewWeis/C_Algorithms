#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
 * @key : The key string of a pair
 * The key is unique in the HashTable
 *
 * @value : The value corresponding to a key
 * A value is not unique. It can correspond to several keys
 *
 * @next : A pointer to the next node of the List
 */
typedef struct List
{
	char* key;
	char* value;
	struct List* next;
} List;

/*
 * @size : The size of the array
 *
 * @array : An array of size @size
 * Each cell of this array is a pointer to the first node of a linked list,
 * because we want our HashTable to use a Chaining collision handling
 */
typedef struct HashTable
{
	unsigned int size;
	List** array;
} HashTable;

/*
 * @key : The key to hash
 *
 * @size : The size of the hashtable
 *
 * @return : An integer N like 0 <= N < @size
 * This integer represents the index of @key in an array of size @size
 */

unsigned int hash(const char* key, unsigned int size)
{
	unsigned int hash;
	unsigned int i;

	hash = 0;
	i = 0;
	while (key && key[i])
	{
		hash = (hash + key[i]) % size;
		++i;
	}
	return (hash);
}

/*
 * ht_create() - If the size is a positive integer, allocate the requisite
 * memory for a new hashtable and its indexed array. Assign the size of the
 * array in ht->size.
 * size: The size of the hashtable's array.
 *
 * Return: A pointer to the newly allocated Hashtable. If size is zero or a
 * negative number, return NULL. If a memory allocation fails, return NULL.
 */
HashTable* ht_create(unsigned int size)
{
	HashTable* ht;

	ht = malloc(sizeof(HashTable));

	ht->array = (List**)malloc(size * sizeof(List));
	if (ht->array == NULL) {
		return (NULL);
	}

	memset(ht->array, 0, size * sizeof(List));

	ht->size = size;

	return ht;
}

/*
 * node_handler() - If the index item is a linked list, traverse it to ensure
 * that there is not already an item with the key passed. If there is,
 * reassign the value of the prexisting node to the current instead of adding
 * the new node.
 * @hashtable: The hashtable of Lists.
 * @node: The linked list to add a node to or update.
 *
 * Return: Void.
 */
void node_handler(HashTable* hashtable, List* node)
{
	unsigned int i = hash(node->key, hashtable->size);
	List* tmp = hashtable->array[i];

	if (hashtable->array[i] != NULL) {
		tmp = hashtable->array[i];
		while (tmp != NULL) {
			if (str_cmp(tmp->key, node->key) == 0) {
				break;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL) {
			node->next = hashtable->array[i];
			hashtable->array[i] = node;
		}
		else {
			free(tmp->value);
			tmp->value = strdup(node->value);
			free(node->value);
			free(node->key);
			free(node);
		}
	}
	else {
		node->next = NULL;
		hashtable->array[i] = node;
	}
}

/*
 * ht_put() - Allocates memory for a new node and calls the node_handler
 * function to either insert the node if the key does not exist, or update
 * a prexisting node in the case that it has the same key as that passed
 * to this function.
 * @key: The key to add to the hash table.
 * @value: The corresponding value to add to the node.
 *
 * Return: One if memory allocation fails, and zero if the function returns
 * successfully.
 */
int ht_put(HashTable* hashtable, const char* key, const char* value)
{
	List* node;

	node = malloc(sizeof(List));

	node->key = strdup(key);
	node->value = strdup(value);

	node_handler(hashtable, node);

	return 0;
}

/*
 * str_cmp() - Compare two strings to determine if they are identical. Ensures
 * that each char in the strings are the same, and that they are of the same
 * length.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Zero if the strings are identical, one otherwise.
 */
int str_cmp(char* s1, char* s2)
{
	int i;
	int j = 0;

	for (i = 0; s1[i] != '\0'; ++i) {
		if (s1[j] != s2[j] || s1[j + 1] != s2[j + 1]) {
			return 1;
		}
		j++;
	}
	return 0;
}

/*
 * ht_get() - Traverse the list that is at the corresponding array location in
 * the hashtable. If a node with the same key is found as that passed to this
 * function, then return the value of that node. Otherwise, return NULL,
 * indicating there is no node with the key passed. Before returning, free
 * the copy of the string `key_cp`.
 * @hashtable: The hashtable in which to search for the data.
 * @key: The key to search the hashtable for.
 *
 * Return: The value that corresponds to the key if it is found, and NULL
 * otherwise. If the hashtable is NULL, return NULL.
 */
char* ht_get(HashTable* hashtable, const char* key)
{
	char* key_cp;
	unsigned int i;
	List* tmp;

	if (hashtable == NULL) {
		return NULL;
	}
	key_cp = strdup(key);
	i = hash(key, hashtable->size);
	tmp = hashtable->array[i];

	while (tmp != NULL) {
		if (str_cmp1(tmp->key, key_cp) == 0) {
			break;
		}
		tmp = tmp->next;
	}
	free(key_cp);

	if (tmp == NULL) {
		return NULL;
	}
	return tmp->value;
}

/*
 * str_cmp1() - Compare two strings to determine if they are identical. Ensures
 * that each char in the strings are the same, and that they are of the same
 * length.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Zero if the strings are identical, one otherwise.
 */
int str_cmp1(char* s1, char* s2)
{
	int i;
	int j = 0;

	for (i = 0; s1[i] != '\0'; ++i) {
		if (s1[j] != s2[j] || s1[j + 1] != s2[j + 1]) {
			return 1;
		}
		j++;
	}
	return 0;
}

/*
 * ht_free() - Free the items in a hashtable. Iterate through the hashtable's
 * array. If it is a linked list, then traverse the list and free all the
 * node's attributes and then the node itself. When the end of the list is
 * reached, free the array item itself (i.e., `hashtable->array[i]`). Finally,
 * when all the array items are freed, free the hashtable array pointer and
 * the hastable itself.
 * @hashtable: The hashtable to free.
 *
 * Return: If the hashtable is NULL, return because there is nothing to free.
 */
void ht_free(HashTable* hashtable)
{
	List* tmp;
	unsigned int i;

	if (hashtable == NULL) {
		return;
	}

	for (i = 0; i < hashtable->size; ++i) {
		if (hashtable->array[i] != NULL) {
			/* Traverse the list and free the nodes. */
			while (hashtable->array[i] != NULL) {
				tmp = hashtable->array[i]->next;
				free(hashtable->array[i]->key);
				free(hashtable->array[i]->value);
				free(hashtable->array[i]);
				hashtable->array[i] = tmp;
			}
			free(hashtable->array[i]);
		}
	}
	free(hashtable->array);
	free(hashtable);
}

void print_str(char* str);
int print_hashtable(HashTable* ht);
void print_num(int n);
int print_char(char c);

int main(void) {
	HashTable* ht;
	ht = ht_create(3);

	if (ht == NULL) {
		return 1;
	}

	ht_put(ht, "key 1", "val 1");
	ht_put(ht, "key 1", "val 1");
	ht_put(ht, "key -2", "val -2");
	ht_put(ht, "key 4", "val 4");
	ht_put(ht, "key 3", "val 3");
	ht_put(ht, "key 0", "val 0");
	ht_put(ht, "key 0", "val 0");
	ht_put(ht, "key 0", "val 0");
	ht_put(ht, "key -2", "val -2");
	print_hashtable(ht);
	print_str(ht_get(ht, "key 4"));
	print_str("\n");
	ht_free(ht);
	return 0;
}

int print_hashtable(HashTable* ht) {
	unsigned int i;
	List* listptr;
	for (i = 0; i < ht->size; ++i) {
		print_num(i);
		print_str("\n");

		listptr = ht->array[i];
		print_str("\t--------\n");

		while (listptr != NULL) {
			print_str("\tkey: ");
			print_str(listptr->key);
			print_str("\n\tval: ");
			print_str(listptr->value);
			listptr = listptr->next;
			print_str("\n\t--------\n");
		}
		print_str("\tNULL\n\t--------\n");
	}
	return 0;
}

int print_char(char c)
{
	return (write(1, &c, 1));
}

/*
 * print_str() - Prints a string to stdout.
 * @str: A pointer to a string to be printed.
 *
 * Return: Void.
 */
void print_str(char* str)
{
	int i;
	for (i = 0; str[i] != '\0'; ++i) {
		print_char(str[i]);
	}
}

/*
 * print_num() - Prints a number to stdout.
 * @n: The number to print.
 *
 * Return: Void.
 */

void print_num(int n)
{
	if (n >= 10) {
		print_num(n / 10);
	}
	print_char(n % 10 + 48);
} 
