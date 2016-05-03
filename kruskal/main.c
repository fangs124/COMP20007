/*
 * Anh Vo, 17/04/2016. 
 * For:
 *
 * Week 7 Lab: COMP20007 Design of Algorithms
 *
 *
*/
#include <stdlib.h>
#include <stdio.h>

#include "kruskal.h"
#include "graph.h"
#include "graphio.h"
#include "my_malloc.h"

int main(int argc, char *argv[]) {
  Graph graph = NULL;    /* imput & output  graph */

  graph= load_graph(stdin);	
  print_graph(stdout, graph, "Original graph:");

  if ( kruskal(graph) ) {
    print_graph(stdout, graph, "\nMinimal spanning tree:");  
  }
 
  free_graph(graph);
  exit(EXIT_SUCCESS);
}

