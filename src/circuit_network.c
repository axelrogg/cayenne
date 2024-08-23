#include <stdlib.h>
#include <stdio.h>
#include "circuit_network.h"
#include "circuit_component.h"
#include "clist.h"


static int resolve_node_index(
    struct circuit_network_node **adjacency_list,
    int size,
    int node_id
) {
    int i;
    for (i = 0; i < size; i++) {
        if (!adjacency_list[i]) {
            break;
        }
        if (adjacency_list[i]->node_id == node_id) {
            break;
        }
    }
    return i;
}


struct circuit_network *circuit_network_new(struct clist *circuit_components) {
    struct circuit_network *network;
    struct circuit_network_node **adjacency_list;

    adjacency_list = malloc(
        2 * circuit_components->count * sizeof(struct network_node *)
    );
    if (!adjacency_list)
        return NULL;

    for (int i = 0; i < 2 * circuit_components->count; i++) {
        adjacency_list[i] = NULL;
    }

    struct clist_cell *cursor;
    for (cursor = circuit_components->first; cursor != NULL; cursor = cursor->next) {
        int node_position;
        struct circuit_component *component;

        component = (struct circuit_component *)cursor->data;

        // Node position is the index of adjacency_list where the
        // `component->node_positive` is
        node_position = resolve_node_index(
            adjacency_list,
            2 * circuit_components->count,
            component->node_positive
        );
        if (!adjacency_list[node_position]) {
            adjacency_list[node_position] = circuit_network_node_new(
                component->node_positive
            );

            if (!adjacency_list[node_position]) {
                printf("could not create new network node\n");
                circuit_network_adj_list_free(adjacency_list, 2 * circuit_components->count);
                return NULL;
            }
        }
        clist_append(
            adjacency_list[node_position]->incident_components, component
        );

        // Node position is the index of adjacency_list where the
        // `component->node_positive` is
        node_position = resolve_node_index(
            adjacency_list, 2 * circuit_components->count, component->node_negative
        );
        if (!adjacency_list[node_position]) {
            adjacency_list[node_position] = circuit_network_node_new(component->node_negative);
            if (!adjacency_list[node_position]) {
                circuit_network_adj_list_free(adjacency_list, 2 * circuit_components->count);
                printf("could not create new network node\n");
                return NULL;
            }
        }
    }

    int i;
    for (i = 0; i < 2 * circuit_components->count; i++) {
        if (!adjacency_list[i])
            break;
    }

    for (int j = i; j < 2 * circuit_components->count; j++) {
        if (adjacency_list[j]) {
            circuit_network_node_free(adjacency_list[j]);
        }
    }

    struct circuit_network_node **new_adj_list = realloc(adjacency_list, i * sizeof(struct circuit_network_node *));
    if (!new_adj_list) {
        circuit_network_adj_list_free(adjacency_list, 2 * circuit_components->count);
        return NULL;
    }
    adjacency_list = new_adj_list;

    network = malloc(sizeof(struct circuit_network));
    if (!network) {
        circuit_network_adj_list_free(adjacency_list, i);
        return NULL;
    }

    network->edge_count = circuit_components->count;
    network->adjacency_list = adjacency_list;
    network->node_count = i;
    return network;
}


struct circuit_network_node *circuit_network_node_new(int id) {
    struct circuit_network_node *node;

    node = malloc(sizeof(struct circuit_network_node));
    if (!node)
        return NULL;

    node->incident_components = clist_new();
    if (!node->incident_components) {
        free(node);
        return NULL;
    }
    node->node_id = id;
    return node;
}


void circuit_network_node_free(struct circuit_network_node *node) {
    if (!node) return;

    if (node->incident_components) {
        struct clist_cell *cursor;
        for (cursor = node->incident_components->first; cursor != NULL; cursor = cursor->next) {
            circuit_component_free((struct circuit_component*)cursor->data);
        }
    }

    clist_free(node->incident_components);
    free(node);
}


void circuit_network_adj_list_free(struct circuit_network_node **adjacency_list, int size) {
    if (!adjacency_list) return;

    for (int i = 0; i < size; i++) {
        circuit_network_node_free(adjacency_list[i]);
    }
    free(adjacency_list);
}


void circuit_network_free(struct circuit_network *net) {
    if (!net) return;
    circuit_network_adj_list_free(net->adjacency_list, net->node_count);
    free(net);
}
