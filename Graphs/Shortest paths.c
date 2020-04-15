#pragma comment (linker, "/STACK:50000000")
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
	int curSize;
	int capacity;
	int* grArr;
} Vertex;

void BFS(Vertex* vertex, int s, int V);

struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
int front(struct Queue* queue);

struct Queue
{
	int front, rear, size;
	unsigned capacity;
	int* array;
};

struct Queue* createQueue(unsigned capacity)
{
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->array = (int*)malloc(queue->capacity * sizeof(int));
	return queue;
}

int isFull(struct Queue* queue)
{
	return (queue->size == queue->capacity);
}

int isEmpty(struct Queue* queue)
{
	return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item)
{
	if (isFull(queue))
		return;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

int front(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}


void printAdj(Vertex* vertex, int V)
{
	for (int i = 1; i < V + 1; i++)
	{
		printf("\n%d: ", i);
		for (int j = 0; j < vertex[i].curSize; j++)
			printf("%d; ", vertex[i].grArr[j]);
	}
}

void BFS(Vertex* vertex, int s, int V)
{
	int* visited = (int*)malloc(sizeof(int) * (V+1));
	for (int i = 1; i < V + 1; i++)
		visited[i] = 0;

	int* isPath = (int*)malloc(sizeof(int) * (V + 1));
	for (int i = 0; i < V + 1; i++)
		isPath[i] = -1;
	isPath[1] = 0;

	struct Queue* queue = createQueue(V);

	visited[s] = 1;
	enqueue(queue, s);
	
	int distance = 0;
	int vertice = 0;
	
	while (!isEmpty(queue))
	{
		s = front(queue);
		int u = dequeue(queue);

		for (int j = 0; j < vertex[s].curSize; j++)
		{
			vertice = vertex[s].grArr[j];
			if (!visited[vertice])
			{
				enqueue(queue, vertice);
				visited[vertice] = 1;
				isPath[vertice] = isPath[u]+1;
			}
		}
	}

	for (int i = 1; i < V + 1; i++)
	{
		printf("%d\n", isPath[i]);
	}

	free(visited);
	free(queue->array);
	free(queue);
}

Vertex* adj(int V, int E)
{
	Vertex* vertex = malloc(sizeof(Vertex) * (V + 1));

	for (int i = 1; i < (V + 1); ++i)
	{
		vertex[i].capacity = 1;
		vertex[i].curSize = 0;
		vertex[i].grArr = malloc(sizeof(int));
	}

	for (int i = 0; i < E; ++i)
	{
		int from = 0, to = 0;
		scanf("%d %d", &from, &to);

		if (vertex[from].curSize >= vertex[from].capacity)
		{
			vertex[from].capacity *= 2;
			vertex[from].grArr = realloc(vertex[from].grArr, sizeof(int) * vertex[from].capacity);
		}
		vertex[from].grArr[vertex[from].curSize] = to;
		vertex[from].curSize++;
	}

	return vertex;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int V = 0, E = 0;
	scanf("%d %d", &V, &E);

	Vertex* vertex = adj(V, E);

//	printAdj(vertex, V);
	BFS(vertex, 1, V);

	return 0;
}
