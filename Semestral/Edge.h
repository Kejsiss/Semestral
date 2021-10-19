#ifndef _NODE_H
#define _NODE_H

typedef struct Edge {
	
	int id;
	int source;
	int target;
	int is_valid;
	char wtk[256];
}Edge;

#endif