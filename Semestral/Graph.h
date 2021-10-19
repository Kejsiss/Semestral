#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct NextListNode
{
	int id;
	char wtk[256];
	int id_destination;
	struct NextListNode* next;
}Node;

typedef struct Edge {

	int id;
	int source;
	int target;
	int capacity;
	int is_valid;
	char wtk[256];
}Edge;

typedef struct NextList {
	Node* head;
}Node_List;

typedef struct Graph
{
	int vertices;
	Node_List* nodes;
}Graph;

Graph* create_graph(int V);
Node* create_next_node(int dest);
void add_edge(Graph* graph, int src, int dest);
void print_graph(Graph* graph);
void free_graph(Graph* graph);
void free_node_in_list(Node* node);

#endif