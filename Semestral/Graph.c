#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph* create_graph(int V) {

	int i;
	Graph* graph;

	graph = (Graph*)malloc(sizeof(Graph));

	graph->vertices = V;
	graph->nodes = (Node_List*)malloc(V * sizeof(Node_List));

	for (i = 0; i < V; i++) {
		graph->nodes[i].head = NULL;
	}

	return graph;
}

Node* create_next_node(int dest){

	Node* new_node;

	new_node = (Node*)malloc(sizeof(Node));

	new_node->next = NULL;
	new_node->id_destination = dest;

	return new_node;

}

void add_edge(Graph* graph, int src, int dest) {

	Node* new_node;

	/*Pridal hranu z src do  dest*/
	new_node = create_next_node(dest);
	new_node->next = graph->nodes[src].head;
	graph->nodes[src].head = new_node;

	/* Vytvarim obousmernou hranu 
	new_node = create_next_node(src);
	new_node->next = graph->nodes[dest].head;
	graph->nodes[dest].head = new_node;
	*/
}

void print_graph(Graph* graph) {

	int i;

	for (i = 0; i < graph->vertices; i++)
	{
		Node* node = graph->nodes[i].head;
		printf("\ List of adjacent nodes for vertex %d\n head ", i);

		while (node)
		{
			printf("-> %d", node->id_destination);
			node = node->next;
		}
		printf("\n");
	}
}

void free_graph(Graph* graph)
{
	int v;

	for (v = 0; v < graph->vertices; v++)
	{
		Node* node = graph->nodes[v].head;
		free_node_in_list(node);
		printf("Clearing adjacency list of vertex %d", v);
	}
}

void free_node_in_list(Node* node)
{
	if (node->next == NULL) {
		node = NULL;
		free(node);
	}
	else {
		free_node_in_list(node->next);
	}

}
