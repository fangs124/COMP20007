/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module provides all the IO functionality related to graphs.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graphio.h"

#define MAX_LINE_LEN 256

#define MAX_DIGIT 8

typedef enum {
    VCOUNT    = 0,
    VLABEL    = 1,
    DEDGES    = 2,
} input_stage;

/* Loads the graph from input */
void set_edges(Graph graph, char* buffer){//implemented
	char* c = buffer;
	int start = 0;
	int charcount = 0;
	char* integer = (char*) malloc(sizeof(char) * MAX_DIGIT);
	int i; //= (int*) malloc (sizeof(int));
	int j; //= (int*) malloc (sizeof(int));
	while(*c != '\0' && *c != '\n'){
		//fprintf(stderr, "c = %c\n", *c);
		if(*c >= 0x30 && *c <= 0x39){
			//fprintf(stderr, "here1\n");
			charcount++;
		}
		else if(*c == 0x20){
			//fprintf(stderr, "here2\n");
			integer = memcpy(integer,
				&buffer[start], charcount);
			integer[charcount] = '\0';
			start = charcount+1;
			charcount = 0;
			i = atoi(integer);
		}
		c++;
	}
	integer = memcpy(integer,
		&buffer[start], charcount);
	integer[charcount] = '\0';
	j = atoi(integer);
	//fprintf(stderr, "i = %d\nj = %d\n", *i, *j);
	graph->size++;
	graph->vertices[i].out = push(graph->vertices[i].out, j);
	graph->vertices[j].in = push(graph->vertices[j].in, i);
	return;
}

Graph load_graph(char *input) {//implemented
	/* open file */
	FILE *file = fopen(input, "r");
	input_stage stage = VCOUNT;
	char *buffer = (char*) malloc(sizeof(char) * MAX_LINE_LEN);
	assert(buffer);
	Graph graph = malloc(sizeof(*graph));
	graph->size = 0;
	int i = 0;
	fprintf(stderr, "here\n");

	while((buffer = fgets(buffer, MAX_LINE_LEN, file)) != NULL){
		//debug
		fprintf(stderr, "%s", buffer);
		/* get number of nodes */
		if(stage == VCOUNT){
			graph->order = atoi(buffer);
			graph->vertices = (Vertex) malloc(sizeof(*graph->vertices) * graph->order);
			stage++;
		}
		/* assign labels */
		else if(stage == VLABEL){
			//fprintf(stderr, "i=%d\n", i);
			graph->vertices[i].id = i;
			graph->vertices[i].label = malloc(strlen(buffer) - 1);
			graph->vertices[i].label = memcpy(graph->vertices[i].label,
				buffer, strlen(buffer) - 1);
			graph->vertices[i].label[strlen(buffer) - 1] = '\0';
			graph->vertices[i].in = NULL;
			graph->vertices[i].out = NULL;
			i++;
			if(i == graph->order){
				stage++;
			}
		}
		/* assign edges */
		else if(stage == DEDGES){
			set_edges(graph, buffer);
		}
	}
	//debug
	List list_ptr;
	for(i = 0; i < graph->order; i++){
		print_vertex_id(stderr, &graph->vertices[i]);
		print_vertex_label(stderr, &graph->vertices[i]);
		list_ptr = graph->vertices[i].in;
		fprintf(stderr, "vertice[%d]: in\n", i);
		while(list_ptr != NULL){
			fprintf(stderr, "[%d] ", (int)list_ptr->data);
			list_ptr = list_ptr->next;
		}
		fprintf(stderr, "\n");
		list_ptr = graph->vertices[i].out;
		fprintf(stderr, "vertice[%d]: out\n", i);
		while(list_ptr != NULL){
			fprintf(stderr, "[%d] ", (int)list_ptr->data);
			list_ptr = list_ptr->next;
		}
		fprintf(stderr, "\n");
	}
	fclose(file);
	return graph;
}

/* Prints the graph */
void print_graph(char *output, Graph graph) {//implement this function
	FILE *file = fopen(output, "w");

	fprintf(file, "digraph {\n");
	int i;
	int j;
	List list_ptr;
	for(i = 0; i < graph->order; i++){
		fprintf(file, "  %s", graph->vertices[i].label);
		if(graph->vertices[i].out != NULL){
			fprintf(file, " -> {");
			list_ptr = graph->vertices[i].out;
			while(list_ptr != NULL){
				j = (int)list_ptr->data;
				fprintf(file, " %s ", graph->vertices[j].label);
				list_ptr = list_ptr->next;
			}
			fprintf(file, "}");
		}
		fprintf(file, "\n");
	}
	fprintf(file, "}\n");
	return;
}

/* Prints the destination vertex label surrounded by spaces */
void print_vertex_label(FILE *file, void *vertex) {//implemented
	if (vertex)
		fprintf(file, "%s\n", ((Vertex)vertex)->label);
}

/* Prints the id of a vertex then a newline */
void print_vertex_id(FILE *file, void *vertex) {
	if (vertex)
		fprintf(file, "%d\n", ((Vertex)vertex)->id);
}

/* Returns a sequence of vertices read from file */
List load_vertex_sequence(FILE *file, Graph graph) {
	const char *err_duplicate = "Error: duplicate vertex %d %s\n";
	const char *err_order = "Error: graph order %d, loaded %d vertices\n";
	List list = NULL;
	int id;

	while(fscanf(file, "%d\n", &id) == 1) {
		assert(id >= 0);
		assert(id < graph->order);

		if (!insert_if(id_eq, graph->vertices + id, &list)) {
			fprintf(stderr, err_duplicate, id, graph->vertices[id].label);
			exit(EXIT_FAILURE);
		}
	}

	if (len(list) != graph->order) {
		fprintf(stderr, err_order, graph->order, len(list));
		exit(EXIT_FAILURE);
	}

	return list;
}
