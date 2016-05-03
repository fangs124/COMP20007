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

extern void *my_malloc(int n, int size, char *module);

/* unsafe read a line and get an int from that */
/*   unsafe: not checking for EOF or invalid data format */
int getInt(FILE *f) {
  char s[MAX_LINE_LEN+1];
  fgets(s, MAX_LINE_LEN, f);
  return atoi(s);
}

/* read & return a line s, when fails return NULL and set line s to "" */
char* getString(FILE *f, char *s) {
  char *p;
  if (!fgets(s, MAX_LINE_LEN, f)) {
    *s= '\0';
    return NULL;
  }
  if ((p=strchr(s, '\n')) != NULL)   /* chop tailing \n */
    *p = '\0';

  return s;
}


/* Loads the graph from input, according to the given input file format -A*/
Graph load_graph(FILE *f) {
  Graph g= NULL;
  Edge e= my_malloc(1, sizeof(*e),"load_graph.1");

  int order;
  int i;
  char s[MAX_LINE_LEN+1];
	                                
  order= getInt(f);               /* get order = int in the first line --- */    
  assert (order >= 0);
  g= new_graph(order);
   
  for (i=0; i<order; i++) {       /* read sequence of "order" vertex id -- */
    Vertex v= g->vertices + i;
    v->id= i;
    v->label= my_malloc(MAX_LINE_LEN+1, sizeof(char), "load_graph.1");
    getString(f,v->label);
  }
   
  while (getString(f,s)) {        /* read lines which contain an edge each */
    /* and add to the grapg g                */
    if (sscanf(s,"%d %d %d", &e->u, &e->v, &e->w) ==3) { 
      printf("Read edge %d %d %d\n", e->u, e->v, e->w);
      assert(e->u != e->v);
      if (e->u > e->v) {    /* swap so that u < v */
	int tmp= e->u;
	e->u= e->v;
	e->v= tmp;
      }
      add_edge(g, e);
    }
  }
  
  free(e);
  return g;
}

int vertices_cmp(const void *a, const void *b) {
  Edge aa= (Edge) a, bb= (Edge) b;
  if (aa->u < bb->u || (aa->u==bb->u && aa->v < bb->v)) return -1;
  if (aa->u > bb->u || (aa->u==bb->u && aa->v > bb->v)) return 1;
  return 0;
}

/* Prints the graph -A */
void print_graph(FILE *f, Graph g, char *title) {
  int i;
  int ei;       /* index to g->edges */

  /* make sure that g->edges is ordered by vertices */
  if (g->edges_ordering != E_ORDER_VERTICES) {
    qsort(g->edges, g->size, sizeof(*g->edges), &vertices_cmp);
    g->edges_ordering= E_ORDER_VERTICES;
  }

  fprintf(f,"%s\n", title); 
  fprintf(f, "{\n");
  for (i=0, ei= 0; i<g->order; i++) {
    Vertex v= g->vertices+i;
		
    print_vertex_label(f,v); 
    /* foreach edge from v printing the names of other vertex & weight */
    if (ei < g->size && i == g->edges[ei].u ) {
      fprintf(f, " ~ {");
      for ( ; ei<g->size && i == g->edges[ei].u; ei++) {
	print_vertex_label(f, g->vertices + g->edges[ei].v);
	fprintf(f, ":%d", g->edges[ei].w);
      }
      fprintf(f," }");
    }
    fprintf(f, "\n" );
  }
  fprintf(f,"}\n");
}

/* Prints the destination vertex label surrounded by spaces -A*/
void print_vertex_label(FILE *file, void *vertex) {
  fprintf (file," %s", ((Vertex) vertex)->label);
}

