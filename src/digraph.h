#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "linked_list.h"

typedef struct Digraph {
    LinkedList **vertices;
    int num_vertices;
} Digraph;

Digraph* digraph_build(int num_vertices, int num_edges, int edges[][2]);
int digraph_num_edges(Digraph *digraph);
int **digraph_gen_incidence_matrix(Digraph *digraph);
void digraph_print(Digraph *digraph);
void digraph_free(Digraph *digraph);
void digraph_free_incidence_matrix(int **matrix, int num_rows);

#endif // !DIGRAPH_H


