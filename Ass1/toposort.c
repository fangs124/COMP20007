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

bool is_equal(void *aim, void *node){
	return(bool)((int)aim == (int)node);
}

void kahn_remove_edge(Graph graph, int v_index, int n_index, int *edge_count){
	del(is_equal,v_index, &graph->vertices[n_index].in);
	*edge_count = *edge_count-1;
	fprintf(stderr, "in remove: size = %d\n", *edge_count);
	return;
}
/* Returns a list of topologically sorted vertices using the Kahn method */
List kahn_sort(Graph graph) {
	fprintf(stderr, "initial: size = %d\n", graph->size);
	int edge_count = graph->size;
	int order = graph->order;
	List sorted = NULL;
	List source = NULL;
	int i;
	/* add all vertices with no incoming edge */
	for(i = 0; i < order; i++){
		if(graph->vertices[i].in == NULL){
			source = push(source, i);
		}
	}
	List ptr;
	int v_index;//srt
	int n_index;//dst
	while(source != NULL){
		v_index = (int)pop(&source);
		insert(&graph->vertices[v_index], &sorted);
		ptr = graph->vertices[v_index].out;
		while(ptr != NULL){
			n_index = (int)ptr->data;
			kahn_remove_edge(graph, v_index, n_index, &edge_count);
			fprintf(stderr, "in sort: size = %d\n", edge_count);
			if(graph->vertices[n_index].in == NULL){
				source = push(source, n_index);
			}
			ptr = ptr->next;
		}
	}
	
	if(edge_count != 0){
		fprintf(stderr, "E: graph is cyclical\n");
		exit(EXIT_FAILURE);
	}

    return sorted;
}

/* Uses graph to verify vertices are topologically sorted */
bool verify(Graph graph, List vertices) {
	bool processed[graph->order];
	int i;
	for(i = 0; i < graph->order; i++){
		processed[i] = false;
	}
	int v;
	List v_ptr = vertices;
	List out_ptr;
	while(v_ptr->next != NULL){
		v = ((Vertex)v_ptr->data)->id;
		processed[v] = true;
		out_ptr = ((Vertex)v_ptr->data)->out;
		while(out_ptr != NULL){
			if(processed[(int)out_ptr->data] == true){
				return false;
			}
			out_ptr = out_ptr->next;
		}
		v_ptr = v_ptr->next;
	}
    return true;
}
