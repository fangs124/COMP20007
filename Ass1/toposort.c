/*
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "toposort.h"

void dfs_traverse(Graph g, int v, List* sorted, bool *visited, bool *added){
	if(visited[v] == true){
		fprintf(stderr, "E: graph is cyclical\n");
		exit(EXIT_FAILURE);
	}
	if(added[v] == true){
		return;
	}
	visited[v] = true;
	List ptr = g->vertices[v].out;
	while(ptr != NULL){
		dfs_traverse(g, (int)ptr->data, sorted, visited, added);
		ptr = ptr->next;
	}
	*sorted = push(*sorted, &g->vertices[v]);
	added[v] = true;
	visited[v] = false;
	return;
}

/* Returns a list of topologically sorted vertices using the DFS method */
List dfs_sort(Graph graph) {
	int order = graph->order;
	bool visited[order];
	bool added[order];
	List sorted	= NULL;
	int i;
	for(i = 0; i < order; i++){
		visited[i] = false;
		added[i] = false;
	}

	for(i = 0; i < order; i++){
		dfs_traverse(graph, i, &sorted, &visited[0], &added[0]);
	}
	List ptr = sorted;
	while(ptr != NULL){
		fprintf(stderr, "%s", ((Vertex)ptr->data)->label);
		if(ptr->next != NULL){
			fprintf(stderr, " -> ");
		}
		ptr = ptr->next;
	}
	fprintf(stderr, "\n");
    return sorted;
}

/* Returns a list of topologically sorted vertices using the Kahn method */
List kahn_sort(Graph graph) {
	int order = graph->order;
	List sorted = NULL;
	
    return NULL;
}

/* Uses graph to verify vertices are topologically sorted */
bool verify(Graph graph, List vertices) {
    return false;
}
