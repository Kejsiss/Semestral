#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "Graph.h"


int get_number_of_lines(char* filename)
{
	FILE* vertex_file = fopen(filename, "r");
	int count = 0, biggest_id = 0;
	char line[200];

	//skipping first line
	fgets(line, sizeof(line), vertex_file);

	while (fgets(line, sizeof(line), vertex_file))
	{
		char* token;
		int id;

		token = strtok(line, ",");
		id = atoi(token);
		if (biggest_id < id)
			biggest_id = id;
		count++;
	}
	
	fclose(vertex_file);
	printf("count %d a biggestID %d\n", count, biggest_id);

	if (count < biggest_id)
		count = biggest_id;

	return count + 1;
}

void open_vertex_file(char* filename, Node* vertex_array) {

	char line[200];
	FILE* vertex_file = fopen(filename, "r");

	//skipping first line
	fgets(line, sizeof(line), vertex_file);

	while (fgets(line, sizeof(line), vertex_file))
	{
		char* token;
		int id;

		token = strtok(line, ",");	
		id = atoi(token);

		if (vertex_array[id].id < 0)
			vertex_array[id].id = id;

	}

	// Close the file
	fclose(vertex_file);
}

void open_edge_file(char* filename, Edge* edges) {

	char line[200];
	FILE* vertex_file = fopen(filename, "r");

	//skipping first line
	fgets(line, sizeof(line), vertex_file);

	while (fgets(line, sizeof(line), vertex_file))
	{
		char* token;
		int id, temp, counter = 0;

		//mozna pak zkusit union

		token = strtok(line, ",");

		while (token != NULL)
		{
			switch (counter)
			{
			case 0:
				id = atoi(token);
				if (edges[id].id < 0)
					edges[id].id = id;
				break;
			case 1:
				temp = atoi(token);
				edges[id].source = temp;
				break;
			case 2:
				temp = atoi(token);
				edges[id].target = temp;
				break;
			case 3:
				temp = atoi(token);
				edges[id].capacity = temp;
				break;
			case 4:
				if (strcmp(token, "True"))
					edges[id].is_valid = 0;
				else
					edges[id].is_valid = 1;
				break;

			default:
				break;
			}
			token = strtok(NULL, ",");
	
			counter++;
		}
	}

	// Close the file
	fclose(vertex_file);
}

void initialize_vertices(Node* vertices, int size)
{
	int i;

	vertices = (Node*)malloc(size * sizeof(Node));
	for (i = 0; i < size; i++)
	{
		vertices[i].id = -999;
	}

}

int check_vertex_correctness(char* filename)
{
	int line_count;

	line_count = get_number_of_lines(filename);
	printf("line count %d\n", line_count);

	if (line_count <= 0)
		return -1;

	return line_count;
}

int check_edge_correctness(char* filename, Edge* edges)
{
	int i, line_count;

	line_count = get_number_of_lines(filename);
	printf("line count %d\n", line_count);

	if (line_count <= 0)
		return 1;


	edges = (Edge*)malloc(line_count * sizeof(Edge));
	for (i = 0; i < line_count; i++)
	{
		edges[i].id = -999;
	}

	open_edge_file(filename, edges);

	for (i = 0; i < line_count; i++)
	{
		printf("edge s id %d ma hodnotu %d a source %d s target %d o kapacite %d a validni %d\n",
			i, edges[i].id, edges[i].source, edges[i].target, edges[i].capacity, edges[i].is_valid);
	}

	return 0;
}


int check_source_correctness(char* source_id, Node* vertices)
{
	

	return 0;
}


int main(int argc, char *argv[])
{
	int i;
	Node* vertices;
	Edge* edges;
	int vertices_size = 0;


	if (argc >= 6) 
	{
		printf("Checking correctness of vertexes file.....\n");
		if ((vertices_size = check_vertex_correctness(argv[1])) < 0)
		{
			printf(ERR_VERTEX_FILE);
			return 1;
		}

		initialize_vertices(vertices, vertices_size);

		for (i = 0; i < vertices_size; i++)
		{
			printf("Vertex s id %d ma hodnotu %d\n", i, vertices[i].id);
		}

		open_vertex_file(argv[1], vertices);

		for (i = 0; i < vertices_size; i++)
		{
			printf("Vertex s id %d ma hodnotu %d\n", i, vertices[i].id);
		}
			
		printf("Checking correctness of edges file.....\n");
		if (check_edge_correctness(argv[2], edges))
		{
			printf(ERR_EDGE_FILE);
			return 2;
		}

		
		
		printf("Checking correctness of source vertex ID.....\n");
		
		if (check_source_correctness(argv[3], vertices)) 
		{
			printf(ERR_SOURCE_VERTEX);
			return 3;
		}

		printf("Checking correctness of target vertex ID.....\n");
		if (argc < 2) {
			//nactu nejdriv soubor 
			//zde pak spustim samostatny proces extrakce
		}
		else {
			printf("Invalid sink vertex.\n");
			return 4;
		}
		printf("Checking correctness of output file.....\n");
		if (argc < 2) {
			//nactu nejdriv soubor 
			//zde pak spustim samostatny proces extrakce
		}
		else {
			printf("Invalid output file.\n");
			return 5;
		}

		if (argc == 7 && strcmp(argv[6],"-a"))
		{
			//spust algoritmus i s -a (volani metody s parametrem na konci 1)
		}
		else
		{
			//spust algoritmus bez -a (volani metody s parametrem na konci 0)
		}

	}
	else {
		printf("Missing arguments or too many! Expected atleast 5 arguments!\nUsage: -v <vertex-file> -e <edge-file> -s <source-id> -t <target-id> -out <output-file> -a <optional-working with invalid edges>");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}