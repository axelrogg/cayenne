#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

typedef struct Digraph {
    LinkedList **vertices;
    int num_vertices;
} Digraph;


Digraph* digraph_build(int num_vertices, int num_edges, int edges[][2]) {
    // We don't allow self-loops
    for (int i = 0; i < num_edges; i++) {
        if (edges[i][0] == edges[i][1]) {
            return NULL;
        }
    }
    LinkedList **vertices = malloc(num_vertices * sizeof(LinkedList *));
    if (vertices == NULL) {
        return NULL;
    }

    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = NULL;
    }

    for (int i = 0; i < num_edges; i++) {
        if (edges[i][0] == edges[i][1]) {
            return NULL;
        }
    }

    for (int i = 0; i < num_edges; i++) {
        if (vertices[edges[i][0]] == NULL) {
            // Create an empty linked list if we haven't been here before
            int keys[1] = {edges[i][1]};
            vertices[edges[i][0]] = ll_build(keys, 1);
        } else {
            ll_append(vertices[edges[i][0]], edges[i][1]);
        }
    }

    Digraph *digraph = malloc(sizeof(Digraph));
    if (digraph == NULL) {
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
        printf("}\n");
    }
    printf(")\n");
}

int main() {
    int num_vertices = 6;
    int num_edges = 8;
    int edges[8][2] = {
        {0, 1},
        {0, 3},
        {1, 4},
        {2, 4},
        {2, 5},
        {3, 1},
        {4, 3},
        {5, 4},
    };
    
    Digraph *digraph = digraph_build(num_vertices, num_edges, edges);
    digraph_print(digraph);
}
