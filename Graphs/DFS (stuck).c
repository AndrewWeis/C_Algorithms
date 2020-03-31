// Time complexity O(V+E)

#include <stdio.h>
#include <stdlib.h>

struct Graph
{
	int V;
	struct adjList* adj;
};

struct adjList
{
	int cur_size;
	int capacity;
	struct growingArr* grArr;
};

struct growingArr
{
	int vertice;
};

struct Graph* createGraph(int V);
void addToList(struct Graph* graph, int from, int to);
void printAdjList(struct Graph* graph, int V);
void DFS(struct Graph* graph, int s, int V);
int isFull(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int peek(struct Stack* stack);

struct Stack {
	int top;
	unsigned capacity;
	int* array;
};

struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (int*)malloc(stack->capacity * sizeof(int));
	return stack;
}

int isFull(struct Stack* stack)
{
	return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
	return stack->top == -1;
}

void push(struct Stack* stack, int item)
{
	if (isFull(stack))
		return;
	stack->array[++stack->top] = item;
}

int pop(struct Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top--];
}

int peek(struct Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top];
}

struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->adj = (struct adjList*)malloc(sizeof(struct adjList) * V);

	// inizialize list of adjective vertice to i;  ex 0: 1; 2;
	for (int i = 0; i < V; i++)
	{
		graph->adj[i].grArr = (struct adjList*)malloc(sizeof(struct adjList) * 2);
		graph->adj[i].capacity = 2;
		graph->adj[i].cur_size = 0;
	}

	return graph;
}

void addToList(struct Graph* graph, int from, int to)
{
	int cur_size = graph->adj[from].cur_size; // size of growing array whose index is from
	int capacity = graph->adj[from].capacity; // max size of growing array whose index is from

	if (cur_size == capacity)
	{
		struct growingArr* grArr = (struct growingArr*)malloc(sizeof(struct growingArr*) * capacity * 2);

		for (int i = 0; i < cur_size; i++)  // copy all data from old arr to new growing arr
			grArr[i] = graph->adj[from].grArr[i];

		grArr[cur_size].vertice = to;  // add new vertice into new growing arr

		free(graph->adj[from].grArr);  // free memory in old arr

		graph->adj[from].grArr = grArr;  // change pointer to new arr
		graph->adj[from].cur_size++;
		graph->adj[from].capacity *= 2;
	}
	else
	{
		graph->adj[from].grArr[cur_size].vertice = to;
		graph->adj[from].cur_size++;
	}
}

void printAdjList(struct Graph* graph, int V)
{
	for (int i = 0; i < V; i++)
	{
		printf("%d: ", i);
		for (int j = 0; j < graph->adj[i].cur_size; j++)
			printf("%d; ", graph->adj[i].grArr[j].vertice);
		printf("\n");
	}
}

void DFS(struct Graph* graph, int s, int V)
{
	// Mark all the vertices as not visited  
	int* visited = (int*)malloc(sizeof(int) * V);
	for (int i = 0; i < V; i++)
		visited[i] = 0;

	
	struct Stack* stack = createStack(V);

	// Push the current source node. 
	push(stack, s);

	
	int vertice = 0;
	while (!isEmpty(stack))
	{
		s = peek(stack);
		pop(stack);

		if (!visited[s])
		{
			printf("%d ", s);
			visited[s] = 1;
		}

		for (int j = 0; j < graph->adj[s].cur_size; j++)
		{
			vertice = graph->adj[s].grArr[j].vertice;
			if (!visited[vertice])
				push(stack, vertice);
		}
	}

}

int main()
{
	int V = 7;
	struct Graph* graph = createGraph(V);
	addToList(graph, 1, 2);
	addToList(graph, 1, 3);
	addToList(graph, 3, 5);
	addToList(graph, 2, 5);
	addToList(graph, 2, 4);
	addToList(graph, 4, 5);
	addToList(graph, 5, 6);
	addToList(graph, 4, 6);
	printAdjList(graph, V);
	printf("\nDFS: ");
	DFS(graph, 1, V);

	return 0;
}

/*        (1)		Adjective / Incident List
	    /     \		1: 2; 3;
	  (2)     (3)	2: 4; 5;
	   |  \     |	3: 5;
	   |     \  |	4: 5; 6;
	  (4) ---- (5)	5: 6;
		 \    /
	   (6)

      DFS: 1 3 5 6 2 4
*/
