// Time Complexity O(vertices + edges)


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
void freeGraph(struct Graph* graph, int V);
void addToList(struct Graph* graph, int from, int to);
void printAdjList(struct Graph* graph, int V);
 
void DFS(struct Graph* graph, int s, int V);
void DFSUtil(struct Graph* graph, int s, int visited[]);


struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->adj = (struct adjList*)malloc(sizeof(struct adjList) * V);

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
	int cur_size = graph->adj[from].cur_size; 
	int capacity = graph->adj[from].capacity; 

	if (cur_size == capacity)
	{
		struct growingArr* grArr = (struct growingArr*)malloc(sizeof(struct growingArr*) * capacity * 2);

		for (int i = 0; i < cur_size; i++)  
			grArr[i] = graph->adj[from].grArr[i];

		grArr[cur_size].vertice = to;  

		free(graph->adj[from].grArr);  

		graph->adj[from].grArr = grArr;
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

	DFSUtil(graph, s, visited);

	free(visited);
}

void DFSUtil(struct Graph* graph, int s, int visited[])
{
	// Mark the current node as visited and print it 
	visited[s] = 1;
	printf("%d ", s);

	// Recur for all the vertices adjacent to this vertex 
	for (int j = 0; j < graph->adj[s].cur_size; j++)
		if (!visited[graph->adj[s].grArr[j].vertice])
			DFSUtil(graph, graph->adj[s].grArr[j].vertice, visited);
}

void freeGraph(struct Graph* graph, int V)
{
	for (int i = 0; i < V; i++)
		free(graph->adj[i].grArr);
	free(graph->adj);
	free(graph);
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

	printf("DFS: ");
	DFS(graph, 1, V);
	
	freeGraph(graph, V);

	return 0;
}
