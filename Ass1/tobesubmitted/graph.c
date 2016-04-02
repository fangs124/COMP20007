/*
 *
*/
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

/* Returns a pointer to a new graph with order vertices */
Graph new_graph(int order) {
	Graph graph;
	graph->order = order;
	graph->size = 0;

	/* assign memory for vertices */
	graph->vertices = (Vertex) malloc(sizeof(*graph->vertices) * order);
	assert(graph->vertices != NULL);
    return graph;
}

/* Returns whether aim and vertex are pointing to the same location */
bool ptr_eq(void *aim, void *vertex) {
    return false;
}

/* Returns whether aim and vertex have the same id */
bool id_eq(void *aim, void *vertex) {
    return false;
}

/* Add the edge from v1 to v2 to graph */
void add_edge(Graph graph, int v1, int v2) {
	graph->size++;
	graph->vertices[v1].out = push(graph->vertices[v1].out, v2);
	graph->vertices[v2].in  = push(graph->vertices[v2].in , v1);
	return;
}

/* Free the memory allocated to graph */
void free_graph(Graph graph) {

}
