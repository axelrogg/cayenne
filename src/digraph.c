#include <stdio.h>
#include "digraph.h"

int digraph_num_edges(Digraph *digraph) {
    int num_edges = 0;
    for (int i = 0; i < digraph->num_vertices; i++) {
        if (digraph->vertices[i] == NULL) {
            continue;
        }
        num_edges += digraph->vertices[i]->size;
    }
    return num_edges;
}


int **digraph_gen_incidence_matrix(Digraph *digraph) {
    int num_edges = digraph_num_edges(digraph);
    int **matrix = malloc(digraph->num_vertices * sizeof(int*));
    if (matrix == NULL) {
        printf("digraph_gen_incidence_matrix :: Memory allocation for incidence matrix failed. Cannot generate an incidence matrix.\n");
    }

    for (int i = 0; i < digraph->num_vertices; i++) {
        matrix[i] = malloc(num_edges * sizeof(int));
        if (matrix[i] == NULL) {
            printf("digraph_gen_incidence_matrix :: Memory allocation for incidence matrix row %d failed. Cannot generate an incidence matrix.\n", i);
            free(matrix);
            return NULL;

        }
        for (int j = 0; j < num_edges; j++) {
            matrix[i][j] = 0;
        }
    }

    int edge_idx = 0;
    for (int i = 0; i < digraph->num_vertices; i++) {
        Node *current_node = digraph->vertices[i]->head;
        while (current_node != NULL) {
            matrix[i][edge_idx] = 1;
            matrix[current_node->key][edge_idx] = -1;
            current_node = current_node->next;
            edge_idx++;
        }
    }
    return matrix;
}

void digraph_free_incidence_matrix(int **matrix, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


void digraph_free(Digraph *digraph) {
    for (int i = 0; i < digraph->num_vertices; i++) {
        if (digraph->vertices[i] != NULL) {
            ll_free(digraph->vertices[i]);
        }
    }
    free(digraph->vertices);
    free(digraph);
}

Digraph* digraph_build(int num_vertices, int num_edges, int edges[][2]) {
    // We don't allow self-loops
    for (int i = 0; i < num_edges; i++) {
        if (edges[i][0] == edges[i][1]) {
            printf("digraph_build :: Self-loop found in edge (%d, %d) but no self-loop is allowed.", edges[i][0], edges[i][1]);
            return NULL;
        }
    }
    LinkedList **vertices = malloc(num_vertices * sizeof(LinkedList *));
    if (vertices == NULL) {
        printf("digraph_build :: Memory allocation for digraph vertices array failed. Cannot create a digraph.\n");
        return NULL;
    }

    // Assign default NULL values to vertex elements. Is this necessary?
    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = NULL;
    }

    for (int i = 0; i < num_edges; i++) {
        // Create a new linked list if we haven't been here before.
        if (vertices[edges[i][0]] == NULL) {
            int keys[1] = {edges[i][1]};
            vertices[edges[i][0]] = ll_build(keys, 1);
        } else {
            ll_append(vertices[edges[i][0]], edges[i][1]);
        }
    }

    for (int j = 0; j < num_vertices; j++) {
        if (vertices[j] == NULL) {
            vertices[j] = ll_build(NULL, 0);
        }
    }

    Digraph *digraph = malloc(sizeof(Digraph));
    if (digraph == NULL) {
        printf("digraph_build :: Memory allocation for digraph struct failed. Cannot create a digraph.\n");
        free(vertices);
        return NULL;
    }

    digraph->vertices = vertices;
    digraph->num_vertices = num_vertices;
    return digraph;
}

void digraph_print(Digraph *digraph) {
    printf("Graph(\n");
    for (int i = 0; i < digraph->num_vertices; i++) {
        printf("{%d}: ", i);
        printf("{");
        
        Node *current_node = digraph->vertices[i]->head;
        while (current_node != NULL) {
            printf("%d", current_node->key);
            if (current_node->next != NULL) {
                printf("->");
            }
            current_node = current_node->next;
        }
        printf("},\n");
    }
    printf(")\n");
}

