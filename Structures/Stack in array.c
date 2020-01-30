#include<stdio.h>
#include<stdlib.h>

struct stack
{
    int max_size;
    int top;
    int* items;
};

struct stack* newStack(int capacity)
{
    struct stack* pt = (struct stack*)malloc(sizeof(struct stack));

    pt->max_size = capacity;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * capacity);

    return pt;
}

int size(struct stack* pt)
{
    return pt->top + 1;
}

int isEmpty(struct stack* pt)
{
    return pt->top == -1;
}

int isFull(struct stack* pt)
{
    return pt->top == pt->max_size - 1;
}

void push(struct stack* pt, int x)
{
    if (isFull(pt))
    {
        printf("OverFlow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    printf("Inserting: %d\n", x);

    pt->items[++pt->top] = x;
}

// Utility function to return top element in a stack
int peek(struct stack* pt)
{
    if (!isEmpty(pt))
        return pt->items[pt->top];
    else
        exit(EXIT_FAILURE);
}

int pop(struct stack* pt)
{
    if (isEmpty(pt))
    {
        printf("OverFlow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    printf("Removing: %d\n", peek(pt));

    return pt->items[pt->top--];
}

int main()
{
    struct stack* pt = newStack(5);

    push(pt, 1);
    push(pt, 2);
    push(pt, 3);

    printf("Top elements is %d\n", peek(pt));
    printf("Stack size is %d\n", size(pt));

    pop(pt);
    pop(pt);
    pop(pt);

    if (isEmpty(pt))
        printf("Stack is empty");
    else
        printf("Stack isn't empty");

    printf("\n\n\n\n");
    return 0;
}
