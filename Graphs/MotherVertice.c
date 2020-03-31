// Find a mother vertex in graph
// Time complexity O(V+E)

// * Case 1:- Undirected Connected Graph : In this case, all the vertices are mother vertices 
// as we can reach to all the other nodes in the graph.
// * Case 2:- Undirected/Directed Disconnected Graph : In this case, there is no mother vertices
// as we cannot reach to all the other nodes in the graph.
// * Case 3:- Directed Connected Graph : In this case, we have to find a vertex -v in the graph
// such that we can reach to all the other nodes in the graph through a directed path.

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
void DFSUtil(struct Graph* graph, int s, int visited[]);
int findMother(struct Graph* graph, int V);

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

// add vertices into Adjacency list; 
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

	DFSUtil(graph, s, visited);
}

void DFSUtil(struct Graph* graph, int s, int visited[])
{
	// Mark the current node as visited and print it 
	visited[s] = 1;

	// Recur for all the vertices adjacent to this vertex 
	for (int j = 0; j < graph->adj[s].cur_size; j++)
		if (!visited[graph->adj[s].grArr[j].vertice])
			DFSUtil(graph, graph->adj[s].grArr[j].vertice, visited);
}

int findMother(struct Graph* graph, int V)
{
	// visited[] is used for DFS.Initially all are initialized as not visited 
	int* visited = (int*)malloc(sizeof(int) * V);
	for (int i = 0; i < V; i++)
		visited[i] = 0;

	// To store last finished vertex (or mother vertex) 
	int v = 0;

	// Do a DFS traversal and find the last finished vertex  
	for (int i = 0; i < V; i++)
		if (!visited[i])
		{
			DFSUtil(graph, i, visited);
			v = i;
		}

		// If there exist mother vertex(or vetices) in given
		// graph, then v must be one (or one of them) 

		// Now check if v is actually a mother vertex (or graph 
		// has a mother vertex).  We basically check if every vertex 
		// is reachable from v or not. 

		// Reset all values in visited[] as false and do  
		// DFS beginning from v to check if all vertices are 
		// reachable from it or not. 

	for (int i = 0; i < V; i++)
		visited[i] = 0;

	DFSUtil(graph, v, visited);
	for (int i = 0; i < V; i++)
		if (!visited[i])
			return -1;

	return v;
}		

int main()
{
	int V = 7;
	struct Graph* graph = createGraph(V);

	addToList(graph, 0, 1);
	addToList(graph, 0, 2);
	addToList(graph, 1, 3);
	addToList(graph, 4, 1);
	addToList(graph, 6, 4);
	addToList(graph, 5, 6);
	addToList(graph, 5, 2);
	addToList(graph, 6, 0);
	printf("Mother vertex is %d", findMother(graph, V));

	return 0;
}
