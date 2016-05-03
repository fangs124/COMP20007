
/*
 * Anh Vo, for:
 *
 * Week 7 Lab: COMP20007 Design of Algorithms
 *
 *
*/
#ifndef GRAPH_H
#define GRAPH_H


#define E_ORDER_NONE 0      /* edges are in arbitrary order */
#define E_ORDER_VERTICES 1  /* edges are in increasing order of vertice ID */
#define E_ORDER_WEIGHT 2    /* edges are in no-decreasing order of weights */

typedef struct graph_t* Graph;
typedef struct vertex_t* Vertex;
typedef struct edge_t* Edge; 

/* A vertex is an id, a label and degree= a number of associated edges   */
struct vertex_t {
    int id;
    char *label;
		int degree;
};

/* An edge is a triple (u,v,w): 
      where u, v are integer id of vertices, and u<v
*/
struct edge_t {
  int u;
  int v;
  int w;
};

/* A graph is its order, size, and an array of vertices */
struct graph_t {
  int order;         	/* Number of vertices */
  int size;        	/* Number of edges */
  int max_size;  	/* current max allowable size */
  int edges_ordering;   /* order of edges, as in define E_ORDER_*  */
  Vertex vertices; 	/* array of vertices */
  Edge edges;      	/* array of edges */
};

/* Returns a pointer to a new graph with order vertices */
Graph new_graph(int order);


/* Add the edge from v1 to v2 graph */
void add_edge(Graph graph, Edge e);

/* Free the memory allocated to graph */
void free_graph(Graph graph);

#endif
