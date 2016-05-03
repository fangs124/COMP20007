/* 
 * 
 * Clement Poh
 *
 * This program creates random dag (type=1)
 *   or connected weighted undirected graph (type = 2)
 *
 * usage: graphgen type [<order> <edge_chance>]
 *
 *   type = 2 added by Anh Vo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_ORDER 10
#define EDGE_CHANCE 35
#define DAG 1
#define WEIGHTED 2

void init_shuffle(int *labels, int order) {
  int i, j;
  for (i = 0; i < order; i++) {
    /* initialisation using the Knuth-shuffle */
    j = rand() % (i + 1);
    /* Swap an existing element [j] to position [i] */
    labels[i] = labels[j];

    /* put newly-initialized element [i] in position [j] */
    labels[j] = i;
  }
}

int main(int argc, char *argv[]) {
  int type = argc>1 ? atoi(argv[1]) : -1; 
  int order = argc > 2 ? atoi(argv[2]) : DEFAULT_ORDER;
  int prob = argc > 3 ? atoi(argv[3]) : EDGE_CHANCE;
  int *labels  = calloc(order, sizeof(*labels));
  int full_vertex= -1;
  int i, j;

  if (type != DAG && type != WEIGHTED) {
    fprintf(stderr, "creating graph type=1 for DAG,\n"
	    "type =2 for connected weighted undirected\n"); 
    fprintf(stderr, "Usage: %s type [order [probability of egdes]]\n",
	    argv[0]);
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));
  if (type==WEIGHTED) {
    full_vertex= 0; /* make this vertex having edge to all others */
    for (i=0; i<order; i++) labels[i]= i;
  } else {
    init_shuffle(labels, order);
  }

  printf("%d\n", order);
  for (i = 0; i < order; i++) {
    /* print the node label */
    printf("%d\n", labels[i]);
  }

  for (i = 0; i < order - 1; i++) {
    if (i==full_vertex) 
      for (j= i+1; j<order; j++) 
	printf("%d %d %d\n", i, j, rand()%order + 1);
    else for (j = i + 1; j < order; j++) {
	if (rand() % 100 < prob) {
	  if (type==DAG)
	    printf("%d %d\n", labels[i], labels[j]);
	  else
	    printf("%d %d %d\n", i, j, rand()%order+1);
	}
      }
  }

  free(labels);

  return 0;
}

