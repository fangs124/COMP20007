/*
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "toposort.h"

/* recursive part of dfs_sort */
void dfs_traverse(Graph g, int n, List* sorted, bool *visited, bool *added){ //created
	/* check for cyclicity */
	if(visited[n] == true){
		fprintf(stderr, "E: graph is cyclical\n");
		exit(EXIT_FAILURE);
	}
	
	/* skip added vertices */
	if(added[n] == true){
		return;
	}

	/* mark nth vertex visited */
	visited[n] = true;

	/* traverse through all edges of vertex n */
	List ptr = g->vertices.out;
	while(ptr != NULL){
		dfs_traverse(g, (int)ptr->data, sorted, visited, added);
		ptr = ptr->next;
	}

	/* add vertex n to the sorted list */
	*sorted = push(*sorted, &g->vertices[n]);
	added[v] = true;
	visited[v] = false;
	return;
}

/* Returns a list of topologically sorted vertices using the DFS method */
List dfs_sort(Graph graph) { //implemented
	/* create auxilary boolean arrays */
	int order = graph->order;
	bool visited[order];
	bool added[order];

	int n; //vertex index
	List sorted = NULL; //holds sorted list of vertices

	/* initialize auxilary boolean arrays */
	for(n = 0; n < order; n++){
		visited[n] = false;
		added[n] = false;
	}

	/* traverse the graph through nth vertex */
	for(n = 0; n < order; n++){
		dfs_traverse(graph, n, &sorted, &visited[0], &added[0]);
	}
    return sorted;
}

/* removal part of dfs_sort, removes edge(n,m) */
void kahn_remove_edge(Graph graph, int n, int m, int *edge_count){
	del(id_eq, n, &graph->vertices[m].in);
	*edge_count -= 1;	
	return;
}

/* Returns a list of topologically sorted vertices using the Kahn method */
List kahn_sort(Graph graph) {
	/* create relevant lists */
	List sorted = NULL; //holds sorted list of vertices
	List source = NULL; //sources are verices with no incoming edges

	int n, m; //vertex index
	int edge_count = graph->size;
	int order = graph->order;
	List ptr;
    
    /* find all source vertices */
	for(n = 0; n < order; n++){
		if(graph->vertices[n].in == NULL){
			source = push(source, n);
		}
	}

	while(source != NULL){
		/* retrieve vertex n */
		n = (int) pop(&source);

		/* add n to tail of sorted list */
		insert(&graph->vertices[n], &sorted);

		/* traverse through all edges of vertex n */
		ptr = graph->vertices[n].out;
		while(ptr != NULL{
			/* remove edge(n,m) */
			kahn_remove_edge(graph, n, m, &edge_count);

			/* check if vertex m is a source vertex */
			if(graph->vertices[m].in == NULL){
				/* add m to source */
				source = push(source, m);
			}
			ptr = ptr->next;
		}
	}

	/* check for cyclicity */
	if(edge_count != 0){
		fprintf(stderr, "E: graph is cyclical\n");
		exit(EXIT_FAILURE);
	}
    return sorted;
}

/* Uses graph to verify vertices are topologically sorted */
bool verify(Graph graph, List vertices) {
    int order = graph->order;
    int n; //vertex index

    /* create array for checked vertices */
    bool checked[order];

    /* initialize array */
    for(n = 0; n < order; n++){
    	processed[i] = false;
    }

    List ptr = vertices;
    List edges;
    /* check through sorted vertices */
    while(ptr != NULL){
    	n = ((Vertex)ptr->data)->id;
    	/* check if vertices are equal equal*/
    	if(ptr_eq(&graph->vertices[n] , ptr->data) == false){
    		return false;
    	}
    	/* check for incomming edges of vertex n */
    	if((find( , &graph->vertices[n].out) != NULL)



    	ptr = ptr->next;
    }

    return false;
}
