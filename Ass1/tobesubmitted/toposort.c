/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * NAME: Adrian Hendrawan Putra
 * ID  : 743206
 * DESC: 0x7c
 *       Implementation of dfs and kahn topological sorting algorithms.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "toposort.h"

/* Recursive part of dfs_sort */
void dfs_traverse(Vertex n, List* sorted, bool *visited, bool *added);

/* Removal part of dfs_sort, removes edge(n,m) */
void kahn_remove_edge(Vertex n, Vertex m, int *edge_count);

/* Returns a list of topologically sorted vertices using the DFS method */
List dfs_sort(Graph graph) {
    /* create auxilary boolean arrays */
    int order = graph->order;
    bool visited[order];  //temporary
    bool added[order];    //permanent

    int i; //vertex index
    List sorted = NULL;

    /* initialize auxilary boolean arrays */
    for(i = 0; i < order; i++) {
        visited[i] = false;
        added[i] = false;
    }

    /* traverse all the vertices in graph */
    for(i = 0; i < order; i++) {
        /* skip added vertices */
        if(added[i] == true) {
            continue;
        }
        dfs_traverse(&graph->vertices[i], &sorted, &visited[0], &added[0]);
    }

    return sorted;
}

/* Recursive part of dfs_sort */
void dfs_traverse(Vertex n, List* sorted, bool *visited, bool *added) {
    /* check for cyclicity */
    if(visited[n->id] == true) {
        fprintf(stderr, "E: graph is cyclical\n");
        exit(EXIT_FAILURE);
    }
    
    /* skip added vertices */
    if(added[n->id] == true) {
        return;
    }

    /* mark vertex n visited */
    visited[n->id] = true;

    /* traverse through all reachable vertices of vertex n */
    List ptr = n->out;
    while(ptr != NULL) {
        dfs_traverse((Vertex)ptr->data, sorted, visited, added);
        ptr = ptr->next;
    }

    /* add vertex n to the sorted list */
    *sorted = push(*sorted, n);
    added[n->id] = true;
    visited[n->id] = false;

    return;
}


/* Returns a list of topologically sorted vertices using the Kahn method */
List kahn_sort(Graph graph) {
    /* create relevant lists */
    List sorted = NULL;
    List source = NULL; //sources are verices with no incoming edges

    int i; //vertex index
    Vertex n, m;
    int edge_count = graph->size;
    int order = graph->order;
    List ptr;
    
    /* find all source vertices */
    for(i = 0; i < order; i++) {
        if(graph->vertices[i].in == NULL) {
            source = push(source, &graph->vertices[i]);
        }
    }

    while(source != NULL) {
        /* retrieve vertex n */
        n = (Vertex) pop(&source);

        /* add n to tail of sorted list */
        insert(n, &sorted);

        /* traverse through all reachable vertices of vertex n */
        ptr = n->out;
        while(ptr != NULL) {
            m = (Vertex) ptr->data;

            /* remove edge(n,m) */
            kahn_remove_edge(n, m, &edge_count);

            /* check if vertex m is a source vertex */
            if(m->in == NULL) {
                /* add m to source */
                source = push(source, m);
            }
            ptr = ptr->next;
        }
    }

    /* check for cyclicity */
    if(edge_count != 0) {
        fprintf(stderr, "E: graph is cyclical\n");
        exit(EXIT_FAILURE);
    }

    return sorted;
}

/* Removal part of dfs_sort, removes edge(n,m) */
void kahn_remove_edge(Vertex n, Vertex m, int *edge_count) {
    del(ptr_eq, n, &m->in);
    *edge_count -= 1;   
    return;
}

/* Uses graph to verify vertices are topologically sorted */
bool verify(Graph graph, List vertices) {
    int order = graph->order;
    int i; //vertex index

    /* create array for visited vertices */
    bool visited[order];

    /* initialize array */
    for(i = 0; i < order; i++) {
        visited[i] = false;
    }

    List ptr = vertices;
    List edges;

    /* check through sorted vertices */
    while(ptr != NULL) {
        i = ((Vertex)ptr->data)->id;

        /* mark ith vertex visited */
        visited[i] = true;

        /* check for all reachable vertices of ith vertex */
        edges = ((Vertex)ptr->data)->out;
        while(edges != NULL) {
            if(visited[((Vertex)edges->data)->id] == true) {
                return false;
            }
            edges = edges->next;
        }
        ptr = ptr->next;
    }

    return true;
}
