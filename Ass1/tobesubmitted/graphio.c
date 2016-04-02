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

#define MAX_DIGIT 4 //max digit for vertex id

typedef enum { //created
    VCOUNT    = 0,
    VLABEL    = 1,
    DEDGES    = 2,
} input_stage;

//----// sub-functions 

/* Assigns relevant data to pointed vertex */
void assign_vertex(Vertex vertex, int id, char *buffer) { //created
    /* assigning data */
    vertex->id = id;
    vertex->in = NULL;
    vertex->out = NULL;
    
    /* length of label */
    size_t label_len = strlen(buffer) - 1; //compensating for '\n' and '\0'

    /* assign memory for label */
    vertex->label = malloc(label_len);
    assert(vertex->label != NULL);

    vertex->label = memcpy(vertex->label, buffer, label_len);
    vertex->label[label_len] = '\0'; //replacing '\n' with '\0'
    return;
}

/* Assigns value pair form buffer to the edge: [v1, v2] */
void get_value_pair(int *edge, char *buffer) { //created
    /* assign memory for integer */
    char* integer = (char*) malloc(sizeof(char) * MAX_DIGIT);
    assert(integer != NULL);

    int start = 0; //starting index of v1
    int digit_count = 0;
    char *ptr;

    for(ptr = buffer; ptr != '\0'; ptr++){
        /* count digit */
        if(*ptr >= '0' && *ptr <= '9'){ //vertex id is numeric only
            digit_count++;
        }

        /* get v1 */
        else if(*ptr == ' '){
            integer = memcpy(integer, &buffer[start], digit_count);
            /* assign v1 to edge: [v1, v2] */
            edge[0] = atoi(integer);
            
            //starting index of v2
            start = digit_count + 1;
            digit_count = 0;
        }

        /* get v2 */
        else if(*ptr == '\n'){
            integer = memcpy(integer, &buffer[start], digit_count);
            /* assign v2 to edge: [v1, v2] */
            edge[1] = atoi(integer);
        }
    }

    /* free allocated memory */
    free(integer);
    integer = NULL;
    return;
}

//----//

/* Loads the graph from input */
Graph load_graph(char *input) { //impelemented
    /* open file */
    FILE *file = fopen(input, "r");

    /* assign memory for input buffer */
    char *buffer = (char*) malloc(sizeof(char) * MAX_LINE_LEN);
    assert(buffer != NULL);

    int n; //vertex index
    int edge[2]; //ordered pair of vertices: [v1, v2]

    Graph graph;
    input_stage stage = VCOUNT;

    /* get per-line string from input */
    while((buffer = fgets(buffer, MAX_LINE_LEN, file)) != NULL){
        /* count and allocate memory for vertices */
        if(stage == VCOUNT){
            graph = new_graph(atoi(buffer));
            stage++;
        }

        /* assign vertex labels */
        else if(stage == VLABEL){
            //process nth vertex
            assign_vertex(&graph->vertices[n], n, buffer);
            
            n++; 
            if(n == graph->order){
                //move to next stage after all vertices
                stage++;
            }
        }

        /* assign directed edges */
        else if(stage == DEDGES){
            //get [v1, v2] from buffer
            get_value_pair(&edge[0], buffer);
            //create edge [v1, v2]
            add_edge(graph, edge[0], edge[1]);
        }
    }

    /* free allocated memory */
    free(buffer);
    buffer = NULL;
    return graph;
}

/* Prints the graph */
void print_graph(char *output, Graph graph) {
}

/* Prints the destination vertex label surrounded by spaces */
void print_vertex_label(FILE *file, void *vertex) { //implemented
    if (vertex)
        fprintf(file, " %s ", ((Vertex)vertex)->label);
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
