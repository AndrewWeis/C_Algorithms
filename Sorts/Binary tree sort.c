#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct Node {
    int value;
    struct Node* left, * right;
};

struct Node* newNode(int value) {
    struct Node* node = malloc(sizeof * node);
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* node, int value) {
    int k = rand() % 2;
    if (node == NULL)
        return newNode(value);
    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);

    if (value == node->value && k == 0)
        node->left = insert(node->left, value);
    else if (value == node->value && k == 1)
        node->right = insert(node->right, value);

    return node;
}

void collect(struct Node* root, int T[], int* i) {
    if (root != NULL) {
        collect(root->left, T, i);
        T[(*i)++] = root->value;
        collect(root->right, T, i);
    }
}

void binary_tree_sort(int T[], int n) {
    struct Node* root = NULL;
    int i;
    for (i = 0; i < n; i++)
        root = insert(root, T[i]);
    i = 0;
    collect(root, T, &i);
}

int tree[500002] = { 0 };

int myRand() {
    const long n = 2145678965L;
    const long a = 763214L;
    const long b = 88844L;
    const long c = 7766L;

    static long seed = 12345678L;
    long hi = seed / b;
    long lo = seed - b * hi;
    long t = a * lo - c * hi;

    if (t > 0)
        seed = t;
    else
        seed = t + n;
    
    return seed % 500002;
}

int main() {
    FILE* input = fopen("input.bin", "rb");
    FILE* output = fopen("output.bin", "wb");
    int n;
    fread(&n, sizeof(int), 1, input);

    for (int i = 0; i < n; i++)
        fread(&tree[i], sizeof(int), 1, input);
  
    int swap;
        for (int i = 2; i < n; i++) {
            int pos = myRand();
            if (pos < 0)
                pos *= (-1);
            pos = pos % i;
            swap = tree[i];
            tree[i] = tree[pos];
            tree[pos] = swap;
        }

    binary_tree_sort(tree, n);
    for (int i = 0; i < n; i++)
        fwrite(&tree[i], sizeof(int), 1, output);

    fclose(input);
    fclose(output);
    return 0;
}
