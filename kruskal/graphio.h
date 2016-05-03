/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module provides all the IO functionality related to graphs.
 *
*/
#ifndef GRAPHIO_H
#define GRAPHIO_H

#include "graph.h"

/* Loads the graph from file */
Graph load_graph(FILE *f);

/* Prints the graph as a DOT file to output */
void print_graph(FILE *f, Graph graph, char *title);

/* Prints the destination vertex label surrounded by spaces */
void print_vertex_label(FILE *file, void *vertex);

#endif
