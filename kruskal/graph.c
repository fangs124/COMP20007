
/*
 * Anh Vo, for:
 *
 * Week 7 Lab: COMP20007 Design of Algorithms
 *
 *
*/
#include <stdlib.h>
#include <assert.h>

#include "graph.h"
#include "my_malloc.h"


/* Returns a pointer to a new graph with order vertices
   initially supposing that | E | <= 2 | V | */
Graph new_graph(int order) {
  Graph g= (Graph) my_malloc(1,sizeof(*g),"new_graph.1");
  g->order= order;
  g->max_size= order<<1;  
  g->size= 0;
  g->vertices= (Vertex) my_malloc(order, sizeof(*g->vertices), "new_gparh.2");
  g->edges= (Edge) my_malloc(g->max_size, sizeof(*g->edges), "new_gparh.3");
  g->edges_ordering= E_ORDER_NONE;
  return g;
}


/* Add to graph g the edge from u to v with weight w  */
void add_edge(Graph g, Edge e) {
  if (g->size == g->max_size) {
    g->max_size <<= 1;
    g->edges= my_realloc(g->edges, g->max_size, sizeof(*g->edges),"add_edge.1");
  }

  g->edges[g->size]= *e;
  g->size++;
}

/* Free the memory allocated to graph g */
void free_graph(Graph g) {
  int order= g->order;
  int i;

  free(g->edges);
	                                
  for (i=0; i<order; i++) {       /* read sequence of "order" vertex id -- */
    Vertex v= g->vertices + i;
    free(v->label);
  }
  
  free(g->vertices); 
  free(g);
}

