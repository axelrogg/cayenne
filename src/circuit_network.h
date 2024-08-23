#ifndef NETWORK_H
#define NETWORK_H

struct circuit_network {
    struct circuit_network_node **adjacency_list;
    int node_count;
    int edge_count;
};

struct circuit_network_node {
    int node_id;
    struct clist *incident_components;
};

struct circuit_network *circuit_network_new(struct clist *);
struct circuit_network_node *circuit_network_node_new(int);
int **circuit_network_incidence_matrix(struct circuit_network *);
void circuit_network_free(struct circuit_network *);
void circuit_network_node_free(struct circuit_network_node *);
void circuit_network_adj_list_free(struct circuit_network_node **, int size);

#endif // !NETWORK_H
