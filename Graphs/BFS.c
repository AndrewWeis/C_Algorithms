// Time complexity is O(vertices + edges)

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
void BFS(struct Graph* graph, int s, int V);
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

// add vertices into adjence list; 
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

void BFS(struct Graph* graph, int s, int V)
{
	// Mark all the vertices as not visited  
	int* visited = (int*)malloc(sizeof(int) * V);
	for (int i = 0; i < V; i++)
		visited[i] = 0;
	
	// Create a queue for BFS 
	struct Queue* queue = createQueue(V);

	// Mark the current node as visited and enqueue it 
	visited[s] = 1;
	enqueue(queue, s);

	// 'vertice' will be used to get all adjacent vertices of a vertex 
	int vertice = 0;
	while (!isEmpty(queue))
	{
		s = front(queue);
		printf("%d ", s);
		dequeue(queue);
		
		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (int j = 0; j < graph->adj[s].cur_size; j++)
		{
			vertice = graph->adj[s].grArr[j].vertice;
			if (!visited[vertice])
			{
				visited[vertice] = 1;
				enqueue(queue, vertice);
			}			
		}
	}

}

int main ()
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
  	printf("\nBFS: ");
	BFS(graph, 1, V);

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
	   
BFS: 1 2 3 5 4 6
*/
